#include <debug_lib.h>
#include <io_lib.h>

#include <stdio.h>

int main() {
    int test;
    test = mmio_read8(0x100);
    printf("0x%x\n", test);
    return 0;
}
