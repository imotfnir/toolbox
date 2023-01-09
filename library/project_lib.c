#include <debug_lib.h>
#include <io_lib.h>
#include <project_lib.h>

cpu_codename get_cpu_codename() {
    // LPC controller VID DID
    switch(pci_read32(0x0, 0x1F, 0x0, 0x0)) {
    case 0x8C548086:
        return broadwelld;
    case 0xA1C88086:
        return skylaked;
    case 0x19DC8086:
        return denverton;
    case 0x18DC8086:
        return icelaked;
    default:
        debug_print(DEBUG_ERROR, "fail to get cpu codename");
        FATAL;
    }
}
