#include <stdio.h>

#include "PciRwLibrary.h"
#include "debug_lib.h"
#include "efilib.h"

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

UINT8 ME_Bus;
UINT8 ME_Dev;
UINT8 ME_Fun;
UINT32 PciBase;

UINT8 PciRead8(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr) {
    UINT8 read_result; //, read_result_msb, read_result_lsb;
    void *map_base, *virt_addr;
    off_t target;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    debug(DEBUG_INFO, "fd = %d %s %d  \n", fd, __FUNCTION__, __LINE__);
    target = PciBase | (Bus << 20) | (Dev << 15) | (Fun << 12) | Addr;

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

UINT16 PciRead16(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr) {
    UINT16 read_result; //, read_result_msb, read_result_lsb;
    void *map_base, *virt_addr;
    off_t target;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    debug(DEBUG_INFO, "fd = %d %s %d  \n", fd, __FUNCTION__, __LINE__);
    target = PciBase | (Bus << 20) | (Dev << 15) | (Fun << 12) | Addr;

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

UINT32 PciRead32(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr) {
    UINT32 read_result; //, read_result_msb, read_result_lsb;
    void *map_base, *virt_addr;
    off_t target;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    debug(DEBUG_INFO, "fd = %d %s %d  \n", fd, __FUNCTION__, __LINE__);
    target = PciBase | (Bus << 20) | (Dev << 15) | (Fun << 12) | Addr;

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

UINT8 PciWrite8(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr, UINT8 writeval) {
    void *map_base, *virt_addr;
    off_t target;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    debug(DEBUG_INFO, "fd = %d %s %d  \n", fd, __FUNCTION__, __LINE__);
    target = PciBase | (Bus << 20) | (Dev << 15) | (Fun << 12) | Addr;

    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (target & MAP_MASK);
    *((UINT8 *)virt_addr) = (UINT8)writeval;

    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);
    return 0;
}

UINT16 PciWrite16(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr, UINT16 writeval) {
    void *map_base, *virt_addr;
    off_t target;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    debug(DEBUG_INFO, "fd = %d %s %d  \n", fd, __FUNCTION__, __LINE__);
    target = PciBase | (Bus << 20) | (Dev << 15) | (Fun << 12) | Addr;

    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (target & MAP_MASK);
    *((UINT16 *)virt_addr) = (UINT16)writeval;

    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);
    return 0;
}

UINT32 PciWrite32(UINT8 Bus, UINT8 Dev, UINT8 Fun, UINT32 Addr, UINT32 writeval) {
    void *map_base, *virt_addr;
    off_t target;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    debug(DEBUG_INFO, "fd = %d %s %d  \n", fd, __FUNCTION__, __LINE__);
    target = PciBase | (Bus << 20) | (Dev << 15) | (Fun << 12) | Addr;

    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (target & MAP_MASK);
    *((unsigned int *)virt_addr) = (unsigned int)writeval;

    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);
    return 0;
}

UINT8 MmioRead8(off_t target) {
    UINT8 read_result;
    void *map_base, *virt_addr;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
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
    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (target & MAP_MASK);
    read_result = *((unsigned int *)virt_addr);

    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    return read_result;
}

UINT8 MmioWrite8(off_t target, UINT8 writeval) {
    void *map_base, *virt_addr;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (target & MAP_MASK);
    *((UINT8 *)virt_addr) = writeval;

    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);
    return 0;
}

UINT16 MmioWrite16(off_t target, UINT16 writeval) {
    void *map_base, *virt_addr;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (target & MAP_MASK);
    *((UINT16 *)virt_addr) = writeval;

    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);
    return 0;
}

UINT32 MmioWrite32(off_t target, UINT32 writeval) {
    void *map_base, *virt_addr;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
    if(map_base == (void *)-1) FATAL;

    fflush(stdout);

    virt_addr = map_base + (target & MAP_MASK);
    *((unsigned int *)virt_addr) = (unsigned int)writeval;

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

UINTN PCIE_CFG_ADDRESS(UINT8 Bus, UINT8 Dev, UINT8 func, UINT32 reg) {
    return ((UINTN)(PciBase + ((Bus) << 20) + ((Dev) << 15) + ((func) << 12) + reg));
}

UINTN MmPciBase(UINT8 Bus, UINT8 Dev, UINT8 Fun) {
    return PCIE_CFG_ADDRESS(ME_Bus, ME_Dev, ME_Fun, 0);
}

UINT32 HeciPciRead32(UINT32 Register) {
    return MmioRead32(MmPciBase(ME_Bus, ME_Dev, ME_Fun) + Register);
}

UINT32 HeciPciWrite32(UINT32 Register, UINT32 Data) {
    return MmioWrite32(MmPciBase(ME_Bus, ME_Dev, ME_Fun) + Register, (UINT32)Data);
}
UINT8 HeciPciRead8(UINT32 Register) {
    return MmioRead8(MmPciBase(ME_Bus, ME_Dev, ME_Fun) + Register);
}

UINT8 HeciPciOr8(UINT32 Register, UINT32 Data) {
    return MmioOr8(MmPciBase(ME_Bus, ME_Dev, ME_Fun) + Register, (UINT8)Data);
}

VOID InitVar() {
    ME_Bus = 0;
    ME_Dev = 0;
    ME_Fun = 0;

    // Try PCIe Base = 0x80000000 first;
    PciBase = 0x80000000;

    // Broadwell-DE
    if(PciRead32(0x0, 0x1F, 0x0, 0x0) == 0x8C548086) {
        ME_Dev = 22;
    }
    // Skylake-D
    else if(PciRead32(0x0, 0x1F, 0x0, 0x0) == 0xA1C88086) {
        ME_Dev = 22;
    }
    // Icelake-D
    else if(PciRead32(0x0, 0x1F, 0x0, 0x0) == 0x18DC8086) {
        ME_Dev = 24;
    } else {
        // Try PCIe Base = 0xe0000000;
        PciBase = 0xe0000000;
        // Denverton
        if(PciRead32(0x0, 0x1F, 0x0, 0x0) == 0x19DC8086) {
            ME_Dev = 24;
        }
    }
}