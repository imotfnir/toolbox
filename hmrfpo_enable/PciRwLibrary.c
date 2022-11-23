#include <stdio.h>

#include "PciRwLibrary.h"
#include "debug_lib.h"
#include "efilib.h"

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

UINT8 MeBus;
UINT8 MeDev;
UINT8 MeFun;
UINT32 PciBase;

UINT8 PciRead8(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr) {
    off_t target;
    debug(DEBUG_TRACE, "Bus = 0x%x, Dev=0x%x, Fun=0x%x, Addr=0x%x %s %d \n", Bus, Dev, Fun, Addr, __FUNCTION__, __LINE__);
    target = PciBase | (Bus << 20) | (Dev << 15) | (Fun << 12) | Addr;
    return MmioRead8(target);
}

UINT16 PciRead16(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr) {
    off_t target;
    debug(DEBUG_TRACE, "Bus = 0x%x, Dev=0x%x, Fun=0x%x, Addr=0x%x %s %d \n", Bus, Dev, Fun, Addr, __FUNCTION__, __LINE__);
    target = PciBase | (Bus << 20) | (Dev << 15) | (Fun << 12) | Addr;
    return MmioRead16(target);
}

UINT32 PciRead32(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr) {
    off_t target;
    debug(DEBUG_TRACE, "Bus = 0x%x, Dev=0x%x, Fun=0x%x, Addr=0x%x %s %d \n", Bus, Dev, Fun, Addr, __FUNCTION__, __LINE__);
    target = PciBase | (Bus << 20) | (Dev << 15) | (Fun << 12) | Addr;
    return MmioRead32(target);
}

UINT8 PciWrite8(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr, UINT8 Data) {
    off_t target;
    debug(DEBUG_TRACE, "Bus = 0x%x, Dev=0x%x, Fun=0x%x, Addr=0x%x %s %d \n", Bus, Dev, Fun, Addr, __FUNCTION__, __LINE__);
    target = PciBase | (Bus << 20) | (Dev << 15) | (Fun << 12) | Addr;
    return MmioWrite8(target, Data);
}

UINT16 PciWrite16(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr, UINT16 Data) {
    off_t target;
    debug(DEBUG_TRACE, "Bus = 0x%x, Dev=0x%x, Fun=0x%x, Addr=0x%x %s %d \n", Bus, Dev, Fun, Addr, __FUNCTION__, __LINE__);
    target = PciBase | (Bus << 20) | (Dev << 15) | (Fun << 12) | Addr;
    return MmioWrite16(target, Data);
}

UINT32 PciWrite32(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr, UINT32 Data) {
    off_t target;
    debug(DEBUG_TRACE, "Bus = 0x%x, Dev=0x%x, Fun=0x%x, Addr=0x%x %s %d \n", Bus, Dev, Fun, Addr, __FUNCTION__, __LINE__);
    target = PciBase | (Bus << 20) | (Dev << 15) | (Fun << 12) | Addr;
    return MmioWrite32(target, Data);
}

UINT8 MmioRead8(off_t target) {
    UINT8 read_result;
    void *map_base, *virt_addr;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    debug(DEBUG_TRACE, "fd = %d, addr = 0x%x %s %d  \n", fd, target, __FUNCTION__, __LINE__);
    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (target & MAP_MASK);
    read_result = *((UINT8 *)virt_addr);

    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);
    return read_result;
}

UINT16 MmioRead16(off_t target) {
    UINT16 read_result;
    void *map_base, *virt_addr;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    debug(DEBUG_TRACE, "fd = %d, addr = 0x%x %s %d  \n", fd, target, __FUNCTION__, __LINE__);
    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (target & MAP_MASK);
    read_result = *((UINT16 *)virt_addr);

    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);
    return read_result;
}

UINT32 MmioRead32(off_t target) {
    UINT32 read_result;
    void *map_base, *virt_addr;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    debug(DEBUG_TRACE, "fd = %d, addr = 0x%x %s %d  \n", fd, target, __FUNCTION__, __LINE__);
    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (target & MAP_MASK);
    read_result = *((unsigned int *)virt_addr);

    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);
    return read_result;
}

UINT8 MmioWrite8(off_t Target, UINT8 Data) {
    void *map_base, *virt_addr;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    debug(DEBUG_TRACE, "fd = %d, addr = 0x%x %s %d  \n", fd, Target, __FUNCTION__, __LINE__);
    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, Target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (Target & MAP_MASK);
    *((UINT8 *)virt_addr) = Data;

    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);
    return 0;
}

