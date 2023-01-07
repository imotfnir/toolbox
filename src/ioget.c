#include <debug_lib.h>
#include <io_lib.h>

#include <ctype.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_help();
void show_version();
unsigned long djb_hash(char *str);

void show_help() {
    printf("USAGE:\n"
           "    io_tools <address> [<value>] [-h|-v] [-w 1|2|4|8] [-f <format>]\n"
           "\n"
           "OPTIONS:\n"
           "    -h, --help\n"
           "        Prints the usage for this tools and exit\n"
           "    -v, --version\n"
           "        Prints version for this toolbox and exit\n"
           "    -w, --width <io_width>\n"
           "        Set io access width, width only can be 1, 2, 4, 8\n"
           "        Default width is 1\n"
           "    -f, --format <format>\n"
           "        Set the output format for register value, default is "
           "\"0x%%llx\\n\" \n"
           "        Format string is define by libc, \"man 3 printf\" for "
           "more information\n"
           "\n"
           "EXAMPLE:\n"
           "    Read IO 0x600 1 byte\n"
           "        ./ioget -w 1 --io 0x600\n"
           "        ./ioget 1536\n"
           "    You can change the output format by yourself\n"
           "        ./ioget 0x606 : 0x43\n"
           "        ./ioget 0x606 -f \"%%x\" : 43\n"
           "        ./ioget 0x606 -f \"%%d\" : 67\n"
           "        ./ioget 0x606 -f \"%%o\" : 103\n"
           "\n"

    );
    return;
}

void show_version() {
    printf("toolbox version v%d.%d.%d\n", MAJOR, MINOR, PATCH);
    printf("ioget version v%d.%d.%d\n", 1, 5, 0);
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
    int opt;
    rw_config *cfg = malloc(sizeof(rw_config));
    char *convert_checker = NULL;

    if(argc <= 1) {
        show_help();
        return 0;
    }

    // rw_config default value
    cfg->address = 0x0;
    cfg->data = 0x0;
    cfg->mode = io;
    cfg->width = io_width_8;
    cfg->is_address_setted = false;
    cfg->is_data_setted = false;
    cfg->init = rw_config_init;
    cfg->print = rw_config_print;
    cfg->format = "0x%" PRIxMAX "\n";

    debug_print(DEBUG_INFO, "Your have enter %d arguments\n", argc);
    for(size_t i = 0; i < argc; i++) {
        TRACE_PRINT(
            "argv[%d] %-11s hash:0x%-16lX ", i, argv[i], djb_hash(argv[i]));
    }
    // All supported long option
    static struct option long_opt[] = {
        {"help",     no_argument,       NULL, 'h'},
        { "version", no_argument,       NULL, 'v'},
        { "width",   required_argument, NULL, 'w'},
        { "format",  required_argument, NULL, 'f'},
    };

    while((opt = getopt_long(argc, argv, "hvw:f:", long_opt, NULL)) != -1) {
        switch(opt) {
        case 'h':
            show_help();
            return 0;
        case 'v':
            show_version();
            return 0;
        case 'w':
            cfg->width = strtoul(optarg, &convert_checker, 0);
            if(*convert_checker
               != '\0') { /* optarg convert to digit success */
                debug_print(DEBUG_ERROR, "%s not a number\n", optarg);
                return 1;
            }
            debug_print(DEBUG_INFO, "Width: %lu\n", cfg->width);
            break;
        case 'f':
            cfg->format = optarg;
            break;
        case ':':
            break;
        case '?':
            break;
        default:
            break;
        }
    }

    // Invalid Non-option args
    if(argc - optind > 1) {
        debug_print(DEBUG_INFO, "Too many input argument\n");
        return 1;
    }
    if(argc - optind < 1) {
        debug_print(DEBUG_INFO, "Please enter address\n");
        return 1;
    }

    if(!cfg->init(cfg, argv + optind)) return 1;
    cfg->print(cfg);

    rw_worker(cfg);

    printf(cfg->format, cfg->data);

    return 0;
}