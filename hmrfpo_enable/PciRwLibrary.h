#ifndef _PCI_RW_LIBRARY_H_
#define _PCI_RW_LIBRARY_H_

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include "Pci22.h"
#include "efilib.h"

#define PCI_VENDOR_ID_OFFSET 0x00

//#define PCIE_CFG_ADDRESS(bus, dev, func, reg)   ((UINTN)(0xe0000000 + ((bus) << 20) + ((dev) << 15) + ((func) << 12) + reg))
//#define MmPciBase(ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER)   PCIE_CFG_ADDRESS(ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, 0)

UINT8 PciRead8(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr);
UINT16 PciRead16(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr);
UINT32 PciRead32(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr);

UINT8 PciWrite8(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr, UINT8 Data);
UINT16 PciWrite16(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr, UINT16 Data);
UINT32 PciWrite32(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr, UINT32 Data);

UINT8 MmioRead8(off_t Target);
UINT16 MmioRead16(off_t Target);
UINT32 MmioRead32(off_t Target);

UINT8 MmioWrite8(off_t Target, UINT8 Data);
UINT16 MmioWrite16(off_t Target, UINT16 Data);
UINT32 MmioWrite32(off_t Target, UINT32 Data);

UINT16 MmioAndThenOr16(UINTN Address, UINT16 AndData, UINT16 OrData);
UINT32 MmioAndThenOr32(UINTN Address, UINT32 AndData, UINT32 OrData);
UINT8 MmioOr8(UINTN Address, UINT8 OrData);
UINT16 MmioOr16(UINTN Address, UINT16 OrData);

VOID InitVar();
UINT32 HeciPciRead32(UINT32 Register);
UINT32 HeciPciWrite32(UINT32 Register, UINT32 Data);
UINT8 HeciPciRead8(UINT32 Register);
UINT8 HeciPciOr8(UINT32 Register, UINT8 Data);

#endif // _PCI_RW_LIBRARY_H_