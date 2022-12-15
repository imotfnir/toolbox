#include <debug_lib.h>
#include <io_lib.h>

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_help();
void show_version();
unsigned long djb_hash(char *str);
bool is_flag_supported(char *flag);

const char *flag_list[] = { "-h", "--help", "-v", "--version", "-w", "--width", "-io", "-mmio", "-pci", "-cc", "-mc" };

void show_help() {
    // ToDo
    printf("Here is the help\n");
    return;
}

void show_version() {
    // ToDo
    printf("Here is the version\n");
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

bool is_flag_supported(char *flag) {
    const int len = sizeof(flag_list) / sizeof(flag_list[0]);
    for(size_t i = 0; i < len; i++) {
        if(strcasecmp(flag_list[i], flag) == 0)
            return true;
    }
    return false;
}

bool set_mode(rw_mode *mode, char *flag) {
    static bool is_mode_setted = false;

    if(is_mode_setted) {
        debug_print(DEBUG_ERROR, "Mode duplicated\n");
        return false;
    }

    if(strcasecmp("-io", flag) == 0)
        *mode = io;
    if(strcasecmp("-mmio", flag) == 0)
        *mode = mmio;
    if(strcasecmp("-pci", flag) == 0)
        *mode = pci;
    if(strcasecmp("-cc", flag) == 0)
        *mode = cpucpld;
    if(strcasecmp("-mc", flag) == 0)
        *mode = mbcpld;

    is_mode_setted = true;
    return true;
}

int main(int argc, char *argv[]) {
    rw_mode mode = io;
    io_width width = io_width_8;
    daddr_t addr = 0;
    char *convert_checker = NULL;
    unsigned long val;
    bool is_mode_setted = false;

    debug_print(DEBUG_INFO, "Your have enter %d arguments\n", argc);
    for(size_t i = 0; i < argc; i++) {
        TRACE_PRINT("argv[%d] %-11s hash:0x%-16lX ", i, argv[i], djb_hash(argv[i]));
    }

    for(size_t i = 1; i < argc; i++) {
        val = strtoul(argv[i], &convert_checker, 0);
        if(*convert_checker == '\0') { /* argv[i] convert to digit success */
            addr = val;
            debug_print(DEBUG_INFO, "argv[%d] %-8s: 0x%x\n", i, "Address", addr);
            continue;
        }

        if(!is_flag_supported(argv[i])) {
            debug_print(DEBUG_ERROR, "argv[%d] flag: '%s' not support ", i, argv[i]);
            return 1;
        }

        if((strcasecmp("-h", argv[i]) == 0) || (strcasecmp("--help", argv[i]) == 0)) {
            show_help();
            return 0;
        }

        if((strcasecmp("-v", argv[i]) == 0) || (strcasecmp("--version", argv[i]) == 0)) {
            show_version();
            return 0;
        }

        if((strcasecmp("-w", argv[i]) == 0) || (strcasecmp("--width", argv[i]) == 0)) {
            if(++i >= argc) {
                debug_print(DEBUG_ERROR, "Width can not empty\n");
                return 1;
            }
            width = strtoul(argv[i], &convert_checker, 0);
            switch(width) {
            case io_width_8:
            case io_width_16:
            case io_width_32:
                debug_print(DEBUG_INFO, "argv[%d] %-8s: %d\n", i, "Width", width);
                continue;
            case io_width_64:
            default:
                debug_print(DEBUG_ERROR, "argv[%d] Width not support\n", i);
                return 1;
            }
        }

        if(strcasecmp("-io", argv[i]) == 0) {
            if(is_mode_setted) {
                debug_print(DEBUG_ERROR, "argv[%d] Mode duplicated\n", i);
                return 1;
            }
            mode = io;
            is_mode_setted = true;
            debug_print(DEBUG_INFO, "argv[%d] %-8s: %s\n", i, "Mode", "io");
        }

        if(strcasecmp("-mmio", argv[i]) == 0) {
            if(is_mode_setted) {
                debug_print(DEBUG_ERROR, "argv[%d] Mode duplicated\n", i);
                return 1;
            }
            mode = mmio;
            is_mode_setted = true;
            debug_print(DEBUG_INFO, "argv[%d] %-8s: %s\n", i, "Mode", "mmio");
        }

        if(strcasecmp("-pci", argv[i]) == 0) {
            if(is_mode_setted) {
                debug_print(DEBUG_ERROR, "argv[%d] Mode duplicated\n", i);
                return 1;
            }
            mode = pci;
            is_mode_setted = true;
            debug_print(DEBUG_INFO, "argv[%d] %-8s: %s\n", i, "Mode", "pci");
        }
    }
    return 0;
}