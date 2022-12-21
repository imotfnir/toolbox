#include <debug_lib.h>
#include <io_lib.h>

#include <errno.h>
#include <fcntl.h>
#include <linux/pci.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <sys/stat.h>

// static function declaration
static uint64_t _io_read_worker(uint16_t address, io_width width);
static uint64_t _io_write_worker(uint16_t address, io_width width, uint64_t value);
static uint64_t _mmio_read_worker(uint64_t address, io_width width);
static uint64_t _mmio_write_worker(uint64_t address, io_width width, uint64_t value);
static uint64_t _pci_read_worker(uint8_t bus, uint8_t dev, uint8_t fun, off_t off, io_width width);
static uint64_t
_pci_write_worker(uint8_t bus, uint8_t dev, uint8_t fun, off_t off, io_width width, uint64_t value);

void rw_config_init(rw_config *cfg) {
    return;
}

void rw_config_print(rw_config *cfg) {
    debug_print(DEBUG_DEBUG, "cfg->address %-10d", cfg->address);
    debug_print(DEBUG_DEBUG, "cfg->bdf.bus %-10d", cfg->bdf.bus);
    debug_print(DEBUG_DEBUG, "cfg->bdf.dev %-10d", cfg->bdf.dev);
    debug_print(DEBUG_DEBUG, "cfg->bdf.fun %-10d", cfg->bdf.fun);
    debug_print(DEBUG_DEBUG, "cfg->bdf.off %-10d", cfg->bdf.off);
    debug_print(DEBUG_DEBUG, "cfg->data %-10ul", cfg->data);
    debug_print(DEBUG_DEBUG, "cfg->mode %-10d", cfg->mode);
    debug_print(DEBUG_DEBUG, "cfg->width %-10d", cfg->width);
    return;
}

// function definition
static uint64_t _io_read_worker(uint16_t address, io_width width) {
    uint64_t value;

    if((address & (width - 1)) != 0) {
        debug_print(DEBUG_ERROR, "io width is not aligned\n");
        return -1;
    }

    if(ioperm(address, width, true) < 0) {
        debug_print(DEBUG_ERROR, "fail to set ioperm\n");
        return -1;
    }

    switch(width) {
    case io_width_8:
        value = inb(address);
        break;
    case io_width_16:
        value = inw(address);
        break;
    case io_width_32:
        value = inl(address);
        break;
    case io_width_64:
        value = (((uint64_t)inl(address + 4)) << 32) | inl(address);
        break;
    default:
        debug_print(DEBUG_ERROR, "io width unsupport\n");
        break;
    }
    TRACE_PRINT("address:0x%x, width:%d, value:0x%x", address, width, value);

    if(ioperm(address, width, false) < 0) {
        debug_print(DEBUG_ERROR, "fail to set ioperm\n");
        return -1;
    }

    return value;
}

static uint64_t _io_write_worker(uint16_t address, io_width width, uint64_t value) {
    if((address & (width - 1)) != 0) {
        debug_print(DEBUG_ERROR, "io width is not aligned\n");
        return -1;
    }

    if(ioperm(address, width, true) < 0) {
        debug_print(DEBUG_ERROR, "fail to set ioperm\n");
        return -1;
    }

    switch(width) {
    case io_width_8:
        outb(value, address);
        break;
    case io_width_16:
        outw(value, address);
        break;
    case io_width_32:
        outl(value, address);
        break;
    case io_width_64:
        outl(value, address);
        outl(value >> 32, address + 4);
        break;
    default:
        debug_print(DEBUG_ERROR, "io width unsupport\n");
        break;
    }
    TRACE_PRINT("address:0x%x, width:%d, value:0x%x", address, width, value);

    if(ioperm(address, width, false) < 0) {
        debug_print(DEBUG_ERROR, "fail to set ioperm\n");
        return -1;
    }

    return value;
}

static uint64_t _mmio_read_worker(uint64_t address, io_width width) {
    int fd;
    void *map_base;

    if((fd = open("/dev/mem", O_RDONLY | O_SYNC)) < 0) FATAL;

    if((map_base = mmap(0, width, PROT_READ, MAP_SHARED, fd, address)) == MAP_FAILED) FATAL;
    TRACE_PRINT("mmap at address %p", map_base);

    close(fd);
    return *((uint64_t *)map_base);
}

static uint64_t _mmio_write_worker(uint64_t address, io_width width, uint64_t value) {
    int fd;
    void *map_base;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) FATAL;

    if((map_base = mmap(0, width, PROT_READ, MAP_SHARED, fd, address)) == MAP_FAILED) FATAL;
    TRACE_PRINT("mmap at address %p", map_base);

    switch(width) {
    case io_width_8:
        *(uint8_t *)map_base = value;
        break;
    case io_width_16:
        *(uint16_t *)map_base = value;
        break;
    case io_width_32:
        *(uint32_t *)map_base = value;
        break;
    case io_width_64:
    default:
        debug_print(DEBUG_ERROR, "io width unsupport\n");
        break;
    }

    close(fd);
    return value;
}

