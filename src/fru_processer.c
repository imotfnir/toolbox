#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long UINT64;
typedef long long INT64;
typedef unsigned int UINT32;
typedef int INT32;
typedef unsigned short UINT16;
typedef unsigned short CHAR16;
typedef short INT16;
typedef unsigned char BOOLEAN;
typedef unsigned char UINT8;
typedef char CHAR8;
typedef signed char INT8;
typedef UINT64 UINTN;

typedef struct TLV TLV;
typedef struct EEPROM_VENDOR_EXTENSION_FIELD_STRUCT
    EEPROM_VENDOR_EXTENSION_FIELD_STRUCT;
typedef struct EEPROM_FIELD EEPROM_FIELD;

struct TLV {
    UINT8 Type;
    UINT8 Length;
    UINT8 Value[256];
};

struct EEPROM_VENDOR_EXTENSION_FIELD_STRUCT {
    UINT8 UfiSpacePen[4];
    CHAR8 CpuPcbaSerialNumber[256];
    CHAR8 MainboardPcbaSerialNumber[256];
    CHAR8 FanPcbaSerialNumber[256];
    CHAR8 BmcPcbaSerialNumber[256];
};

struct EEPROM_FIELD {
    TLV ProductName;
    TLV PartNumber;
    TLV SerialNumber;
    TLV Mac;
    TLV ManufactureDate;
    TLV DeviceVersion;
    TLV LabelRevision;
    TLV PlatformName;
    TLV OnieVersion;
    TLV NumberOfMac;
    TLV Manufacturer;
    TLV CountryCode;
    TLV Vendor;
    TLV DiagVersion;
    TLV ServiceTag;
    EEPROM_VENDOR_EXTENSION_FIELD_STRUCT VendorExtension;
    TLV Crc32;
};

typedef enum {
    Reserved1 = 0x00,
    ProductName = 0x21,
    PartNumber = 0x22,
    SerialNumber = 0x23,
    Mac = 0x24,
    ManufactureDate = 0x25,
    DeviceVersion = 0x26,
    LabelRevision = 0x27,
    PlatformName = 0x28,
    OnieVersion = 0x29,
    NumberOfMac = 0x2A,
    Manufacturer = 0x2B,
    CountryCode = 0x2C,
    Vendor = 0x2D,
    DiagVersion = 0x2E,
    ServiceTag = 0x2F,
    VendorExtension = 0xFD,
    Crc32 = 0xFE,
    Reserved2 = 0xFF,
} EEPROM_FIELD_TYPE;

typedef enum {
    CpuPcbaSerialNumber = 0x51,
    MainboardPcbaSerialNumber = 0x52,
    FanPcbaSerialNumber = 0x53,
    BmcPcbaSerialNumber = 0x54,
} EEPROM_VENDOR_EXTENSION_FIELD_TYPE;

