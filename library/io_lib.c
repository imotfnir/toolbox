#include <debug_lib.h>
#include <io_lib.h>

#include <stdbool.h>

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

    if((fd = open("/dev/mem", O_RDONLY | O_SYNC)) < 0) FATAL;

    close(fd);
    return 0;
}
