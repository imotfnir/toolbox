#include <debug_lib.h>
#include <io_lib.h>

#include <stdio.h>

int main() {
    int test;
    test = io_read8(0x600);
    printf("0x%x\n", test);
    test = io_read16(0x600);
    printf("0x%x\n", test);
    test = io_read32(0x600);
    printf("0x%x\n", test);
    test = io_write8(0x600, 0x0);
    return 0;
}
