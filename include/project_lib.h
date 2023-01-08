#ifndef _PROJECT_LIB_H_
#define _PROJECT_LIB_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct semver semver;

typedef enum { broadwelld, skyladed, denverton, icelaked } cpu_codename;

typedef enum { emux } project_sku;

struct {
    uint32 major;
    uint32 minor;
    uint32 patch;
} semver;

cpu_codename get_cpu_codename();

project_sku get_project_sku();

#endif //_PROJECT_LIB_H_
