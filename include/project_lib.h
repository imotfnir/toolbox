#ifndef _PROJECT_LIB_H_
#define _PROJECT_LIB_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct semver semver;
typedef struct board_id board_id;
typedef struct cpu_cpld cpu_cpld;
typedef void (*cpu_cpld_traversal)(cpu_cpld *self);
typedef void (*cpu_cpld_print)(cpu_cpld *self);

typedef enum { broadwelld, skylaked, denverton, icelaked } cpu_codename;

typedef enum { emux } project_sku;

typedef enum { proto = 0, alpha, beta, pvt } hardware_revision;

struct semver {
    uint32_t major;
    uint32_t minor;
    uint32_t patch;
};

struct board_id {
    uint8_t build_id : 2;
    uint8_t hardware_revision : 2;
    uint8_t sku_id : 4;
};

void cpu_cpld_traversaler(cpu_cpld *self);
void cpu_cpld_printer(cpu_cpld *self);

struct cpu_cpld {
    semver revision;
    uint8_t status1;
    board_id board_id;
    uint8_t caterr;
    uint8_t wtd_timeout;
    uint8_t thermal_trip;
    uint8_t mem_event;
    uint8_t boot_0x79_wa;

    uint8_t cpld_base;
    cpu_cpld_traversal traversal;
    cpu_cpld_print print;
};

cpu_codename get_cpu_codename();
bool is_me_recovery();
bool is_need_to_block(rw_config cfg);
project_sku get_project_sku();

#endif //_PROJECT_LIB_H_
