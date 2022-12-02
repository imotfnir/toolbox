#include <debug_lib.h>
#include <io_lib.h>

#include <fcntl.h>
#include <stdbool.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <sys/stat.h>

__uint8_t io_read(__uint16_t address) {
    __uint8_t value;

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

__uint8_t mmio_read(__uint64_t address) {
    int fd;
    void *map_base;

    if((fd = open("/dev/mem", O_RDONLY | O_SYNC)) < 0) FATAL;

    if((map_base = mmap(0, 1, PROT_READ, MAP_SHARED, fd, address)) == MAP_FAILED) FATAL;
    TRACE_PRINT("mmap at address %p", map_base);

    close(fd);
    return *((__uint8_t *)map_base);
}