UINT16 MmioWrite16(off_t Target, UINT16 Data) {
    void *map_base, *virt_addr;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    debug(DEBUG_TRACE, "fd = %d, addr = 0x%x %s %d  \n", fd, Target, __FUNCTION__, __LINE__);
    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, Target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (Target & MAP_MASK);
    *((UINT16 *)virt_addr) = Data;

    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);
    return 0;
}

UINT32 MmioWrite32(off_t Target, UINT32 Data) {
    void *map_base, *virt_addr;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    debug(DEBUG_TRACE, "fd = %d, addr = 0x%x %s %d  \n", fd, Target, __FUNCTION__, __LINE__);
    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, Target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (Target & MAP_MASK);
    *((unsigned int *)virt_addr) = (unsigned int)Data;

    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);
    return 0;
}

UINT32
MmioAndThenOr32(
    UINTN Address,
    UINT32 AndData,
    UINT32 OrData) {
    return MmioWrite32(Address, (MmioRead32(Address) & AndData) | OrData);
}

UINT16
MmioAndThenOr16(
    IN UINTN Address,
    IN UINT16 AndData,
    IN UINT16 OrData) {
    return MmioWrite16(Address, (UINT16)((MmioRead16(Address) & AndData) | OrData));
}

UINT8
EFIAPI
MmioOr8(
    IN UINTN Address,
    IN UINT8 OrData) {
    return MmioWrite8(Address, (UINT8)(MmioRead8(Address) | OrData));
}

UINT16
EFIAPI
MmioOr16(
    IN UINTN Address,
    IN UINT16 OrData) {
    return MmioWrite16(Address, (UINT16)(MmioRead16(Address) | OrData));
}

UINT32 HeciPciRead32(UINT32 Register) {
    return PciRead32(MeBus, MeDev, MeFun, Register);
}

UINT32 HeciPciWrite32(UINT32 Register, UINT32 Data) {
    return PciWrite32(MeBus, MeDev, MeFun, Register, Data);
}
UINT8 HeciPciRead8(UINT32 Register) {
    return PciRead8(MeBus, MeDev, MeFun, Register);
}

UINT8 HeciPciOr8(UINT32 Register, UINT8 Data) {
    return MmioOr8((PciBase | (MeBus << 20) | (MeDev << 15) | (MeFun << 12)) + Register, Data);
}

VOID InitPlatformInfo() {
    debug(DEBUG_DEBUG, "%s %d  \n", __FUNCTION__, __LINE__);
    MeBus = 0;
    MeDev = 0;
    MeFun = 0;

    // Try PCIe Base = 0x80000000 first;
    PciBase = 0x80000000;

    // Broadwell-DE
    if(PciRead32(0x0, 0x1F, 0x0, 0x0) == 0x8C548086) {
        PciBase = 0x80000000;
        MeDev = 22;
        debug(DEBUG_INFO, "PciBase=0x%x, MeBus = 0x%x, MeDev = 0x%x, MeFun=0x%x %s %d  \n", PciBase, MeBus, MeDev, MeFun, __FUNCTION__, __LINE__);
        return;
    }
    // Skylake-D
    if(PciRead32(0x0, 0x1F, 0x0, 0x0) == 0xA1C88086) {
        PciBase = 0x80000000;
        MeDev = 22;
        debug(DEBUG_INFO, "PciBase=0x%x, MeBus = 0x%x, MeDev = 0x%x, MeFun=0x%x %s %d  \n", PciBase, MeBus, MeDev, MeFun, __FUNCTION__, __LINE__);
        return;
    }
    // Icelake-D
    if(PciRead32(0x0, 0x1F, 0x0, 0x0) == 0x18DC8086) {
        PciBase = 0x80000000;
        MeDev = 24;
        debug(DEBUG_INFO, "PciBase=0x%x, MeBus = 0x%x, MeDev = 0x%x, MeFun=0x%x %s %d  \n", PciBase, MeBus, MeDev, MeFun, __FUNCTION__, __LINE__);
        return;
    }
    // Try PCIe Base = 0xe0000000;
    PciBase = 0xe0000000;
    // Denverton
    if(PciRead32(0x0, 0x1F, 0x0, 0x0) == 0x19DC8086) {
        PciBase = 0xe0000000;
        MeDev = 24;
        debug(DEBUG_INFO, "PciBase=0x%x, MeBus = 0x%x, MeDev = 0x%x, MeFun=0x%x %s %d  \n", PciBase, MeBus, MeDev, MeFun, __FUNCTION__, __LINE__);
        return;
    }
}
