/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*
** $Id: //Department/DaVinci/BRANCHES/MT6620_WIFI_DRIVER_V1_2/include/mgmt/cnm_timer.h#1 $
*/

/*! \file   cnm_timer.h
    \brief  Declaration of timer obj and related timer macro for setup time out
            event.

    In this file we declare the timer object and provide several macro for
    Protocol functional blocks to setup their own time out event.
*/

/*******************************************************************************
* Copyright (c) 2009 MediaTek Inc.
*
* All rights reserved. Copying, compilation, modification, distribution
* or any other use whatsoever of this material is strictly prohibited
* except in accordance with a Software License Agreement with
* MediaTek Inc.
********************************************************************************
*/

/*******************************************************************************
* LEGAL DISCLAIMER
*
* BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND
* AGREES THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK
* SOFTWARE") RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE
* PROVIDED TO BUYER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY
* DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE
* ANY WARRANTY WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY
* WHICH MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK
* SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY
* WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE
* FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION OR TO
* CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
* BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
* LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL
* BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT
* ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY
* BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
* THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
* WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT
* OF LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING
* THEREOF AND RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN
* FRANCISCO, CA, UNDER THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE
* (ICC).
********************************************************************************
*/

/*
** $Log: cnm_timer.h $
 *
 * 02 09 2011 cp.wu
 * [WCXRP00000430] [MT6620 Wi-Fi][Firmware][Driver] Create V1.2 branch for MT6620E1 and MT6620E3
 * create V1.2 driver branch based on label MT6620_WIFI_DRIVER_V1_2_110209_1031 
 * with BOW and P2P enabled as default
 *
 * 09 03 2010 kevin.huang
 * NULL
 * Refine #include sequence and solve recursive/nested #include issue
 *
 * 07 08 2010 cp.wu
 * 
 * [WPD00003833] [MT6620 and MT5931] Driver migration - move to new repository.
 *
 * 06 08 2010 cp.wu
 * [WPD00003833][MT6620 and MT5931] Driver migration 
 * cnm_timer has been migrated.
 *
 * 06 08 2010 cp.wu
 * [WPD00003833][MT6620 and MT5931] Driver migration 
 * add hem_mbox.c and cnm_mem.h (but disabled some feature) for further migration
 *
 * 06 07 2010 cp.wu
 * [WPD00003833][MT6620 and MT5931] Driver migration 
 * merge cnm_scan.h and hem_mbox.h
 *
 * 06 07 2010 cp.wu
 * [WPD00003833][MT6620 and MT5931] Driver migration 
 * merge wifi_var.h, precomp.h, cnm_timer.h (data type only)
 *
 * 06 04 2010 george.huang
 * [BORA00000678][MT6620]WiFi LP integration 
 * [PM] Support U-APSD for STA mode
 *
 * 04 24 2010 cm.chang
 * [BORA00000018]Integrate WIFI part into BORA for the 1st time 
 * Return timer token back to COS when entering wait off state
 *
 * 01 08 2010 cm.chang
 * [BORA00000018]Integrate WIFI part into BORA for the 1st time
 * Support longer timeout interval to 45 days from 65secu1rwduu`wvpghlqg|fh+fmdkb
 *
 * 01 06 2010 cm.chang
 * [BORA00000018]Integrate WIFI part into BORA for the 1st time
 * Fix system time is 32KHz instead of 1ms
 *
 * Nov 23 2009 mtk01088
 * [BORA00000476] [Wi-Fi][firmware] Add the security module initialize code
 * add the copy time function
 *
 * Nov 5 2009 mtk01461
 * [BORA00000018] Integrate WIFI part into BORA for the 1st time
 * Fix LINT warnning
 *
 * Oct 28 2009 mtk01104
 * [BORA00000018] Integrate WIFI part into BORA for the 1st time
 *
**
*/

#ifndef _CNM_TIMER_H
#define _CNM_TIMER_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#undef MSEC_PER_SEC
#define MSEC_PER_SEC                    1000
#undef USEC_PER_MSEC
#define USEC_PER_MSEC                   1000
#define USEC_PER_TU                     1024 /* microsecond */

#define MSEC_PER_MIN                    (60 * MSEC_PER_SEC)


#define MGMT_MAX_TIMEOUT_INTERVAL       ((UINT_32)0x7fffffff)


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef VOID (*PFN_MGMT_TIMEOUT_FUNC)(P_ADAPTER_T, UINT_32);

typedef struct _TIMER_T {
    LINK_ENTRY_T            rLinkEntry;
    OS_SYSTIME              rExpiredSysTime;
    UINT_16                 u2Minutes;
    UINT_16                 u2Reserved;
    UINT_32                 u4Data;
    PFN_MGMT_TIMEOUT_FUNC   pfMgmtTimeOutFunc;
} TIMER_T, *P_TIMER_T;

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
/* Check if time "a" is before time "b" */
/* In 32-bit variable, 0x00000001~0x7fffffff -> positive number,
 *                     0x80000000~0xffffffff -> negative number
 */
