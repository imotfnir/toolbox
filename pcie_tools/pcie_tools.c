#include <debug_lib.h>
#include <io_lib.h>

#include <stdio.h>

int main() {
    int test;
    test = io_read(0x600);
    printf("0x%x\n", test);
    test = mmio_read(0xa0000);
    printf("0x%x\n", test);
    test = pci_read(0x16, 0x33, 0x2, 0x100);
    printf("0x%x\n", test);
    test = pci_read(0x16, 0x1f, 0x2, 0x100);
    printf("0x%x\n", test);
    return 0;
}
