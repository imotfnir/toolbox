/***************************************************************************
***
***    Copyright (C) 2012-2018 Ufispace, Inc.
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
***      lpc_hal.h
***
***    DESCRIPTION :
***      LPC access
***
***    HISTORY :
***       - 2018/03/12, 08:53:23, Jeff Yen
***             File Creation
***
***************************************************************************/

#ifndef __LPC_HAL_H_
#define __LPC_HAL_H_

#include "efilib.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*==========================================================================
 *
 *      Library Inclusion Segment
 *
 *==========================================================================
 */

/*==========================================================================
 *
 *      Constant Definition Segment
 *
 *==========================================================================
 */
typedef enum {
    E_TYPE_SUCCESS                 = 0,
    E_TYPE_INVALID_CMD             = -11,     /* invalid command */
    E_TYPE_INVALID_CMD_FORMAT      = -12,     /* invalid command format */
    E_TYPE_INVALID_PARA            = -13,     /* invalid parameter */
    E_TYPE_INVALID_ADDR            = -14,     /* invalid address */
    E_TYPE_INVALID_DATA            = -15,
    E_TYPE_CTRL_C                  = -16,     /* interrupt */
    E_TYPE_INIT_FAIL               = -17,
    E_TYPE_ALLOC_MEM_FAIL          = -18,
    E_TYPE_UNSUPPORT               = -19,

    E_TYPE_IO_ERROR                = -200,     /* io error */
    E_TYPE_UNKNOWN_IO              = -201,
    E_TYPE_UNSUPPORT_IO            = -202,
    E_TYPE_DEV_BUSY                = -203,     /* device busy */
    E_TYPE_UNKNOWN_DEV             = -204,     /* unknown device */
    E_TYPE_DEV_MISMATCH            = -205,     /* device id mismatch */
    E_TYPE_UNSUPPORT_DEV           = -206,     /* unsupport this device */
    E_TYPE_IOCTL_FAILED            = -207,

    E_TYPE_DATA_MISMATCH           = -300,     /* compare data mismatch */
    E_TYPE_DATA_GET                = -301,     /* read data error */
    E_TYPE_DATA_SET                = -302,     /* write data error */
    E_TYPE_DATA_CLEAN              = -303,     /* clean data error */
    E_TYPE_REG_READ                = -304,     /* read reg error */
    E_TYPE_REG_WRITE               = -305,     /* write reg error */
    E_TYPE_CRC_ERROR               = -306,

    E_ERROR_TYPE_MAX               = -0x7FFFFFFF
} E_ERROR_TYPE;

//typedef unsigned int       UINT32;
//typedef unsigned short     UINT16;
//typedef unsigned char      UINT8;
//typedef int                INT32;
//typedef short              INT16;
//typedef char               INT8;
//typedef int                BOOL;

#define LPC_DEVICE_ADDR         0x600   /* CPLD on CPU board */
#define DNX_QAX_LPC_CPLD_ADDR   0x700   /* CPLD on Main board */

/*==========================================================================
 *
 *      Type and Structure Definition Segment
 *
 *==========================================================================
 */

 /*==========================================================================
 *
 *      External Funtion Segment
 *
 *==========================================================================
 */
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
 *      data - output register byte data
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
INT32 lpc_halRegGet(UINT32 addr, UINT32 *data);

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
 *      data - byte register data
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
INT32 lpc_halRegSet(UINT32 addr, UINT8 data);

#ifdef __cplusplus
}
#endif

#endif /* __LPC_HAL_H_ */
