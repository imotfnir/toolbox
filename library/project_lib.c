#include <debug_lib.h>
#include <io_lib.h>
#include <project_lib.h>
#include <register.h>

cpu_codename get_cpu_codename() {
    // LPC controller VID DID
    // ToDo change to mechanism for getting codename, use CPU ID or something
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
        me_dev_num = 0x18;
        break;
    default:
        break;
    }

    debug_print(DEBUG_DEBUG, "me_dev_num = 0x%x\n", me_dev_num);
    if((pci_read8(0x0, me_dev_num, 0x0, R_HECI_FIRMWARE_STATE)
        & B_HECI_FIRMWARE_CS)
       == V_HECI_RECOVERY)
        return true;

    return false;
}

bool is_need_to_block(rw_config cfg) {
    if(cfg.address != R_CPLD_CTRL1) { return false; }
    if((io_read8(R_CPLD_CTRL1) & B_BIOS_CHIP_SEL)
       == (cfg.data & B_BIOS_CHIP_SEL)) {
        return false;
    }
    if(is_me_recovery()) { return false; }
    return true;
}

void cpu_cpld_traversaler(cpu_cpld *self) {
    uint8_t value = 0;

    value = io_read8(0x600);
    self->revision.major = value & 0b11000000;
    self->revision.minor = value & 0b00111111;
    self->revision.patch = io_read8(0x6e0);

    value = io_read8(0x606);
    self->board_id = *(board_id *)&value;

    self->caterr = io_read8(0x607);
    self->wtd_timeout = io_read8(0x608);
    self->thermal_trip = io_read8(0x609);
    self->mem_event = io_read8(0x60A);
    self->boot_0x79_wa = io_read8(0x60D);

    self->traversal = cpu_cpld_traversaler;
    self->print = cpu_cpld_printer;

    return;
}

void cpu_cpld_printer(cpu_cpld *self) {
    debug_print(
        DEBUG_DEBUG, "self->revision.major = %d\n", self->revision.major);
    debug_print(
        DEBUG_DEBUG, "self->revision.minor = %d\n", self->revision.minor);
    debug_print(
        DEBUG_DEBUG, "self->revision.patch = %d\n", self->revision.patch);
    debug_print(
        DEBUG_DEBUG, "self->board_id.sku_id = %d\n", self->board_id.sku_id);
    debug_print(DEBUG_DEBUG,
                "self->board_id.hardware_revision = %d\n",
                self->board_id.hardware_revision);
    debug_print(
        DEBUG_DEBUG, "self->board_id.build_id = %d\n", self->board_id.build_id);
    debug_print(DEBUG_DEBUG, "self->caterr = %d\n", self->caterr);
    debug_print(DEBUG_DEBUG, "self->wtd_timeout = %d\n", self->wtd_timeout);
    debug_print(DEBUG_DEBUG, "self->thermal_trip = %d\n", self->thermal_trip);
    debug_print(DEBUG_DEBUG, "self->mem_event = %d\n", self->mem_event);
    debug_print(DEBUG_DEBUG, "self->boot_0x79_wa = %d\n", self->boot_0x79_wa);
    debug_print(DEBUG_DEBUG, "self->traversal = %s\n", self->traversal);
    debug_print(DEBUG_DEBUG, "self->print = %s\n", self->print);
}