static uint64_t _pci_read_worker(uint8_t bus, uint8_t dev, uint8_t fun, off_t off, io_width width) {
    char *csr_file = malloc(50);
    FILE *fp;
    uint64_t value;

    if(dev >= 32) {
        debug_print(DEBUG_ERROR, "device number out of range = %d >= 32\n", dev);
        return -1;
    }
    if(fun >= 8) {
        debug_print(DEBUG_ERROR, "function number out of range = %d >= 8\n", fun);
        return -1;
    }
    if(off >= 0x1000) {
        debug_print(DEBUG_ERROR, "offset out of range = %d >= 4096\n", off);
        return -1;
    }

    sprintf(csr_file, "/sys/bus/pci/devices/%04x:%02x:%02x.%01x/config", 0x0, bus, dev, fun);

    fp = fopen(csr_file, "rb");
    if(fp == NULL) {
        perror("Error while opening the file.\n");
        FATAL;
    }

    fseek(fp, off, SEEK_SET);

    value = fgetc(fp);

    fclose(fp);

    return value;
}

static uint64_t _pci_write_worker(uint8_t bus,
                                  uint8_t dev,
                                  uint8_t fun,
                                  off_t off,
                                  io_width width,
                                  uint64_t value) {
    char *csr_file = malloc(50);
    FILE *fp;

    if(dev >= 32) {
        debug_print(DEBUG_ERROR, "device number out of range = %d >= 32\n", dev);
        return -1;
    }
    if(fun >= 8) {
        debug_print(DEBUG_ERROR, "function number out of range = %d >= 8\n", fun);
        return -1;
    }
    if(off >= 0x1000) {
        debug_print(DEBUG_ERROR, "offset out of range = %d >= 4096\n", off);
        return -1;
    }

    sprintf(csr_file, "/sys/bus/pci/devices/%04x:%02x:%02x.%01x/config", 0x0, bus, dev, fun);

    fp = fopen(csr_file, "wb");
    if(fp == NULL) {
        perror("Error while opening the file.\n");
        FATAL;
    }

    fseek(fp, off, SEEK_SET);

    fputc(value, fp);

    fclose(fp);

    return value;
}

uint8_t io_read8(uint16_t address) {
    return (uint8_t)_io_read_worker(address, io_width_8);
}

uint16_t io_read16(uint16_t address) {
    return (uint16_t)_io_read_worker(address, io_width_16);
}

uint32_t io_read32(uint16_t address) {
    return (uint32_t)_io_read_worker(address, io_width_32);
}

uint64_t io_read64(uint16_t address) {
    return (uint64_t)_io_read_worker(address, io_width_64);
}

uint8_t io_write8(uint16_t address, uint8_t value) {
    return (uint8_t)_io_write_worker(address, io_width_8, value);
}

uint16_t io_write16(uint16_t address, uint16_t value) {
    return (uint16_t)_io_write_worker(address, io_width_16, value);
}

uint32_t io_write32(uint16_t address, uint32_t value) {
    return (uint32_t)_io_write_worker(address, io_width_32, value);
}

uint64_t io_write64(uint16_t address, uint64_t value) {
    return (uint64_t)_io_write_worker(address, io_width_64, value);
}

uint8_t mmio_read8(uint64_t address) {
    return (uint8_t)_mmio_read_worker(address, io_width_8);
}

uint16_t mmio_read16(uint64_t address) {
    return (uint16_t)_mmio_read_worker(address, io_width_16);
}

uint32_t mmio_read32(uint64_t address) {
    return (uint32_t)_mmio_read_worker(address, io_width_32);
}

uint64_t mmio_read64(uint64_t address) {
    return (uint64_t)_mmio_read_worker(address, io_width_64);
}

uint8_t mmio_write8(uint64_t address, uint8_t value) {
    return _mmio_write_worker(address, io_width_8, value);
}

uint16_t mmio_write16(uint64_t address, uint16_t value) {
    return _mmio_write_worker(address, io_width_16, value);
}

uint32_t mmio_write32(uint64_t address, uint32_t value) {
    return _mmio_write_worker(address, io_width_32, value);
}

uint32_t mmio_write64(uint64_t address, uint64_t value) {
    return _mmio_write_worker(address, io_width_64, value);
}

uint8_t pci_read8(uint8_t bus, uint8_t dev, uint8_t fun, off_t off) {
    return (uint8_t)_pci_read_worker(bus, dev, fun, off, io_width_8);
}

uint16_t pci_read16(uint8_t bus, uint8_t dev, uint8_t fun, off_t off) {
    return (uint16_t)_pci_read_worker(bus, dev, fun, off, io_width_16);
}

uint32_t pci_read32(uint8_t bus, uint8_t dev, uint8_t fun, off_t off) {
    return (uint32_t)_pci_read_worker(bus, dev, fun, off, io_width_32);
}

void rw_worker(rw_config *cfg) {
    switch(cfg->mode) {
    case io:
        // if(cfg->is_data_setted) {
        //     _io_write_worker(cfg->address, cfg->width, cfg->data);
        //     return;
        // }
        // _io_read_worker(cfg->address, cfg->width);
        return;
    case mmio:
        // if(cfg->is_data_setted) {
        //     _mmio_write_worker(cfg->address, cfg->width, cfg->data);
        //     return;
        // }
        // _mmio_read_worker(cfg->address, cfg->width);
        return;
    case pci:
        return;

    default:
        break;
    }

    return;
}