#ifndef _IO_LIB_H_
#define _IO_LIB_H_

#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <unistd.h>

#define PAGE_SIZE 4096UL
#define PAGE_MASK (PAGE_SIZE - 1)

typedef enum {
    io_width_8 = 1,
    io_width_16 = 2,
    io_width_32 = 4,
    io_width_64 = 8,
} io_width;

typedef enum { io, mmio, pci, cpucpld, mbcpld } rw_mode;

typedef struct {
    char *key;
    rw_mode value;
} mode_dict;

typedef struct {
    uint8_t bus;
    uint8_t dev;
    uint8_t fun;
    off_t off;
} bdf;

typedef struct rw_config rw_config;
typedef bool (*rw_init)(rw_config *cfg, char *data_set[]);
typedef void (*rw_print)(rw_config *cfg);
bool rw_config_init(rw_config *cfg, char *data_set[]);
void rw_config_print(rw_config *cfg);

struct rw_config {
    uint64_t address;
    bdf bdf;
    uint64_t data;
    rw_mode mode;
    io_width width;
    bool is_address_setted;
    bool is_data_setted;
    rw_init init;
    rw_print print;
    char *format;
};

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
uint64_t mmio_read64(uint64_t address);
uint8_t mmio_write8(uint64_t address, uint8_t value);
uint16_t mmio_write16(uint64_t address, uint16_t value);
uint32_t mmio_write32(uint64_t address, uint32_t value);
uint32_t mmio_write64(uint64_t address, uint64_t value);

uint8_t pci_read8(uint8_t bus, uint8_t dev, uint8_t fun, off_t off);
uint16_t pci_read16(uint8_t bus, uint8_t dev, uint8_t fun, off_t off);
uint32_t pci_read32(uint8_t bus, uint8_t dev, uint8_t fun, off_t off);
uint64_t pci_read64(uint8_t bus, uint8_t dev, uint8_t fun, off_t off);
uint8_t pci_write8(uint8_t bus, uint8_t dev, uint8_t fun, off_t off, uint8_t value);
uint16_t pci_write16(uint8_t bus, uint8_t dev, uint8_t fun, off_t off, uint16_t value);
uint32_t pci_write32(uint8_t bus, uint8_t dev, uint8_t fun, off_t off, uint32_t value);
uint64_t pci_write64(uint8_t bus, uint8_t dev, uint8_t fun, off_t off, uint64_t value);

void rw_worker(rw_config *cfg);

#endif //_IO_LIB_H_
