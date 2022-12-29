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

void show_help() {
    printf("USAGE:\n"
           "\tio_tools address <value> [-h|-v] [--io|--mmio|--pci] [-w 1|2|4|8] [-f format]\n\n"
           "OPTIONS:\n"
           "\t-h, --help\n"
           "\t\tPrints the usage for this tools and exit\n"
           "\n"
           "\t-v, --version\n"
           "\t\tPrints version for this toolbox and exit\n"
           "\n"
           "\t-w, --width <io_width>\n"
           "\t\tSet io access width, width only can be 1, 2, 4, 8\n"
           "\t\tDefault width is 1\n"
           "\n"
           "\t--io, --mmio, --pci\n"
           "\t\tSet io access mode, if not specified, default is --io\n"
           "\t\t--io IO address type\n"
           "\t\t--mmio Memory-Mapped IO address type\n"
           "\t\t--pci PCIe configuration space registers\n"
           "\n"
           "\t-f, --format\n"
           "\t\tSet the output format for register value, default is \"0x%%x\\n\" \n"
           "\n"
           "EXAMPLE:\n"
           "\tRead IO 0x600 1 byte\n"
           "\t\t./io_tools -w 1 --io 0x600\n"
           "\t\t./io_tools 1536\n"
           "\n"
           "\tWrite IO 0x6ff 1 byte\n"
           "\t\t./io_tools 0x6ff 0x80\n"
           "\n"
           "\tRead PCIe device 90:05.0 offset 0x10 2 byte\n"
           "\t\t./io_tools 0x90 0x5 0x0 0x10 --width 2 --pci\n"
           "\n"
           "\tYou can change the output format by yourself\n"
           "\t\t./io_tools 0x606 : 0x43\n"
           "\t\t./io_tools 0x606 -f \"%%x\" : 43\n"
           "\t\t./io_tools 0x606 -f \"%%d\" : 67\n"
           "\t\t./io_tools 0x606 -f \"%%o\" : 103\n"
           "\n"
           "OTHER:\n"
           "\t\tIf value SET, that is write command\n"
           "\t\tIf value NOT set, that is read command\n"
           "\n"

    );
    return;
}

void show_version() {
    printf("toolbox version v%d.%d.%d\n", MAJOR, MINOR, PATCH);
    return;
}

unsigned long djb_hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while((c = *str++)) { hash = ((hash << 5) + hash) + c; /* hash * 33 + c */ }

    return hash;
}

int main(int argc, char *argv[]) {
    int opt;
    rw_config *cfg = malloc(sizeof(rw_config));
    bool is_mode_setted = false;
    char *convert_checker = NULL;

    if(argc <= 1) {
        show_version();
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
    cfg->format = "0x%x\n";

    debug_print(DEBUG_INFO, "Your have enter %d arguments\n", argc);
    for(size_t i = 0; i < argc; i++) {
        TRACE_PRINT("argv[%d] %-11s hash:0x%-16lX ", i, argv[i], djb_hash(argv[i]));
    }
    // All supported long option
    static struct option long_opt[] = {
        {"help",     no_argument,       NULL, 'h' },
        { "version", no_argument,       NULL, 'v' },
        { "width",   required_argument, NULL, 'w' },
        { "io",      no_argument,       0,    io  },
        { "mmio",    no_argument,       0,    mmio},
        { "pci",     no_argument,       0,    pci },
        { "format",  required_argument, NULL, 'f' },
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
            if(*convert_checker != '\0') { /* optarg convert to digit success */
                debug_print(DEBUG_ERROR, "%s not a number\n", optarg);
                return 1;
            }
            debug_print(DEBUG_INFO, "Width: %lu\n", cfg->width);
            break;
        case io:
        case mmio:
        case pci:
            if(is_mode_setted) {
                debug_print(DEBUG_ERROR, "Mode duplicated\n");
                return 1;
            }
            debug_print(DEBUG_INFO, "Mode: %d\n", opt);
            cfg->mode = opt;
            is_mode_setted = true;
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

    if(!cfg->init(cfg, argv + optind)) return 1;
    cfg->print(cfg);

    rw_worker(cfg);

    printf(cfg->format, cfg->data);

    return 1;
}