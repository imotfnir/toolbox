#ifndef _PCIE_LIB_H_
#define _PCIE_LIB_H_

typedef struct pci_csr pci_csr;
typedef struct header header;
typedef struct pci_cap pci_cap;
typedef struct pci_ext_cap pci_ext_cap;

struct pci_csr {
    header header;
    pci_cap *cap;
    pci_ext_cap *ext_cap;
};

#pragma pack(push)
#pragma pack(1)

struct header {
    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t command;
    uint16_t status;
    uint8_t revision_id;
    uint8_t programming_interface;
    uint8_t sub_class_code;
    uint8_t base_class_code;
    uint8_t cache_line_size;
    uint8_t latency_timer;
    uint8_t header_type;
    uint8_t bist;
};

#pragma pack(pop)

#endif //_PCIE_LIB_H_