#define TO_STR(str) (#str)
#define PRINT_IFNOT_NULL(str, len)                                            \
    do {                                                                      \
        if((str) != NULL) {                                                   \
            printf(#str ": %.*s\n", len, str);                                \
        } else {                                                              \
            printf(#str ": NULL");                                            \
        }                                                                     \
                                                                              \
    } while(0);

UINTN PrintEepromField(EEPROM_FIELD Fru);
UINTN PrintEepromField(EEPROM_FIELD Fru);
UINTN FruDataProcesser(UINT8 *RawData, UINTN RawDataLen, EEPROM_FIELD *Fru);

UINTN PrintEepromField(EEPROM_FIELD Fru) {
    printf("ProductName: %s\n", Fru.ProductName.Value);
    printf("PartNumber: %s\n", Fru.PartNumber.Value);
    printf("SerialNumber: %s\n", Fru.SerialNumber.Value);
    printf("Mac: %02X-%02X-%02X-%02X-%02X-%02X\n",
           Fru.Mac.Value[0],
           Fru.Mac.Value[1],
           Fru.Mac.Value[2],
           Fru.Mac.Value[3],
           Fru.Mac.Value[4],
           Fru.Mac.Value[5]);
    printf("ManufactureDate: %s\n", Fru.ManufactureDate.Value);
    printf("DeviceVersion: %d\n", Fru.DeviceVersion.Value[0]);
    printf("LabelRevision: %s\n", Fru.LabelRevision.Value);
    printf("PlatformName: %s\n", Fru.PlatformName.Value);
    printf("OnieVersion: %s\n", Fru.OnieVersion.Value);
    printf("NumberOfMac: %02d%02d\n",
           Fru.NumberOfMac.Value[0],
           Fru.NumberOfMac.Value[1]);
    printf("Manufacturer: %s\n", Fru.Manufacturer.Value);
    printf("CountryCode: %s\n", Fru.CountryCode.Value);
    printf("Vendor: %s\n", Fru.Vendor.Value);
    printf("DiagVersion: %s\n", Fru.DiagVersion.Value);
    printf("ServiceTag: %s\n", Fru.ServiceTag.Value);
    printf("VendorExtension: %s\n", Fru.ServiceTag.Value);
    printf("Crc32: 0x%02x%02x%02x%02x\n",
           Fru.ServiceTag.Value[0],
           Fru.ServiceTag.Value[1],
           Fru.ServiceTag.Value[2],
           Fru.ServiceTag.Value[3]);

    return 0;
}

UINTN FruDataProcesser(UINT8 *RawData, UINTN RawDataLen, EEPROM_FIELD *Fru) {
    UINTN TypeFinder = 0;
    UINT8 TlvType = 0;
    UINT8 TlvLen = 0;

    while(TypeFinder < RawDataLen) {
        TlvType = RawData[TypeFinder];
        TlvLen = RawData[TypeFinder + 1];

        switch(TlvType) {
        case ProductName:
            memcpy(&Fru->ProductName, &RawData[TypeFinder], TlvLen + 2);
            break;
        case PartNumber:
            memcpy(&Fru->PartNumber, &RawData[TypeFinder], TlvLen + 2);
            break;
        case SerialNumber:
            memcpy(&Fru->SerialNumber, &RawData[TypeFinder], TlvLen + 2);
            break;
        case Mac:
            memcpy(&Fru->Mac, &RawData[TypeFinder], TlvLen + 2);
            break;
        case ManufactureDate:
            memcpy(&Fru->ManufactureDate, &RawData[TypeFinder], TlvLen + 2);
            break;
        case DeviceVersion:
            memcpy(&Fru->DeviceVersion, &RawData[TypeFinder], TlvLen + 2);
            break;
        case LabelRevision:
            memcpy(&Fru->LabelRevision, &RawData[TypeFinder], TlvLen + 2);
            break;
        case PlatformName:
            memcpy(&Fru->PlatformName, &RawData[TypeFinder], TlvLen + 2);
            break;
        case OnieVersion:
            memcpy(&Fru->OnieVersion, &RawData[TypeFinder], TlvLen + 2);
            break;
        case NumberOfMac:
            memcpy(&Fru->NumberOfMac, &RawData[TypeFinder], TlvLen + 2);
            break;
        case Manufacturer:
            memcpy(&Fru->Manufacturer, &RawData[TypeFinder], TlvLen + 2);
            break;
        case CountryCode:
            memcpy(&Fru->CountryCode, &RawData[TypeFinder], TlvLen + 2);
            break;
        case Vendor:
            memcpy(&Fru->Vendor, &RawData[TypeFinder], TlvLen + 2);
            break;
        case DiagVersion:
            memcpy(&Fru->DiagVersion, &RawData[TypeFinder], TlvLen + 2);
            break;
        case ServiceTag:
            memcpy(&Fru->ServiceTag, &RawData[TypeFinder], TlvLen + 2);
            break;
        case VendorExtension:
            memcpy(&Fru->VendorExtension, &RawData[TypeFinder], TlvLen + 2);
            break;
        case Crc32:
            memcpy(&Fru->Crc32, &RawData[TypeFinder], TlvLen + 2);
            break;
        default:
            break;
        }

        TypeFinder += 2 + TlvLen;
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    EEPROM_FIELD Fru = { 0x0 };
    UINT8 FruRaw[] = {
        0x54, 0x6c, 0x76, 0x49, 0x6e, 0x66, 0x6f, 0x00, 0x01, 0x00, 0xfa, 0x21,
        0x0c, 0x53, 0x39, 0x37, 0x30, 0x30, 0x2d, 0x35, 0x33, 0x44, 0x58, 0x2d,
        0x4a, 0x22, 0x0e, 0x53, 0x39, 0x37, 0x30, 0x30, 0x2d, 0x35, 0x33, 0x44,
        0x58, 0x2d, 0x4a, 0x42, 0x31, 0x23, 0x10, 0x57, 0x44, 0x58, 0x31, 0x39,
        0x37, 0x37, 0x37, 0x30, 0x30, 0x30, 0x30, 0x34, 0x2d, 0x50, 0x31, 0x24,
        0x06, 0xe8, 0xc5, 0x7a, 0x07, 0xe8, 0x00, 0x25, 0x13, 0x30, 0x37, 0x2f,
        0x33, 0x30, 0x2f, 0x32, 0x30, 0x31, 0x39, 0x20, 0x31, 0x38, 0x3a, 0x34,
        0x32, 0x3a, 0x34, 0x34, 0x26, 0x01, 0x00, 0x27, 0x03, 0x4e, 0x2f, 0x41,
        0x28, 0x1d, 0x78, 0x38, 0x36, 0x5f, 0x36, 0x34, 0x2d, 0x75, 0x66, 0x69,
        0x73, 0x70, 0x61, 0x63, 0x65, 0x5f, 0x73, 0x39, 0x37, 0x30, 0x30, 0x5f,
        0x35, 0x33, 0x64, 0x78, 0x2d, 0x72, 0x37, 0x29, 0x0a, 0x32, 0x30, 0x31,
        0x37, 0x2e, 0x30, 0x38, 0x76, 0x30, 0x36, 0x2a, 0x02, 0x01, 0x00, 0x2b,
        0x09, 0x55, 0x66, 0x69, 0x20, 0x53, 0x70, 0x61, 0x63, 0x65, 0x2c, 0x02,
        0x43, 0x4e, 0x2d, 0x09, 0x55, 0x66, 0x69, 0x20, 0x53, 0x70, 0x61, 0x63,
        0x65, 0x2e, 0x05, 0x30, 0x2e, 0x36, 0x2e, 0x36, 0x2f, 0x03, 0x4e, 0x2f,
        0x41, 0xfd, 0x48, 0x00, 0x00, 0xcc, 0x21, 0x51, 0x0b, 0x57, 0x43, 0x53,
        0x4e, 0x39, 0x32, 0x37, 0x30, 0x30, 0x34, 0x56, 0x52, 0x0e, 0x57, 0x43,
        0x55, 0x4e, 0x39, 0x32, 0x38, 0x30, 0x30, 0x32, 0x4d, 0x2d, 0x50, 0x31,
        0x53, 0x0b, 0x57, 0x43, 0x33, 0x4e, 0x39, 0x31, 0x37, 0x30, 0x30, 0x31,
        0x36, 0x54, 0x0b, 0x57, 0x42, 0x4b, 0x4e, 0x39, 0x32, 0x37, 0x30, 0x30,
        0x31, 0x52, 0x55, 0x0b, 0x57, 0x42, 0x4b, 0x4e, 0x39, 0x32, 0x37, 0x30,
        0x30, 0x31, 0x52, 0xfe, 0x04, 0x26, 0xe5, 0x46, 0x1c, 0x04
    };

    UINT8 *FruData = &FruRaw[0xB];
    UINTN FruLen = FruLen = (FruRaw[0x9] << 8) | FruRaw[0xA];

    FruDataProcesser(FruData, FruLen, &Fru);
    PrintEepromField(Fru);

    return 0;
}
