#include <debug_lib.h>
#include <io_lib.h>
#include <project_lib.h>
#include <register.h>

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

bool is_me_recovery() {
    uint8_t me_dev_num;

    switch(get_cpu_codename()) {
    case broadwelld:
    case skylaked:
    case denverton:
        me_dev_num = 0x16;
        break;
    case icelaked:
        me_dev_num = 0x24;
        break;
    default:
        break;
    }

    if((pci_read8(0x0, me_dev_num, 0x0, R_HECI_FIRMWARE_STATE)
        & B_HECI_FIRMWARE_CS)
       == V_HECI_RECOVERY)
        return true;

    return false;
}

bool is_allow_switch_chip_select(rw_config cfg) {
    if(cfg.address != R_CPLD_CTRL1) return true;
    if((io_read8(R_CPLD_CTRL1) & B_BIOS_CHIP_SEL)
       == (cfg.data & B_BIOS_CHIP_SEL))
        return true;
    if(is_me_recovery()) return true;
    return false;
}
