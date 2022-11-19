#ifndef _PCIRW_LIBRARY_H_
#define _PCIRW_LIBRARY_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

#include "efilib.h"
#include "Pci22.h"

#define PCI_VENDOR_ID_OFFSET                        0x00

//#define PCIE_CFG_ADDRESS(bus, dev, func, reg)   ((UINTN)(0xe0000000 + ((bus) << 20) + ((dev) << 15) + ((func) << 12) + reg))
//#define MmPciBase(ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER)   PCIE_CFG_ADDRESS(ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, 0)

UINT8  PciRead8(UINT8 bus, UINT8 dev, UINT8 fun, UINT32 addr);
UINT16 PciRead16(UINT8 bus, UINT8 dev, UINT8 fun, UINT32 addr);
UINT32 PciRead32(UINT8 bus, UINT8 dev, UINT8 fun, UINT32 addr);

UINT8  PciWrite8(UINT8 bus, UINT8 dev, UINT8 fun, UINT32 addr, UINT8 writeval);
UINT16 PciWrite16(UINT8 bus, UINT8 dev, UINT8 fun, UINT32 addr, UINT16 writeval);
UINT32 PciWrite32(UINT8 bus, UINT8 dev, UINT8 fun, UINT32 addr, UINT32 writeval);

UINT8  MmioRead8(off_t target);
UINT16 MmioRead16(off_t target);
UINT32 MmioRead32(off_t target);

UINT8  MmioWrite8(off_t target, UINT8 writeval);
UINT16 MmioWrite16(off_t target, UINT16 writeval);
UINT32 MmioWrite32(off_t target, UINT32 writeval);

UINT16 MmioAndThenOr16 (UINTN Address, UINT16 AndData, UINT16 OrData);
UINT32 MmioAndThenOr32 (UINTN Address, UINT32 AndData, UINT32 OrData);
UINT8  MmioOr8 (UINTN Address, UINT8 OrData);
UINT16 MmioOr16 (UINTN Address, UINT16 OrData);

UINTN PCIE_CFG_ADDRESS (UINT8 bus, UINT8 dev, UINT8 func, UINT32 reg);
UINTN MmPciBase (UINT8 bus, UINT8 dev, UINT8 fun);

VOID    InitVar();
UINT32  HeciPciRead32(UINT32 Register);
UINT32  HeciPciWrite32(UINT32 Register, UINT32 Data);
UINT8   HeciPciRead8(UINT32 Register);
UINT8   HeciPciOr8(UINT32 Register, UINT32 Data);

#endif