#include <debug_lib.h>
#include <io_lib.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_help();
unsigned long djb_hash(char *str);

typedef enum {
    io,
    mmio,
    pci,
    cpucpld,
    mbcpld
} rw_mode;

void show_help() {
    printf("Here is the help\n");
    return;
}

unsigned long djb_hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

int main(int argc, char *argv[]) {
    rw_mode mode = 0xff;
    io_width width = 0;

    debug_print(DEBUG_INFO, "Your have enter %d arguments\n", argc);
    for(int i = 0; i < argc; i++) {
        debug_print(DEBUG_TRACE, "argv[%d] %-11s hash:0x%-16lX \n", i, argv[i], djb_hash(argv[i]));
    }

    for(int i = 1; i < argc; i++) {
        debug_print(DEBUG_DEBUG, "argv[%d] %-8s ", i, argv[i], djb_hash(argv[i]));
        if((strcasecmp("-h", argv[i]) == 0) || (strcasecmp("--help", argv[i]) == 0)) {
            show_help();
        }
        if((strcasecmp("-w", argv[i]) == 0) || (strcasecmp("--width", argv[i]) == 0)) {
            width = atoi(argv[i++ + 1]);
            debug_print(DEBUG_INFO, "%-8s: %d\n", "Width", width);
        }
        if(strcasecmp("-io", argv[i]) == 0) {
            mode = io;
            debug_print(DEBUG_INFO, "%-8s: %s\n", "Mode", "io");
        }
        if(strcasecmp("-mmio", argv[i]) == 0) {
            mode = mmio;
            debug_print(DEBUG_INFO, "%-8s: %s\n", "Mode", "mmio");
        }
    }
    return 0;
}