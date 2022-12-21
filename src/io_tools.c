#include <debug_lib.h>
#include <io_lib.h>

#include <ctype.h>
#include <getopt.h>
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

bool set_digit_args_to_config(rw_config *cfg, int val) {
    static size_t digit_args_count = 0;
    if(digit_args_count >= 2) {
        debug_print(DEBUG_ERROR, "Too many data\n");
        return false;
    }
    if(digit_args_count == 0) {
        cfg->address = val;
        cfg->is_address_setted = true;
        debug_print(DEBUG_DEBUG, "Address = 0x%x\n", cfg->address);
    }
    if(digit_args_count == 1) {
        cfg->data = val;
        cfg->is_data_setted = true;
        debug_print(DEBUG_DEBUG, "Address = 0x%x\n", cfg->data);
    }

    digit_args_count++;
    return true;
}

int main(int argc, char *argv[]) {
    int opt;
    rw_config *cfg = malloc(sizeof(rw_config));
    bool is_mode_setted = false;
    char *convert_checker = NULL;

    static struct option long_opt[] = { { "help", no_argument, NULL, 'h' },
                                        { "version", no_argument, NULL, 'v' },
                                        { "width", required_argument, NULL, 'w' },
                                        { "io", no_argument, 0, io },
                                        { "mmio", no_argument, 0, mmio },
                                        { "pci", no_argument, 0, pci },
                                        { 0, 0, 0, 0 } };

    cfg->address = 0x0;
    cfg->data = 0x0;
    cfg->mode = io;
    cfg->width = io_width_8;
    cfg->is_address_setted = false;
    cfg->is_data_setted = false;
    cfg->init = rw_config_init;
    cfg->print = rw_config_print;

    debug_print(DEBUG_INFO, "Your have enter %d arguments\n", argc);
    for(size_t i = 0; i < argc; i++) {
        TRACE_PRINT("argv[%d] %-11s hash:0x%-16lX ", i, argv[i], djb_hash(argv[i]));
    }

    while((opt = getopt_long(argc, argv, "hvw:", long_opt, NULL)) != -1) {
        switch(opt) {
        case 'h':
            show_help();
            return 0;
        case 'v':
            show_version();
            return 0;
        case 'w':
            cfg->width = strtoul(optarg, &convert_checker, 0);
            if(*convert_checker != '\0') { /* optarg convert to digit success */
                debug_print(DEBUG_ERROR, "%s not a number\n", optarg);
                exit(EXIT_FAILURE);
            }
            debug_print(DEBUG_INFO, "Width: %lu\n", cfg->width);
            break;
        case io:
        case mmio:
        case pci:
            if(is_mode_setted) {
                debug_print(DEBUG_ERROR, "Mode duplicated\n");
                exit(EXIT_FAILURE);
            }
            debug_print(DEBUG_INFO, "Mode: %d\n", opt);
            cfg->mode = opt;
            is_mode_setted = true;
            break;
        case ':':
            break;
        case '?':
            break;
        default:
            break;
        }
    }

    if(!cfg->init(cfg, argv + optind)) exit(EXIT_FAILURE);
    cfg->print(cfg);

    exit(EXIT_SUCCESS);
}