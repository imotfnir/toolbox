#include <debug_lib.h>
#include <io_lib.h>

#include <stdio.h>

int main() {
    int test;
    test = io_read(0x600);
    printf("%d", test);
    return 0;
}
