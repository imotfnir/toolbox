/***************************************************************************
***
***    Copyright (C) 2012-2019 UfiSpace, Inc.
***    All Rights Reserved.
***    No portions of this material shall be reproduced in any form without
***    the written permission of Ufispace, Inc.
***
***    All information contained in this document is Ufispace, Inc. company
***    private, proprietary, and trade secret property and are protected by
***    international intellectual property laws and treaties.
***
****************************************************************************
***
***    FILE NAME :
***      lpc_hal.c
***
***    DESCRIPTION :
***      LPC access
***
***    HISTORY :
***       - 2018/03/12, 08:53:23, Jeff Yen
***             File Creation
***
***************************************************************************/
/*==========================================================================
 *
 *      Library Inclusion Segment
 *
 *==========================================================================
 */
/* System Library */
#include <stdio.h>
#include <sys/io.h>

#include "lpc_hal.h"

/*--------------------------------------------------------------------------
 *
 *  FUNCTION NAME :
 *      lpc_halRegGet
 *
 *  DESCRIPTION :
 *      get register value of LPC device
 *
 *  INPUT :
 *      addr - io register address
 *
 *  OUTPUT :
 *      data - output register data
 *
 *  RETURN :
 *      E_TYPE_SUCCESS  - action successfully
 *      Other - fail to action
 *
 *  COMMENT :
 *      none
 *
 *--------------------------------------------------------------------------
 */
INT32 lpc_halRegGet(UINT32 addr, UINT32 *data)
{
    UINT32 getValue;

    if (iopl(3)) {
        printf("lpc_halRegSet: iopl() enable failed\n");
        return E_TYPE_IO_ERROR;
    }

    if (ioperm(addr, 4, 1)) {
        printf("lpc_halRegSet: ioperm() enable failed\n");
        return E_TYPE_IO_ERROR;
    }

//    getValue = inb(addr);
    getValue = inl(addr);

    if (ioperm(addr, 4, 0)) {
        printf("lpc_halRegSet: ioperm() disable failed\n");
        return E_TYPE_IO_ERROR;
    }

    if (iopl(0)) {
        printf("lpc_halRegSet: iopl() disable failed\n");
        return E_TYPE_IO_ERROR;
    }

    *data = getValue;

    return E_TYPE_SUCCESS;
}

/*--------------------------------------------------------------------------
 *
 *  FUNCTION NAME :
 *      lpc_halRegSet
 *
 *  DESCRIPTION :
 *      set register value to LPC device
 *
 *  INPUT :
 *      addr - io register address
 *      data - register data
 *
 *  OUTPUT :
 *      none
 *
 *  RETURN :
 *      E_TYPE_SUCCESS  - action successfully
 *      Other - fail to action
 *
 *  COMMENT :
 *      none
 *
 *--------------------------------------------------------------------------
 */
INT32 lpc_halRegSet(UINT32 addr, UINT8 data)
{
    UINT8 setValue = data;

    if (iopl(3)) {
        printf("lpc_halRegSet: iopl() enable failed\n");
        return E_TYPE_IO_ERROR;
    }

    if (ioperm(addr, 4, 1)) {
        printf("lpc_halRegSet: ioperm() enable failed\n");
        return E_TYPE_IO_ERROR;
    }

    outb(setValue, addr);

    if (ioperm(addr, 4, 0)) {
        printf("lpc_halRegSet: ioperm() disable failed\n");
        return E_TYPE_IO_ERROR;
    }

    if (iopl(0)) {
        printf("lpc_halRegSet: iopl() disable failed\n");
        return E_TYPE_IO_ERROR;
    }

    return E_TYPE_SUCCESS;
}
