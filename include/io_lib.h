#ifndef _IO_LIB_H_
#define _IO_LIB_H_

#include <fcntl.h>
#include <stdint.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <unistd.h>

typedef enum {
    io_width_8 = 1,
    io_width_16 = 2,
    io_width_32 = 4,
    io_width_64 = 8,
} io_width;

typedef enum {
    io,
    mmio,
    pci,
    cpucpld,
    mbcpld
} rw_mode;

uint8_t io_read8(uint16_t address);
uint16_t io_read16(uint16_t address);
uint32_t io_read32(uint16_t address);
uint64_t io_read64(uint16_t address);
uint8_t io_write8(uint16_t address, uint8_t value);
uint16_t io_write16(uint16_t address, uint16_t value);
uint32_t io_write32(uint16_t address, uint32_t value);
uint64_t io_write64(uint16_t address, uint64_t value);

uint8_t mmio_read8(uint64_t address);
uint16_t mmio_read16(uint64_t address);
uint32_t mmio_read32(uint64_t address);
uint8_t pci_read8(uint8_t bus, uint8_t dev, uint8_t fun, off_t off);

#endif //_IO_LIB_H_
