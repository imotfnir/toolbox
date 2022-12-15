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
bool set_digit_args_to_config(rw_config *cfg, int val);
bool set_width_to_config(rw_config *cfg, char *flag);
bool set_mode_to_config(rw_config *cfg, char *flag);

const char *flag_list[]
    = { "-h", "--help", "-v", "--version", "-w", "--width", "-io", "-mmio", "-pci", "-cc", "-mc" };

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

    while((c = *str++)) { hash = ((hash << 5) + hash) + c; /* hash * 33 + c */ }

    return hash;
}

bool is_flag_supported(char *flag) {
    const int len = sizeof(flag_list) / sizeof(flag_list[0]);
    for(size_t i = 0; i < len; i++) {
        if(strcasecmp(flag_list[i], flag) == 0) return true;
    }
    debug_print(DEBUG_ERROR, "Argument %s not supported\n", flag);
    return false;
}

bool set_digit_args_to_config(rw_config *cfg, int val) {
    static size_t digit_args_count = 0;
    if(digit_args_count >= 2) {
        debug_print(DEBUG_ERROR, "Too many data\n");
        return false;
    }
    if(digit_args_count == 0) {
        cfg->address = val;
        debug_print(DEBUG_DEBUG, "Address = 0x%x\n", cfg->address);
    }
    if(digit_args_count == 1) {
        cfg->data = val;
        debug_print(DEBUG_DEBUG, "Address = 0x%x\n", cfg->data);
    }

    digit_args_count++;
    return true;
}

bool set_width_to_config(rw_config *cfg, char *flag) {
    int val;
    char *success;

    val = strtoul(flag, &success, 0);
    if(!*success == '\0') {
        debug_print(DEBUG_DEBUG, "%s not a digit\n", flag);
        return false;
    }
    switch(val) {
    case io_width_8:
    case io_width_16:
    case io_width_32:
        cfg->width = val;
        break;
    case io_width_64:
    default:
        debug_print(DEBUG_DEBUG, "Width not support\n");
        break;
    }
    debug_print(DEBUG_INFO, "Width = %d\n", cfg->width);
    return true;
}

bool set_mode_to_config(rw_config *cfg, char *flag) {
    static bool is_mode_setted = false;

    if(is_mode_setted) {
        debug_print(DEBUG_ERROR, "Mode duplicated\n");
        return false;
    }

    if(strcasecmp("-io", flag) == 0) cfg->mode = io;
    if(strcasecmp("-mmio", flag) == 0) cfg->mode = mmio;
    if(strcasecmp("-pci", flag) == 0) cfg->mode = pci;
    if(strcasecmp("-cc", flag) == 0) cfg->mode = cpucpld;
    if(strcasecmp("-mc", flag) == 0) cfg->mode = mbcpld;

    is_mode_setted = true;
    debug_print(DEBUG_INFO, "Mode = %d, %s\n", cfg->mode, flag);
    return true;
}

int main(int argc, char *argv[]) {
    rw_config *cfg = malloc(sizeof(rw_config));
    char *convert_checker = NULL;
    unsigned long val;

    cfg->address = 0x0;
    cfg->data = 0x0;
    cfg->mode = io;
    cfg->width = io_width_8;

    debug_print(DEBUG_INFO, "Your have enter %d arguments\n", argc);
    for(size_t i = 0; i < argc; i++) {
        TRACE_PRINT("argv[%d] %-11s hash:0x%-16lX ", i, argv[i], djb_hash(argv[i]));
    }

    for(size_t i = 1; i < argc; i++) {
        val = strtoul(argv[i], &convert_checker, 0);
        if(*convert_checker == '\0') { /* argv[i] convert to digit success */
            if(!set_digit_args_to_config(cfg, val)) return 1;
            continue;
        }

        if(!is_flag_supported(argv[i])) return 1;

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
            if(!set_width_to_config(cfg, argv[i])) return 1;
        }

        if((strcasecmp("-io", argv[i]) == 0) || (strcasecmp("-mmio", argv[i]) == 0)
           || (strcasecmp("-pci", argv[i]) == 0) || (strcasecmp("-cc", argv[i]) == 0)
           || (strcasecmp("-mc", argv[i]) == 0)) {
            if(!set_mode_to_config(cfg, argv[i])) return 1;
        }
    }
    return 0;
}