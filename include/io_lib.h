#ifndef _IO_LIB_H_
#define _IO_LIB_H_

#include <fcntl.h>
#include <stdint.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <stdint.h>
#include <unistd.h>

uint8_t io_read(uint16_t address);
uint8_t mmio_read(uint64_t address);
uint8_t pci_read(uint8_t bus, uint8_t dev, uint8_t fun, off_t off);

#endif //_IO_LIB_H_
