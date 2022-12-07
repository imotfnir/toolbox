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

uint8_t io_write8(uint16_t address, uint8_t value) {
    return (uint8_t)_io_write_worker(address, io_width_8, value);
}

uint8_t mmio_read8(uint64_t address) {
    int fd;
    void *map_base;

    if((fd = open("/dev/mem", O_RDONLY | O_SYNC)) < 0) FATAL;

    if((map_base = mmap(0, 1, PROT_READ, MAP_SHARED, fd, address)) == MAP_FAILED) FATAL;
    TRACE_PRINT("mmap at address %p", map_base);

    close(fd);
    return *((uint8_t *)map_base);
}

uint8_t pci_read8(uint8_t bus, uint8_t dev, uint8_t fun, off_t off) {
    char *csr_file = malloc(50);
    FILE *fp;
    uint8_t value;

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

    value = (uint8_t)fgetc(fp);

    fclose(fp);

    return value;
}