#define TIME_BEFORE_64bit(a,b)       (a < b)

#define TIME_BEFORE(a,b)        ((UINT_32)((UINT_32)(a) - (UINT_32)(b)) > 0x7fffffff)

/* #define TIME_BEFORE(a,b)        ((INT_32)((INT_32)(b) - (INT_32)(a)) > 0)
 * may cause UNexpect result between Free build and Check build for WinCE
 */

#define TIME_AFTER(a,b)         TIME_BEFORE(b,a)

#define SYSTIME_TO_SEC(_systime)            ((_systime) / KAL_HZ)
#define SEC_TO_SYSTIME(_sec)                ((_sec) * KAL_HZ)


/* The macros to convert second & millisecond */
#define MSEC_TO_SEC(_msec)                  ((_msec) / MSEC_PER_SEC)
#define SEC_TO_MSEC(_sec)                   ((UINT_32)(_sec) * MSEC_PER_SEC)


/* The macros to convert millisecond & microsecond */
#define USEC_TO_MSEC(_usec)                 ((_usec) / USEC_PER_MSEC)
#define MSEC_TO_USEC(_msec)                 ((UINT_32)(_msec) * USEC_PER_MSEC)


/* The macros to convert TU & microsecond, TU & millisecond */
#define TU_TO_USEC(_tu)                     ((_tu) * USEC_PER_TU)
#define TU_TO_MSEC(_tu)                     USEC_TO_MSEC( TU_TO_USEC(_tu) )


/* The macros to convert TU & & OS system time, round up by 0.5 */
#define TU_TO_SYSTIME(_tu)                  MSEC_TO_SYSTIME( TU_TO_MSEC(_tu) )
#define SYSTIME_TO_TU(_systime)             \
    ((SYSTIME_TO_USEC(_systime) + ((USEC_PER_TU / 2) - 1)) / USEC_PER_TU)


/* The macros to convert OS system time & microsecond */
#define SYSTIME_TO_USEC(_systime)           (SYSTIME_TO_MSEC(_systime) * USEC_PER_MSEC)


/* The macro to get the current OS system time */
#define GET_CURRENT_SYSTIME(_systime_p)     {*(_systime_p) = kalGetTimeTick();}

/* The macro to copy the system time */
#define COPY_SYSTIME(_destTime, _srcTime)   (_destTime) = (_srcTime)

/* The macro to get the system time difference between t1 and t2 (t1 - t2) */
/* #define GET_SYSTIME_DIFFERENCE(_time1, _time2, _diffTime) \
        (_diffTime) = (_time1) - (_time2) */

/* The macro to check for the expiration, if TRUE means _currentTime >= _expirationTime */
#define CHECK_FOR_EXPIRATION(_currentTime, _expirationTime) \
        ( ((UINT_32)(_currentTime) - (UINT_32)(_expirationTime)) <= 0x7fffffffUL)

/* The macro to check for the timeout */
#define CHECK_FOR_TIMEOUT(_currentTime, _timeoutStartingTime, _timeout) \
    CHECK_FOR_EXPIRATION((_currentTime), ((_timeoutStartingTime) + (_timeout)))

/* The macro to set the expiration time with a specified timeout *//* Watch out for round up.*/
#define SET_EXPIRATION_TIME(_expirationTime, _timeout) \
        { \
            GET_CURRENT_SYSTIME(&(_expirationTime)); \
            (_expirationTime) += (OS_SYSTIME)(_timeout); \
        }

#define timerRenewTimer(adapter,tmr,interval) \
        timerStartTimer(adapter,tmr,interval,(tmr)->function,(tmr)->data)

#define MGMT_INIT_TIMER(_adapter_p, _timer, _callbackFunc) \
        timerInitTimer(_adapter_p, &(_timer), (UINT_32)(_callbackFunc))


/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID
cnmTimerInitialize (
    IN P_ADAPTER_T prAdapter
    );

VOID
cnmTimerDestroy (
    IN P_ADAPTER_T prAdapter
    );

VOID
cnmTimerInitTimer (
    IN P_ADAPTER_T              prAdapter,
    IN P_TIMER_T                prTimer,
    IN PFN_MGMT_TIMEOUT_FUNC    pfFunc,
    IN UINT_32                  u4Data
    );

VOID
cnmTimerStopTimer (
    IN P_ADAPTER_T              prAdapter,
    IN P_TIMER_T                prTimer
    );

VOID
cnmTimerStartTimer (
    IN P_ADAPTER_T              prAdapter,
    IN P_TIMER_T                prTimer,
    IN UINT_32                  u4TimeoutMs
    );

VOID
cnmTimerDoTimeOutCheck (
    IN P_ADAPTER_T              prAdapter
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
__KAL_INLINE__
INT_32
timerPendingTimer (
    IN P_TIMER_T prTimer
    )
{
    ASSERT(prTimer);

    return prTimer->rLinkEntry.prNext != NULL;
}

#endif /* _CNM_TIMER_H */


