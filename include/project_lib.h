#ifndef _PROJECT_LIB_H_
#define _PROJECT_LIB_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct semver semver;

typedef enum { broadwelld, skylaked, denverton, icelaked } cpu_codename;

typedef enum { emux } project_sku;

struct semver {
    uint32_t major;
    uint32_t minor;
    uint32_t patch;
};

cpu_codename get_cpu_codename();
bool is_me_recovery();
bool is_allow_switch_chip_select(rw_config cfg);
project_sku get_project_sku();

#endif //_PROJECT_LIB_H_
