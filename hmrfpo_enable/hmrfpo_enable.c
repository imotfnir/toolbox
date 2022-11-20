#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include "HeciCoreLib.h"
#include "MeAccess.h"
#include "PciRwLibrary.h"
#include "Sps.h"
#include "SpsSmm.h"
#include "debug_lib.h"
#include "efilib.h"
#include "hmrfpo_enable.h"
#include "lpc_hal.h"

EFI_STATUS
HeciReqHmrfpoEnable(
    IN UINT64 Nonce) {
    UINT32 RspLen;
    EFI_STATUS Status;

    union {
        HECI_MSG_HMRFPO_ENABLE_REQ Req;
        HECI_MSG_HMRFPO_ENABLE_RSP Rsp;
    } HeciMsg;

    printf("Sending HMRFPO_ENABLE, HFSTS1 = 0x%08X\n", HeciPciRead32(SPS_REG_MEFS1));

    // Construct HMRFPO_ENABLE request message
    memset(&HeciMsg, 0, sizeof(HeciMsg));

    HeciMsg.Req.Mkhi.Data = HECI_MSG_ENABLE_REQ_MKHI_HDR;
    HeciMsg.Req.Nonce = Nonce;

    RspLen = sizeof(HeciMsg.Rsp);
    Status = HeciSendwAck(HECI1_DEVICE, (UINT32 *)&HeciMsg.Req, sizeof(HeciMsg.Req), &RspLen, SPS_CLIENTID_BIOS, SPS_CLIENTID_ME_MKHI);

    printf("HFSTS1 = 0x%08X\n", HeciPciRead32(SPS_REG_MEFS1));

    if(EFI_ERROR(Status)) {
        debug(DEBUG_ERROR, "HMRFPO_ENABLE sending failed, Status = %llx\n", Status);
        return Status;
    }

    if(HeciMsg.Rsp.Mkhi.Data != HECI_MSG_ENABLE_RSP_MKHI_HDR) {
        debug(DEBUG_ERROR, "HMRFPO_ENABLE response Invalid, MKHI = 0x%08X)\n", HeciMsg.Rsp.Mkhi.Data);
        return EFI_UNSUPPORTED;
    }

    if(HeciMsg.Rsp.Status != 0) {
        debug(DEBUG_ERROR, "HMRFPO_ENABLE command refused, reason = %d)\n", HeciMsg.Rsp.Status);
        return EFI_UNSUPPORTED;
    }

    printf("HMRFPO_ENABLE command success\n");
    printf("==================================================================\n");
    printf("\E[1;31;40m");
    printf("Do power cycle instead of \"reboot\" if HMRFPO_ENABLE command success.\n");
    printf("System will become abnormal if you do \"reboot\" only!!!\n");
    printf("\E[0m");

    return EFI_SUCCESS;
}

int main(void) {
    UINT64 Nonce;
    UINT32 RCBA;
    UINT32 Data32;
    UINT8 StratchBus;
    UINTN i;
    int fd;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    fflush(stdout);

    InitPlatformInfo();

    // Broadwell-DE
    if(PciRead32(0x0, 0x1F, 0x0, 0x0) == 0x8C548086) {
        printf("Chipset: Broadwell-DE\n");
        RCBA = PciRead32(0x0, 0x1F, 0x0, 0xF0) & 0xFFFFC000;
        Data32 = MmioRead32(RCBA + 0x3428);
        MmioWrite32(RCBA + 0x3428, Data32 & 0xFFFFFFFD);

        StratchBus = PciRead8(0x0, 0x5, 0x0, 0x109);
        Nonce = ((UINT64)PciRead32(StratchBus, 0x10, 0x7, 0x54) << 32) | PciRead32(StratchBus, 0x10, 0x7, 0x50);
        HeciReqHmrfpoEnable(Nonce);
    }
    // Skylake-D
    else if(PciRead32(0x0, 0x1F, 0x0, 0x0) == 0xA1C88086) {
        printf("Chipset: Skylake-D\n");
        // Disable HECI MSI
        PciWrite8(0x0, 0x16, 0x0, 0x8E, PciRead8(0x0, 0x16, 0x0, 0x8E) & 0xFE);
        // Get Nonce and send hmfpo_enable command
        Nonce = ((UINT64)PciRead32(0x0, 0x8, 0x2, 0xB0) << 32) | PciRead32(0x0, 0x8, 0x2, 0xAC);
        debug(DEBUG_INFO, "Nonce = 0x%08llx, %s, %d\n", Nonce, __FUNCTION__, __LINE__);
        HeciReqHmrfpoEnable(Nonce);
    }
    // Denverton
    else if(PciRead32(0x0, 0x1F, 0x0, 0x0) == 0x19DC8086) {
        printf("Chipset: Denverton\n");
        Nonce = 0;
        lpc_halRegGet(0xE3FC, &Data32);
        Nonce = (Nonce | Data32) << 32;
        lpc_halRegGet(0xE3F8, &Data32);
        Nonce = (Nonce | Data32);
        debug(DEBUG_INFO, "Nonce = 0x%08llx, %s, %d\n", Nonce, __FUNCTION__, __LINE__);
        HeciReqHmrfpoEnable(Nonce);
    }
    // Icelake-D
    else if(PciRead32(0x0, 0x1F, 0x0, 0x0) == 0x18DC8086) {
        printf("Chipset: Icelake-D\n");
        Nonce = 0;
        lpc_halRegGet(0x6FC, &Data32);
        Nonce = (Nonce | Data32) << 32;
        lpc_halRegGet(0x6F8, &Data32);
        Nonce = (Nonce | Data32);
        debug(DEBUG_INFO, "Nonce = 0x%08llx, %s, %d\n", Nonce, __FUNCTION__, __LINE__);
        HeciReqHmrfpoEnable(Nonce);
    }
    // Unknown chipset
    else {
        printf("Unknown chipset!!!!!\n");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}
