#include <debug_lib.h>
#include <io_lib.h>

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <sys/stat.h>

uint8_t io_read(uint16_t address) {
    uint8_t value;

    if(iopl(3) < 0) {
        debug_print(DEBUG_ERROR, "fail to change iopl, errno(%s)\n", strerror(errno));
    }

    if(ioperm(address, 1, true) < 0) {
        debug_print(DEBUG_ERROR, "fail to set ioperm\n");
    }
    value = inb(address);
    TRACE_PRINT("address:0x%x, value:0x%x", address, value);

    if(iopl(0) < 0) {
        debug_print(DEBUG_ERROR, "fail to change iopl\n");
    }

    if(ioperm(address, 1, false) < 0) {
        debug_print(DEBUG_ERROR, "fail to set ioperm\n");
    }

    return value;
}

uint8_t mmio_read(uint64_t address) {
    int fd;
    void *map_base;

    if((fd = open("/dev/mem", O_RDONLY | O_SYNC)) < 0) FATAL;

    if((map_base = mmap(0, 1, PROT_READ, MAP_SHARED, fd, address)) == MAP_FAILED) FATAL;
    TRACE_PRINT("mmap at address %p", map_base);

    close(fd);
    return *((uint8_t *)map_base);
}

uint8_t pci_read(uint8_t bus, uint8_t dev, uint8_t fun, off_t off) {
    char *pcie_csr_file = malloc(50);
    FILE *file;
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

    sprintf(pcie_csr_file, "/sys/bus/pci/devices/%04x:%02x:%02x.%01x/config", 0x0, bus, dev, fun);
    printf("%s\n", pcie_csr_file);

    file = fopen(pcie_csr_file, "rb");
    if(file == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, off, SEEK_SET);

    value = (uint8_t)fgetc(file);

    fclose(file);

    return value;
}