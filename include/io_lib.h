#ifndef _IO_LIB_H_
#define _IO_LIB_H_

#include <fcntl.h>
#include <stdint.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

__uint8_t io_read(__uint16_t address);
__uint8_t mmio_read(__uint64_t address);

#endif //_IO_LIB_H_
