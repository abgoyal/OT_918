/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/hal.c#2 $
*/

/*! \file   "hal.c"
    \brief  This file includes the hal functions for specific chip.

    Detail description.
*/

/*******************************************************************************
* Copyright (c) 2007 MediaTek Inc.
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
** $Log: hal.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\143 2009-09-03 11:38:07 GMT mtk01088
**  adding the 802.11 data path for linux
**  \main\maintrunk.MT5921\142 2009-08-18 22:56:33 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\141 2009-08-14 16:58:42 GMT MTK01090
**  Add support for MT5921 ECO IC
**  \main\maintrunk.MT5921\140 2009-08-06 16:44:08 GMT mtk01090
**  Use GPIO0 and GPIO2 to control antenna switch and remove obsolete compile flag CFG_SUPPORT_SINGLE_ANTENNA
**  \main\maintrunk.MT5921\139 2009-07-09 18:57:19 GMT mtk01088
**  move the wapi code to wpi.c
**  \main\maintrunk.MT5921\138 2009-07-08 14:55:20 GMT mtk01088
**  rename the wapi variable to mtk nameing style
**  \main\maintrunk.MT5921\137 2009-07-08 10:51:14 GMT mtk01088
**  adding the key error skip for wapi mode at SDIO path
**  \main\maintrunk.MT5921\136 2009-07-07 11:53:30 GMT mtk01088
**  avoid compiling warning
**  \main\maintrunk.MT5921\135 2009-07-07 10:34:48 GMT mtk01088
**  fixing the hw header translation enable if code
**  \main\maintrunk.MT5921\134 2009-07-06 21:41:57 GMT mtk01088
**  fixed the compiling error at linux
**  \main\maintrunk.MT5921\133 2009-07-06 20:49:40 GMT mtk01088
**  adding the to to tx/rx wpi frame at hal
**  \main\maintrunk.MT5921\132 2009-05-14 19:47:05 GMT mtk01104
**  Add function halEepromRecall()
**  \main\maintrunk.MT5921\131 2009-02-02 14:26:50 GMT mtk01084
**  modify continuous polling mechanism, with not to do extra poll when no WiFi downlink traffic
**  \main\maintrunk.MT5921\130 2009-01-22 13:00:38 GMT mtk01088
**  fixed the wlan table assigned code
**  \main\maintrunk.MT5921\129 2009-01-11 23:30:09 GMT mtk01461
**  Fix compiling error if remove CFG_TX_DBG_TFCB_CHKSUM
**  \main\maintrunk.MT5921\128 2009-01-05 10:16:24 GMT mtk01725
**  Add a checking code in RX Fill RFB for checking wanted packet when pattern search SLT is enabled.
**  \main\maintrunk.MT5921\127 2008-12-08 16:15:59 GMT mtk01461
**  Add u2ValidBufSize in halTxTfcbs() and halRxFillRFB() for kalDevPortWrite/Read in sdio.c
**  \main\maintrunk.MT5921\126 2008-11-28 11:08:24 GMT mtk01088
**  fixed the lint warning
**  \main\maintrunk.MT5921\125 2008-10-30 11:33:42 GMT mtk01088
**  update code for lint
**  \main\maintrunk.MT5921\124 2008-10-29 10:57:44 GMT mtk01088
**  update the code style for lint warning
**  \main\maintrunk.MT5921\123 2008-10-13 10:25:34 GMT mtk01461
**  Remove define of minimum life time & update halRxFillRFB for coding rule
**  \main\maintrunk.MT5921\122 2008-09-24 10:58:19 GMT mtk01084
**  add single antenna related support function
**  \main\maintrunk.MT5921\121 2008-09-05 17:25:04 GMT mtk01461
**  Update Driver for Code Review
**  \main\maintrunk.MT5921\120 2008-09-02 22:21:34 GMT mtk01461
**  Revise TX Aggregation to support TX Fragmentation
**  \main\maintrunk.MT5921\119 2008-09-02 11:44:55 GMT mtk01461
**  Update driver for code review
**  \main\maintrunk.MT5921\118 2008-08-21 00:31:05 GMT mtk01461
**  \main\maintrunk.MT5921\117 2008-08-18 20:12:42 GMT mtk01088
**  add function declaration and add some assert check
**  \main\maintrunk.MT5921\116 2008-08-16 13:10:15 GMT mtk01088
**  code review
**  \main\maintrunk.MT5921\115 2008-07-29 10:13:13 GMT mtk01461
**  Remove kalMemZero for SDIO TX Aggregation
**  \main\maintrunk.MT5921\114 2008-07-25 20:08:45 GMT mtk01461
**  Remove union for removing __KAL_ATTRIB_PACKED__ from HW_TFCB_T
**  \main\maintrunk.MT5921\113 2008-07-25 17:01:35 GMT mtk01461
**  Add TX FIFO Aggregate Function to improve TX throughput
**  \main\maintrunk.MT5921\112 2008-07-22 10:04:19 GMT mtk01084
**  enhancement for TX/RX performance on IBSS-PS
**  \main\maintrunk.MT5921\111 2008-07-14 20:56:08 GMT mtk01461
**  Fix the warning message from PREfast
**  \main\maintrunk.MT5921\110 2008-07-09 09:29:42 GMT mtk01104
**  Add failCount_up_limit and failCount_down_limit in halARSetParam()
**  \main\maintrunk.MT5921\109 2008-07-04 13:41:36 GMT mtk01088
**  add code to identify the reversion id at CIR and store to adapter variable
**  \main\maintrunk.MT5921\108 2008-06-26 21:08:42 GMT mtk01084
**  add WMM-PS test related customizations
**  \main\maintrunk.MT5921\107 2008-06-25 18:01:23 GMT mtk01425
**  1. Fix logic reset bug
**  \main\maintrunk.MT5921\106 2008-06-18 20:45:20 GMT mtk01084
**  fix compiling warning
**  \main\maintrunk.MT5921\105 2008-06-17 17:56:51 GMT mtk01425
**  1. Add code from SDIO Tx Enhancement
**  \main\maintrunk.MT5921\104 2008-06-16 16:07:26 GMT mtk01084
**  fix TX gain to 0x28 when supporting 802.11A
**  \main\maintrunk.MT5921\103 2008-06-14 11:21:22 GMT MTK01088
**  use fixed wlan table entry to send non-encrypted 802.1x packet
**  \main\maintrunk.MT5921\102 2008-06-13 10:43:02 GMT MTK01088
**  not consider the Thermo and ALC at 802.11A support
**  \main\maintrunk.MT5921\101 2008-06-12 20:29:25 GMT mtk01461
**  Refine CFG_TX_DBG_TFCB_CHKSUM compile flag.
**  \main\maintrunk.MT5921\100 2008-06-06 09:33:48 GMT mtk01461
**  Add checking of lifetime field, set it to maximum if exceed the maximum value.
**  \main\maintrunk.MT5921\99 2008-06-01 12:28:29 GMT mtk01088
**  move the wlan tabe index init at nic halMCRInit, let this always be done at chip reset path
**  \main\maintrunk.MT5921\98 2008-05-23 10:24:55 GMT mtk01084
**  modified MAC address setting by CM's proposal
**  \main\maintrunk.MT5921\97 2008-05-21 18:35:09 GMT MTK01088
**  update the 0x134 MCR_BRDR default setting
**  \main\maintrunk.MT5921\96 2008-05-16 10:50:03 GMT mtk01461
**  Revise RCPI related function for RSSI OID & Roaming
**  \main\maintrunk.MT5921\95 2008-05-12 13:22:23 GMT mtk01084
**  modify the places to invoke port write macro
**  \main\maintrunk.MT5921\94 2008-04-24 12:01:47 GMT mtk01461
**  alter the order of set mac address relate func
**  \main\maintrunk.MT5921\93 2008-04-22 23:02:13 GMT mtk01084
**  modify port access function prototype
**  \main\maintrunk.MT5921\92 2008-04-21 14:07:27 GMT mtk01461
**  Fix compile error in x86
**  \main\maintrunk.MT5921\91 2008-04-20 11:29:00 GMT mtk01385
**  1. add UNDEF_TEMP state to thermo state.
**  \main\maintrunk.MT5921\90 2008-04-17 22:08:59 GMT mtk01084
**  set minimum timeout value by the input arguemt assignemetn
**  \main\maintrunk.MT5921\89 2008-04-17 19:37:42 GMT mtk01461
**  Add Data Port Test Code for SDIO Block/Byte Access
**  \main\maintrunk.MT5921\88 2008-04-16 15:22:13 GMT mtk01461
**  Remove AR ASSERT when get Current Rate Index
**  \main\maintrunk.MT5921\87 2008-04-11 00:34:51 GMT mtk01385
**  1. move nic tx power gain update related functions from nic to hal layer.
**  2. add update BB/RF Rx setting based on thermo info function.
**  \main\maintrunk.MT5921\86 2008-04-11 00:18:50 GMT mtk01385
**  1. add thermo high/normal/middle condition definitions.
**  2. move nic alc udate related macro from nic to hal layer.
**  \main\maintrunk.MT5921\85 2008-04-02 20:50:53 GMT mtk01084
**  support halRxConfigRxStatusGroup()
**  \main\maintrunk.MT5921\84 2008-03-31 11:04:05 GMT mtk01461
**  Add readdone larget incoming frame for SDIO enhance mode
**  \main\maintrunk.MT5921\83 2008-03-30 22:21:45 GMT mtk01084
**  workaround for tx done false alarm issue
**  \main\maintrunk.MT5921\82 2008-03-29 14:02:57 GMT mtk01461
**  Revise ASSERT to ASSERT_REPORT for PID check
**  \main\maintrunk.MT5921\81 2008-03-28 14:28:15 GMT mtk01385
**  1. fix ALC algorithm init error.
**  \main\maintrunk.MT5921\80 2008-03-28 10:40:19 GMT mtk01461
**  Print PID when PID mismatch
**  \main\maintrunk.MT5921\79 2008-03-26 23:22:40 GMT mtk01084
**  fix the issue on the workaround of HEC 5269 work on SDIO enhance mode
**  \main\maintrunk.MT5921\78 2008-03-20 22:01:48 GMT mtk01461
**  Revise coding method in ARSetRate() to avoid wrong asm instruction of CE5.0 compiler issue.
**  \main\maintrunk.MT5921\77 2008-03-20 12:04:27 GMT mtk01084
**  refine the hal access functions
**  \main\maintrunk.MT5921\76 2008-03-18 19:43:04 GMT mtk01084
**  modify the sleep timeout used for WDT, which aligns with BG SSID scan maximum interval
**  \main\maintrunk.MT5921\75 2008-03-18 12:03:43 GMT mtk01084
**  add function for AR to set the Fail Down Count Limit
**  \main\maintrunk.MT5921\74 2008-03-13 14:29:13 GMT mtk01461
**  Revise functions for Roaming Module
**  \main\maintrunk.MT5921\73 2008-03-12 09:14:40 GMT mtk01084
**  modify ARB_INDICATE_UC_FRAME_RECEIVED() macro
**  \main\maintrunk.MT5921\72 2008-02-21 23:26:56 GMT mtk01084
**  remove un-used lines
**  \main\maintrunk.MT5921\71 2008-02-21 15:01:45 GMT mtk01461
**  Rename the aucARBit2RateIndex to aucARIndex2RateIndex
**  \main\maintrunk.MT5921\70 2008-02-18 17:24:37 GMT mtk01084
**  remove un-used function
**  \main\maintrunk.MT5921\69 2008-02-13 15:25:35 GMT mtk01084
**  fix type mismatch issue, which cause compiler error
**  \main\maintrunk.MT5921\68 2008-02-12 23:00:55 GMT mtk01461
**  Add TX auto fragmentation for BT support
**  \main\maintrunk.MT5921\67 2008-02-04 17:05:56 GMT mtk01461
**  Refine ARB_IF_IN_RFTEST_STATE
**  \main\maintrunk.MT5921\66 2008-02-01 13:41:43 GMT mtk01385
**  1. read mcr value, or tirgger bit before ALC trigger.
**  \main\maintrunk.MT5921\65 2008-02-01 11:37:28 GMT mtk01385
**  1. fix CE 4.2 compiling error.
**  \main\maintrunk.MT5921\64 2008-02-01 10:34:54 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\63 2008-01-31 18:07:02 GMT mtk01385
**  1. add eeprom definitions and modify EEPROM read config function.
**  2. move eeprom definition to Nic layer.
**  3. Move EEPROM hal functions to NIC layer.
**  4. Add ALC Interrupt.
**  \main\maintrunk.MT5921\62 2008-01-31 16:17:16 GMT mtk01461
**  Add flush queue process for SDIO enhance mode
**  \main\maintrunk.MT5921\61 2008-01-17 16:14:04 GMT mtk01084
**  ensure RX and TX done status will be served if a not 0 value of length is read from the enhanced mode command
**  \main\maintrunk.MT5921\60 2008-01-07 15:07:09 GMT mtk01461
**  Add SDIO Enhance Support
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\59 2008-01-02 21:18:49 GMT mtk01461
**  Fix initial value of MCR-TCR wrongly set to Antenna 1.
**  \main\maintrunk.MT5921\58 2007-12-29 16:18:52 GMT mtk01385
**  1. move h/w Que Memory test to Arb init function.
**  2. Modify input parameter type in RR Enable function.
**  3. Add ALC HAL functions.
**  \main\maintrunk.MT5921\57 2007-12-24 16:00:50 GMT mtk01425
**  1. Revise Autorate function
**  \main\maintrunk.MT5921\56 2007-12-20 16:34:02 GMT mtk01084
**  new function to setup HW packet TX rate
**  \main\maintrunk.MT5921\55 2007-12-20 15:47:49 GMT mtk01084
**  modify chip reset procedure
**  \main\maintrunk.MT5921\54 2007-12-11 00:10:59 GMT mtk01461
**  Fix the order of SCAN Done & RX Done INT Event
**  \main\maintrunk.MT5921\53 2007-12-07 12:13:38 GMT mtk01084
**  fix compiling error
**  \main\maintrunk.MT5921\52 2007-12-04 18:08:32 GMT mtk01461
**  Add Tx Lifetime support
**  \main\maintrunk.MT5921\51 2007-11-30 19:41:18 GMT mtk01084
**  remove duplicated job
**  \main\maintrunk.MT5921\50 2007-11-30 16:59:27 GMT mtk01425
**  1. Modify halEnableRxHeaderTranslation to halSetRxHeaderTranslation
**  \main\maintrunk.MT5921\49 2007-11-29 15:52:43 GMT mtk01461
**  Update MCR 0x100, for duration cover next frame in TXOP
**  \main\maintrunk.MT5921\48 2007-11-29 15:50:21 GMT mtk01385
**  1. Enable Watch dog and MIB counter at default.
**  \main\maintrunk.MT5921\47 2007-11-26 19:42:05 GMT mtk01461
**  Unify SCAN
**
**  \main\maintrunk.MT5921\45 2007-11-22 23:19:56 GMT mtk01385
**  1. modify RCIP to RCPI
**  \main\maintrunk.MT5921\44 2007-11-22 22:17:15 GMT mtk01084
**  update event for handing TX packet timeout
**  \main\maintrunk.MT5921\43 2007-11-22 21:36:24 GMT mtk01385
**  1. updat RR register comply with DataSheet v0.26.
**  \main\maintrunk.MT5921\42 2007-11-22 19:06:54 GMT mtk01425
**  1. remove unused code
**  \main\maintrunk.MT5921\41 2007-11-21 15:44:46 GMT mtk01088
**  add code to get the rate code
**  \main\maintrunk.MT5921\40 2007-11-19 10:24:54 GMT mtk01385
**  1. add EEProm related functions.
**  2. update CCK short/long preamble counters.
**  \main\maintrunk.MT5921\39 2007-11-17 15:08:25 GMT mtk01385
**  1. Add Rx G0, G1, G2 extension field handle code.
**  2. add TFCB rftest mode handle code.
**  \main\maintrunk.MT5921\38 2007-11-12 16:32:40 GMT mtk01084
**  modify halChipReset()
**  \main\maintrunk.MT5921\37 2007-11-09 16:34:45 GMT mtk01425
**  1. Modify for CSUM offloading with Tx Fragment
**  \main\maintrunk.MT5921\36 2007-11-09 12:50:19 GMT mtk01084
**  support PSP-FAST mode
**  \main\maintrunk.MT5921\35 2007-11-08 20:40:53 GMT mtk01088
**  add tkip gen mic path
**  \main\maintrunk.MT5921\34 2007-11-08 20:27:42 GMT MTK01461
**  Add TX Port Read error handling for potential HW error
**  \main\maintrunk.MT5921\33 2007-11-08 14:07:57 GMT mtk01084
**  Fix compiler error in previous version on WInCE
**  \main\maintrunk.MT5921\32 2007-11-07 19:12:51 GMT mtk01425
**  1. Add Tx Fragment CSUM offloading
**  \main\maintrunk.MT5921\31 2007-11-07 18:38:55 GMT mtk01461
**  Add Tx Fragmentation Support
**  \main\maintrunk.MT5921\30 2007-11-06 20:31:21 GMT mtk01088
**  use new macro to do the HW status check
**  \main\maintrunk.MT5921\29 2007-11-06 19:06:31 GMT mtk01385
**  remove redundant LP instructions array.
**  \main\maintrunk.MT5921\28 2007-11-02 01:02:06 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
**  \main\maintrunk.MT5921\27 2007-10-30 20:09:25 GMT mtk01084
**  support admission control
**  \main\maintrunk.MT5921\26 2007-10-30 10:36:20 GMT mtk01425
**  1. Refine multicast list code
**  \main\maintrunk.MT5921\25 2007-10-26 19:15:30 GMT mtk01084
**  modify halLogicReset functions
**  \main\maintrunk.MT5921\24 2007-10-25 18:07:06 GMT mtk01461
**  Add VOIP SCAN Support  & Refine Roaming
** Revision 1.4  2007/07/05 07:25:32  MTK01461
** Add Linux initial code, modify doc, add 11BB, RF init code
**
** Revision 1.3  2007/07/03 08:28:39  MTK01088
** remove non-used function
**
** Revision 1.2  2007/06/28 12:51:37  MTK01088
** add the check fifo empty function to hal.c
**
*/

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "precomp.h"

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
QINFO_T arQInitTbl[] = {
    {ENUM_QUEUE_ID_AC0,         HW_BUFF_DWSIZE_FOR_AC0,         0},
    {ENUM_QUEUE_ID_AC1,         HW_BUFF_DWSIZE_FOR_AC1,         0},
    {ENUM_QUEUE_ID_AC2,         HW_BUFF_DWSIZE_FOR_AC2,         0},
    {ENUM_QUEUE_ID_AC3,         HW_BUFF_DWSIZE_FOR_AC3,         0},
    {ENUM_QUEUE_ID_AC4,         HW_BUFF_DWSIZE_FOR_AC4,         0},
    {ENUM_QUEUE_ID_TSB,         HW_BUFF_DWSIZE_FOR_TSB,         0},
    {ENUM_QUEUE_ID_RX,          HW_BUFF_DWSIZE_FOR_RX,          0},
    {ENUM_QUEUE_ID_SCAN,        HW_BUFF_DWSIZE_FOR_SCAN,        0},
    {ENUM_QUEUE_ID_SCAN_CTRL,   HW_BUFF_DWSIZE_FOR_SCAN_CTRL,   0}
};

#define INT_EVENT_MAP_SIZE  sizeof(arIntEventMapTable)/sizeof(INT_EVENT_MAP_T)

#define EEPROM_TTL_ACCESS_RDY_MSEC      20
#define EEPROM_MAX_LOOP_ACCESS_RDY      200

#define THERMO_CONDITION_NOR2HI_TEMP    55
#define THERMO_CONDITION_HI2NOR_TEMP    35
#define THERMO_CONDITION_NOR2LOW_TEMP   (-5)
#define THERMO_CONDITION_LOW2NOR_TEMP   15

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/
const REG_ENTRY_T arMCRInitTable[] = {
    {MCR_HISR,          0x0},

    //workaround for the BB RX ready slow issue
    {MCR_BRUR1,         0x0000501e},
    {MCR_BRDR,          0x0606160a},

    {MCR_BSSSAR,        0x50},
    {MCR_DBGR,          0x20008073}, /*Enable Watch Dog, sleep timeout = 120sec (for BG SSID scan) */
    {MCR_MIBSCR,        MIBSR_DEFAULT},
    {MCR_MTCLR,         0x07701123},
    {MCR_TRANSMITCR,    0x7682000} /* TX RESP Antenna mode = 3, EIFS = 0x168, duration_cal = 1 (Kevin) */
};


INT_EVENT_MAP_T arIntEventMapTable[] = {
    {HISR_ABNORMAL_INT,     INT_EVENT_ABNORMAL,         INT_HISR},
    {HISR_WATCH_DOG,        INT_EVENT_WATCH_DOG,        INT_HISR},
    {HISR_TSF_DRIFT,        INT_EVENT_TSF_DRIFT,        INT_HISR},
    {HISR_RX_DONE,          INT_EVENT_RX,               INT_HISR}, /* NOTE: RX should have priority > SCAN_DONE for BG_SSID_SCAN */
    {HISR_SCAN_DONE,        INT_EVENT_SCAN_DONE,        INT_HISR},

    {HISR_TX_DONE,          INT_EVENT_TX,               INT_HISR},
    {HISR_T0_TIME,          INT_EVENT_T0_TIMEUP,        INT_HISR},
    {HISR_T1_TIME,          INT_EVENT_T1_TIMEUP,        INT_HISR},
    {HISR_T2_TIME,          INT_EVENT_T2_TIMEUP,        INT_HISR},
    {HISR_T3_TIME,          INT_EVENT_T3_TIMEUP,        INT_HISR},

    {HISR_ADMIT_TIME_MET,   INT_EVENT_ADMIT_TIME_MET,   INT_HISR},
    {HSCISR_BCN_TIMEOUT,    INT_EVENT_BEACON_TIMEOUT,   INT_HSCISR},
    {HSCISR_TX_NULL_FAIL,   INT_EVENT_TX_NULL_FAIL,     INT_HSCISR},
    {HSCISR_TX_TRIG_FAIL,   INT_EVENT_TX_TRIG_FAIL,     INT_HSCISR},
    {HSCISR_TX_PSPOLL_FAIL, INT_EVENT_TX_PSPOLL_FAIL,   INT_HSCISR},
    {HSCISR_BMC_TIMEOUT,    INT_EVENT_BMC_TIMEOUT,      INT_HSCISR},
    {HISR_APSD_TIMEOUT,     INT_EVENT_APSD_TIMEOUT,     INT_HISR},
    {HISR_TX_PSPOLL_TIMEOUT,INT_EVENT_PSPOLL_TIMEOUT,   INT_HISR},
    {HISR_TBTT,             INT_EVENT_TBTT,             INT_HISR},
    {HISR_BEACON_TR_OK,     INT_EVENT_BCN_TR_OK,        INT_HISR},
    {HISR_ATIM_W_TIMEUP,    INT_EVENT_ATIM,             INT_HISR},
    {HISR_BEACON_T_OK,      INT_EVENT_BCN_TX_OK,        INT_HISR},
    {HISR_RCPI_INT,         INT_EVENT_RCPI,             INT_HISR},
    {HISR_ALC_VIOLATE,      INT_EVENT_ALC,              INT_HISR},
};

const UINT_8 ucIntEventMapSize = (sizeof(arIntEventMapTable) / sizeof(INT_EVENT_MAP_T));

const UINT_8 ucIntRegNum = 2;
const UINT_32 au4IntRegs[] = {
    MCR_HISR,
    MCR_HSCISR
};
const UINT_32 au4IERRegs[] = {
    MCR_HIER,
    MCR_HSCIER
};

RX_FILTER_MAP_T arRxFilterMapTable[] = {
    {/* RXFILTER_RXSAMEBSSIDPRORESP, */TRUE, BIT(28)},
    {/* RXFILTER_RXDIFFBSSIDPRORESP, */TRUE, BIT(27)},
    {/* RXFILTER_RXSAMEBSSIDATIM, */TRUE, BIT(26)},
    {/* RXFILTER_RXDIFFBSSIDATIM, */TRUE, BIT(25)},
    {/* RXFILTER_RXSAMEBSSIDNULL, */TRUE, BIT(24)},
    {/* RXFILTER_RXDIFFBSSIDNULL, */TRUE, BIT(23)},
    {/* RXFILTER_RXSAMEBSSIDBCN, */TRUE, BIT(22)},
    {/* RXFILTER_RXDIFFBSSIDBCN, */TRUE, BIT(21)},
    {/* RXFILTER_RXPROREQ, */TRUE, BIT(20)},
    {/* RXFILTER_RXDROPVERSIONNOT0, */TRUE, BIT(19)},
    {/* RXFILTER_RXNOACK, */TRUE, BIT(18)},
    {/* RXFILTER_RXMGMTFRAME, */TRUE, BIT(17)},
    {/* RXFILTER_RXDATAFRAME, */TRUE, BIT(16)},
    {/* RXFILTER_DROPDIFFBSSIDMGT, */TRUE, BIT(15)},
    {/* RXFILTER_DROPA3OWNSA, */TRUE, BIT(14)},
    {/* RXFILTER_DROPDIFFBSSIDA3, */TRUE, BIT(13)},
    {/* RXFILTER_DROPDIFFBSSIDA2, */TRUE, BIT(12)},
    {/* RXFILTER_RXBCFRAME, */TRUE, BIT(11)},
    {/* RXFILTER_MCTABLENOCHK, */TRUE, BIT(10)},
    {/* RXFILTER_RXMCFRAME, */TRUE, BIT(9)},
    {/* RXFILTER_RXPROMISCUOUSFRAME, */TRUE, BIT(1)},
    {/* RXFILTER_DROPFCS, */TRUE, BIT(0)}
};

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

static const UINT_16 aucRateIndex2RateCode[PREAMBLE_OPTION_NUM][RATE_NUM] = {
    { /* Long Preamble(Default) */
        RATE_CCK_1M_LONG,       /* RATE_1M_INDEX = 0 */
        RATE_CCK_2M_LONG,       /* RATE_2M_INDEX */
        RATE_CCK_5_5M_LONG,     /* RATE_5_5M_INDEX */
        RATE_CCK_11M_LONG,      /* RATE_11M_INDEX */
        RATE_CCK_1M_LONG,       /* RATE_22M_INDEX - Not supported */
        RATE_CCK_1M_LONG,       /* RATE_33M_INDEX - Not supported */
        RATE_OFDM_6M,           /* RATE_6M_INDEX */
        RATE_OFDM_9M,           /* RATE_9M_INDEX */
        RATE_OFDM_12M,          /* RATE_12M_INDEX */
        RATE_OFDM_18M,          /* RATE_18M_INDEX */
        RATE_OFDM_24M,          /* RATE_24M_INDEX */
        RATE_OFDM_36M,          /* RATE_36M_INDEX */
        RATE_OFDM_48M,          /* RATE_48M_INDEX */
        RATE_OFDM_54M           /* RATE_54M_INDEX */
    },
    { /* Short Preamble Option */
        RATE_CCK_1M_LONG,       /* RATE_1M_INDEX = 0 */
        RATE_CCK_2M_SHORT,      /* RATE_2M_INDEX */
        RATE_CCK_5_5M_SHORT,    /* RATE_5_5M_INDEX */
        RATE_CCK_11M_SHORT,     /* RATE_11M_INDEX */
        RATE_CCK_1M_LONG,       /* RATE_22M_INDEX - Not supported */
        RATE_CCK_1M_LONG,       /* RATE_33M_INDEX - Not supported */
        RATE_OFDM_6M,           /* RATE_6M_INDEX */
        RATE_OFDM_9M,           /* RATE_9M_INDEX */
        RATE_OFDM_12M,          /* RATE_12M_INDEX */
        RATE_OFDM_18M,          /* RATE_18M_INDEX */
        RATE_OFDM_24M,          /* RATE_24M_INDEX */
        RATE_OFDM_36M,          /* RATE_36M_INDEX */
        RATE_OFDM_48M,          /* RATE_48M_INDEX */
        RATE_OFDM_54M           /* RATE_54M_INDEX */
    }
};

static const UINT_8 aucRateIndex2ACKRateCode[RATE_NUM] = {
    ACK_RATE_CCK_1M,        /* RATE_1M_INDEX = 0 */
    ACK_RATE_CCK_2M,        /* RATE_2M_INDEX */
    ACK_RATE_CCK_5_5M,      /* RATE_5_5M_INDEX */
    ACK_RATE_CCK_11M,       /* RATE_11M_INDEX */
    ACK_RATE_CCK_1M,        /* RATE_22M_INDEX - Not supported */
    ACK_RATE_CCK_1M,        /* RATE_33M_INDEX - Not supported */
    ACK_RATE_OFDM_6M,       /* RATE_6M_INDEX */
    ACK_RATE_OFDM_9M,       /* RATE_9M_INDEX */
    ACK_RATE_OFDM_12M,      /* RATE_12M_INDEX */
    ACK_RATE_OFDM_18M,      /* RATE_18M_INDEX */
    ACK_RATE_OFDM_24M,      /* RATE_24M_INDEX */
    ACK_RATE_OFDM_36M,      /* RATE_36M_INDEX */
    ACK_RATE_OFDM_48M,      /* RATE_48M_INDEX */
    ACK_RATE_OFDM_54M       /* RATE_54M_INDEX */
};

static const UINT_8 aucRateIndex2ARIndex[PREAMBLE_OPTION_NUM][RATE_NUM] = {
    { /* Long Preamble(Default) */
        ARCR_1M_IDX,
        ARCR_2ML_IDX,
        ARCR_5_5ML_IDX,
        ARCR_11ML_IDX,
        ARCR_1M_IDX,
        ARCR_1M_IDX,
        ARCR_6M_IDX,
        ARCR_9M_IDX,
        ARCR_12M_IDX,
        ARCR_18M_IDX,
        ARCR_24M_IDX,
        ARCR_36M_IDX,
        ARCR_48M_IDX,
        ARCR_54M_IDX
    },
    { /* Short Preamble Option */
        ARCR_1M_IDX,
        ARCR_2MS_IDX,
        ARCR_5_5MS_IDX,
        ARCR_11MS_IDX,
        ARCR_1M_IDX,
        ARCR_1M_IDX,
        ARCR_6M_IDX,
        ARCR_9M_IDX,
        ARCR_12M_IDX,
        ARCR_18M_IDX,
        ARCR_24M_IDX,
        ARCR_36M_IDX,
        ARCR_48M_IDX,
        ARCR_54M_IDX
    }
};

static const UINT_8 aucARIndex2RateIndex[] = {
    RATE_1M_INDEX,
    RATE_2M_INDEX,
    RATE_2M_INDEX,
    RATE_5_5M_INDEX,
    RATE_5_5M_INDEX,
    RATE_11M_INDEX,
    RATE_11M_INDEX,
    RATE_6M_INDEX,
    RATE_9M_INDEX,
    RATE_12M_INDEX,
    RATE_18M_INDEX,
    RATE_24M_INDEX,
    RATE_36M_INDEX,
    RATE_48M_INDEX,
    RATE_54M_INDEX
};


/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
#define TX_GAIN_UPDATE_WITH_LIMIT(_oldGain, _DeltaGain, _newGain) \
        { \
            if(_DeltaGain < 0) {\
                if(_oldGain + _DeltaGain < 0) {\
                    _newGain = 0;\
                }\
                else{\
                    _newGain = _oldGain+ _DeltaGain;\
                }\
            }\
            else {\
                if(_oldGain + _DeltaGain > 0x7F) {\
                    _newGain = 0x7F;\
                }\
                else{\
                    _newGain = _oldGain+ _DeltaGain;\
                }\
            }\
        }


#if CFG_ONLY_802_11A
#define TX_GAIN_UPDATA_FROM_EEPROM_ALC(_rate_Group, _ucPowerGain ) \
    {\
        _ucPowerGain = prEepChCfg[ucChannelNum].rTxCfg[_rate_Group].ucPowerGain;\
    }

#else
#define TX_GAIN_UPDATA_FROM_EEPROM_ALC(_rate_Group, _ucPowerGain ) \
    {\
        INT_8 _cThermoVal;\
        INT_8 _cDeltaGain;\
        _ucPowerGain = prEepChCfg[ucChannelNum].rTxCfg[_rate_Group].ucPowerGain;\
        DBGLOG(NIC, LOUD, ("old Gain = 0x%02X\n", _ucPowerGain));\
        if (prThermoInfo->fgUpdateTxGainFromAlcInt == FALSE) { \
            DBGLOG(NIC, LOUD, ("Thermo Updata is disabled\n"));\
        }\
        else{\
            _cThermoVal = (INT_8)prEepChCfg[ucChannelNum].rTxCfg[_rate_Group].ucThermoVal;\
            _cDeltaGain = (INT_8) ((cInThermoVal- _cThermoVal) * cVgaSlop )/ cThermoSlop;\
            TX_GAIN_UPDATE_WITH_LIMIT(_ucPowerGain, _cDeltaGain, _ucPowerGain);\
            DBGLOG(NIC, LOUD, ("delta = %d\n", _cDeltaGain));\
        }\
    }
#endif

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

/*----------------------------------------------------------------------------*/
/*!
* \brief Verify the CHIP ID
*
* \param prAdapter      a pointer to adapter private data structure.
*
*
* \retval TRUE          CHIP ID is the same as the setting compiled
* \retval FALSE         CHIP ID is different from the setting compiled
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
halVerifyChipID (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4CIR = 0;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_CIR, &u4CIR );

    if ((u4CIR & CIR_CHIP_ID) != MTK_CHIP_REV) {
        return FALSE;
    }

    prAdapter->ucRevID = (UINT_8)(((u4CIR & CIR_REVISION_ID) >> 16) & 0x0F);

    switch (prAdapter->ucRevID) {
    case MTK_CHIP_MP_REVERSION_ID:
    case MTK_CHIP_ECO4_REVERSION_ID:
    case MTK_CHIP_ECO5_REVERSION_ID:
    case MTK_CHIP_ECO6_REVERSION_ID:
        break;

    default:
        ASSERT(FALSE);
        return FALSE;
        break;
    }

    return TRUE;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Verify the CHIP Revision ID
*
* \param prAdapter      a pointer to adapter private data structure.
*
*
* \retval TRUE          CHIP Revision ID is verified ok
* \retval FALSE         CHIP Revision ID is verified fail
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
halVerifyRevID (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4Reg = 0;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, BBCR_BPROBECTR, &u4Reg);

    if (MTK_CHIP_ECO5_REVERSION_ID == prAdapter->ucRevID) {
        if ((u4Reg & BIT(15))) {
            ASSERT(FALSE);
            return FALSE;
        }
    }
    else if (MTK_CHIP_ECO6_REVERSION_ID == prAdapter->ucRevID) {
        if (!(u4Reg & BIT(15))) {
            ASSERT(FALSE);
            return FALSE;
        }
    }

    /* Default return TRUE */
    return TRUE;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Initialize the MCR to the appropriate init value, and verify the init
*        value
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \return -
*/
/*----------------------------------------------------------------------------*/

VOID
halMCRInit (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4Idx = 0;

    ASSERT(prAdapter);

    //4 <0> Initial value
    for(u4Idx = 0; u4Idx < sizeof(arMCRInitTable)/sizeof(REG_ENTRY_T); u4Idx++) {
        HAL_MCR_WR(prAdapter, arMCRInitTable[u4Idx].u4Offset, arMCRInitTable[u4Idx].u4Value);
    }

#if SUPPORT_WAPI
    if (!prAdapter->fgUseWapi)
        halSetRxHeaderTranslation(prAdapter, TRUE);
#else
    halSetRxHeaderTranslation(prAdapter, TRUE);
#endif
    //4 <1> Change the wrong initial values to the correct ones
    halMCRChipInit(prAdapter);

    //4 <2> Do WLAN Table index init
    halWlanTableInit(prAdapter);

}


/*----------------------------------------------------------------------------*/
/*!
* \brief Initialize the FIFO queues address
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \return -
*/
/*----------------------------------------------------------------------------*/
//4 20060823, mikewu, mt5912b Queue initialization
VOID
halHWQueueInit (
    IN P_ADAPTER_T prAdapter
    )
{

    UINT_32 u4StartDW = 0;
    UINT_32 u4EndDW = 0;
    UINT_8 i = 0;
#if DBG
    UINT_32 u4UnusedSpace = 0;
#endif /* DBG */

    DEBUGFUNC("halHWQueueInit");

    ASSERT(prAdapter);

#if CFG_INTERNAL_MEMORY_TEST
    halHWQueueMemoryTest(prAdapter);
#endif /* CFG_INTERNAL_MEMORY_TEST */

#if CFG_DATA_PORT_ACCESS_TEST
    halBeaconQueueDataPortTest(prAdapter);
#endif /* CFG_DATA_PORT_ACCESS_TEST */


    // juji: modify to meet usage in HW scan
    for (i = 0; i < (sizeof(arQInitTbl)/sizeof(QINFO_T)); i++) {
        if (arQInitTbl[i].u4SizeDW != 0) {
            u4EndDW = u4StartDW + arQInitTbl[i].u4SizeDW - 1;
            HAL_MCR_WR(prAdapter,
                        MCR_QAR,
                        (u4StartDW | (u4EndDW << 13) | (arQInitTbl[i].ucQueueId << 28)));

            arQInitTbl[i].u4OffsetDW = u4StartDW;

            u4StartDW = u4EndDW + 1;

            DBGLOG(INIT, INFO, ("HW Queue %d: Offset: 0x%04lx DW, Size: %04ld bytes.\n",
                                arQInitTbl[i].ucQueueId,
                                arQInitTbl[i].u4OffsetDW,
                                DWORD_TO_BYTE(arQInitTbl[i].u4SizeDW)));
#if DBG
            u4UnusedSpace += DWORD_TO_BYTE(arQInitTbl[i].u4SizeDW);
#endif /* DBG */
        }
    }

#if DBG
    u4UnusedSpace = MAX_FIFO_SIZE - u4UnusedSpace;
#endif /* DBG */
    DBGLOG(INIT, INFO, ("HW Queue: Unused Space = %04ld bytes.\n", u4UnusedSpace));

    return;
} /* end of halHWQueueInit() */


#if CFG_TX_AGGREGATE_HW_FIFO
/*----------------------------------------------------------------------------*/
/*!
* \brief This function is used to aggregate the HW FIFO of AC0,AC1,AC2 to AC1 or
*        segregate AC1 to AC0,AC1,AC2 by update MCR_QAR.
*
* \param[in] prAdapter          Pointer to the Adapter structure.
* \param[in] fgAggregateTxFifo  A flag to instruct to aggregate HW FIFO or segregate.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halAggregateHWTxDataQueue (
    IN P_ADAPTER_T       prAdapter,
    IN BOOLEAN           fgAggregateTxFifo
    )
{

    UINT_32 u4StartDW = 0;
    UINT_32 u4EndDW = 0;
    UINT_8 i = 0;

    DEBUGFUNC("halHWQueueInit");

    ASSERT(prAdapter);

    // juji: modify to meet usage in HW scan
    if (fgAggregateTxFifo) { /* Aggregate AC0~2 to AC1 */
        UINT_32 u4AC1SizeDW = 0;

        for (i = 0; i < (sizeof(arQInitTbl)/sizeof(QINFO_T)); i++) {

            if ((arQInitTbl[i].ucQueueId == ENUM_QUEUE_ID_AC0) ||
                (arQInitTbl[i].ucQueueId == ENUM_QUEUE_ID_AC1) ||
                (arQInitTbl[i].ucQueueId == ENUM_QUEUE_ID_AC2) /* ||
                (arQInitTbl[i].ucQueueId == ENUM_QUEUE_ID_AC3) */) {

                u4AC1SizeDW += arQInitTbl[i].u4SizeDW;
            }
        }

        if (u4AC1SizeDW) {
            u4EndDW = u4StartDW + u4AC1SizeDW - 1;
            HAL_MCR_WR(prAdapter,
                       MCR_QAR,
                       (u4StartDW | (u4EndDW << 13) | (ENUM_QUEUE_ID_AC1 << 28)));

        }
    }
    else {

        for (i = 0; i < (sizeof(arQInitTbl)/sizeof(QINFO_T)); i++) {
            if (arQInitTbl[i].ucQueueId == ENUM_QUEUE_ID_AC1) {

                if (arQInitTbl[i].u4SizeDW) {
                    u4EndDW = u4StartDW + arQInitTbl[i].u4SizeDW - 1;
                    HAL_MCR_WR(prAdapter,
                               MCR_QAR,
                               (u4StartDW | (u4EndDW << 13) | (ENUM_QUEUE_ID_AC1 << 28)));
                }

                break;
            }
        }
    }

    return;
} /* end of halAggregateHWTxDataQueue() */
#endif /* CFG_TX_AGGREGATE_HW_FIFO */


#if CFG_INTERNAL_MEMORY_TEST
VOID
halHWQueueMemoryTest (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4TestPatterns[] = {0xFFFFffff, 0xa5a5a5a5, 0x5a5a5a5a, 0x00000000};
    UINT_32 u4Pattern, u4RegValue;
    BOOL fgIsFail = FALSE;
    INT_32 i, j;

    DEBUGFUNC("halHWQueueMemoryTest");

    ASSERT(prAdapter);

    HAL_MCR_WR(prAdapter, MCR_QCR, QCR_ALL_STOP_FLUSH);

    DBGLOG(INIT, TRACE, ("Internal memory (FIFO) test: test decreased pattern\n"));
    /* test decreased pattern */
    {
        HAL_MCR_WR(prAdapter, MCR_HFCR, (HFCR_SELECT_DATA_FIFO|
            HFCR_FIFO_WRITE));

        for (j = (MAX_FIFO_SIZE/sizeof(UINT_32) - 1); j >= 0; j--) {
            HAL_MCR_WR(prAdapter, MCR_HFDR, (UINT_32)j);
        }

        HAL_MCR_WR(prAdapter, MCR_HFCR, (HFCR_SELECT_DATA_FIFO|
            HFCR_FIFO_READ));

        for (j = (MAX_FIFO_SIZE/sizeof(UINT_32) - 1); j >= 0; j--) {
            HAL_MCR_RD(prAdapter, MCR_HFDR, &u4RegValue);

            ASSERT((UINT_32)j == u4RegValue);

            if ((UINT_32)j != u4RegValue) {
                fgIsFail = TRUE;
            }
        }
    }


    /* test fixed pattern */
    for (i = 0; i < (sizeof(u4TestPatterns)/sizeof(UINT_32)); i++) {
        DBGLOG(INIT, TRACE, ("Internal memory (FIFO) test: test fixed pattern (i=%ld)\n", i));

        u4Pattern = u4TestPatterns[i];

        HAL_MCR_WR(prAdapter, MCR_HFCR, (HFCR_SELECT_DATA_FIFO|
            HFCR_FIFO_WRITE));

        for (j = 0; j < (MAX_FIFO_SIZE/sizeof(UINT_32)); j++) {
            HAL_MCR_WR(prAdapter, MCR_HFDR, u4Pattern);
        }

        HAL_MCR_WR(prAdapter, MCR_HFCR, (HFCR_SELECT_DATA_FIFO|
            HFCR_FIFO_READ));

        for (j = 0; j < (MAX_FIFO_SIZE/sizeof(UINT_32)); j++) {
            HAL_MCR_RD(prAdapter, MCR_HFDR, &u4RegValue);

            ASSERT(u4Pattern == u4RegValue);

            if (u4Pattern != u4RegValue) {
                fgIsFail = TRUE;
            }
        }
    }

    /* summary */
    if (fgIsFail) {
        DBGLOG(INIT, ERROR, ("Internal memory (FIFO) test fail.\n"));
    }
    else {
        DBGLOG(INIT, TRACE, ("Internal memory (FIFO) test ok.\n"));
    }

    return;
}
#endif /* CFG_INTERNAL_MEMORY_TEST */


#if CFG_DATA_PORT_ACCESS_TEST

#define HW_BUFF_OFFSET_FOR_TSB          1024
#define HW_BUFF_DWSIZE_FOR_TSB_TEST     512 /* Payload Length = 2044 */
#define TEST_PATTERN_I(_tmp)            (_tmp)
#define TEST_PATTERN_II(_tmp)           ((_tmp) << 1)
#define TEST_PATTERN_III(_tmp)          ((_tmp) << 2)

//UINT_32 au4DummyBeaconContent[HW_BUFF_DWSIZE_FOR_TSB_TEST] __KAL_ATTRIB_ALIGN_4__;

VOID
halBeaconQueueDataPortTest (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 au4DummyBeaconContent[HW_BUFF_DWSIZE_FOR_TSB_TEST];
    UINT_32 u4TestLengthDW[] = {128, 255, 511, 512};
    UINT_32 u4LengthDW;
    UINT_32 u4QAR, u4RegValue;
    UINT_32 u4StartDW;
    UINT_32 u4EndDW;
    UINT_32 u4BeaconTfb;
    UINT_32 i, j;
    BOOL fgIsFail = FALSE;
#ifdef _HIF_SDIO
    BOOL fgResult = FALSE;
#endif

    ASSERT(prAdapter);

    /* Program QAR and verify it */
    u4StartDW = HW_BUFF_OFFSET_FOR_TSB;
    u4EndDW = HW_BUFF_OFFSET_FOR_TSB + (HW_BUFF_DWSIZE_FOR_TSB_TEST - 1);

    u4QAR = u4StartDW | (u4EndDW << 13) | (ENUM_QUEUE_ID_TSB << 28);

    HAL_MCR_WR(prAdapter, MCR_QAR, u4QAR);

    u4QAR = QAR_READ_MODE | (ENUM_QUEUE_ID_TSB << 28);

    HAL_MCR_WR(prAdapter, MCR_QAR, u4QAR);

    HAL_MCR_RD(prAdapter, MCR_QAR, &u4RegValue);

    if ((u4RegValue & BITS(0, 25)) != (u4StartDW | (u4EndDW << 13))) {
        fgIsFail = TRUE;
        ASSERT_REPORT(0, ("QAR Access Fail, u4RegValue = %08lx\n", u4RegValue));
    }

    /* Write dummy beacon content and verify it for different length */
    for (i = 0; i < sizeof(u4TestLengthDW)/sizeof(UINT_32); i++) {

        u4LengthDW = u4TestLengthDW[i];
        DBGLOG(HAL, INFO, ("MT5921: test DW length(%ld)\n", u4LengthDW));

        u4BeaconTfb = 0; // Antenna 0
        u4BeaconTfb |= (RATE_CCK_11M_SHORT << BCN_TFCB_RATE_INDEX_OFFSET);
        u4BeaconTfb |= (DWORD_TO_BYTE(u4LengthDW - 1) & BCN_TFCB_PAYLOAD_LEN_MASK);

        /* Test Case I: Port Write and MCR Read */
        DBGLOG(HAL, INFO, ("\n\nTest Case I: Port Write and MCR Read\n\n"));

        au4DummyBeaconContent[0] = u4BeaconTfb;
        for (j = 1; j < u4LengthDW; j++) {
            au4DummyBeaconContent[j] = TEST_PATTERN_I(j);
        }

        HAL_PORT_WR(prAdapter,
                    MCR_HBDR,
                    (UINT_16)DWORD_TO_BYTE(u4LengthDW),
                    (PUINT_8)&au4DummyBeaconContent[0],
                    (UINT_16)DWORD_TO_BYTE(u4LengthDW));

        DBGLOG(HAL, INFO, ("Port Write done\n"));

        HAL_MCR_WR(prAdapter, MCR_HWTCR, HWTCR_B_RMODE);
        DBGLOG(HAL, INFO, ("MCR Write done\n"));

        HAL_MCR_RD(prAdapter, MCR_HBDR, &u4RegValue);
        DBGLOG(HAL, INFO, ("MCR Read done\n"));

        if (u4RegValue != u4BeaconTfb) {
            fgIsFail = TRUE;
            ASSERT_REPORT(0, ("Port Write and MCR Read Fail, u4RegValue[0] = %08lx (expect: %08lx)\n",
                u4RegValue, u4BeaconTfb));
            break;
        }

        for (j = 1; j < u4LengthDW; j++) {
            HAL_MCR_RD(prAdapter, MCR_HBDR, &u4RegValue);

            DBGLOG(HAL, LOUD, ("u4RegValue = %08lx\n", u4RegValue));
            if (u4RegValue != TEST_PATTERN_I(j)) {
                fgIsFail = TRUE;
                ASSERT_REPORT(0, ("Port Write and MCR Read Fail, u4RegValue[%ld] = %08lx\n",
                    j, u4RegValue));
                break;
            }
        }

        if (fgIsFail) {
            break;
        }

        /* Test Case II: MCR Write and Port Read */
        DBGLOG(HAL, INFO, ("\n\nTest Case II: MCR Write and Port Read\n\n"));

        HAL_MCR_WR(prAdapter, MCR_HBDR, u4BeaconTfb);
        for (j = 1; j < u4LengthDW; j++) {
            HAL_MCR_WR(prAdapter, MCR_HBDR, TEST_PATTERN_II(j));
        }

        HAL_MCR_WR(prAdapter, MCR_HWTCR, HWTCR_B_RMODE);

        kalMemZero(&au4DummyBeaconContent[0],
                   sizeof(au4DummyBeaconContent));

        HAL_PORT_RD(prAdapter,
                    MCR_HBDR,
                    (UINT_16)DWORD_TO_BYTE(u4LengthDW),
                    (PUINT_8)&au4DummyBeaconContent[0],
                    (UINT_16)DWORD_TO_BYTE(u4LengthDW));

        if (u4BeaconTfb != au4DummyBeaconContent[0]) {
            fgIsFail = TRUE;
            ASSERT_REPORT(0, ("MCR Write and Port Read Fail, au4DummyBeaconContent[0] = %08lx\n",
                au4DummyBeaconContent[0]));
            break;
        }

        for (j = 1; j < u4LengthDW; j++) {
            DBGLOG(HAL, LOUD, ("au4DummyBeaconContent[%ld] = %08lx\n", j, au4DummyBeaconContent[j]));

            if (au4DummyBeaconContent[j] != TEST_PATTERN_II(j)) {
                fgIsFail = TRUE;
                ASSERT_REPORT(0, ("MCR Write and Port Read Fail, au4DummyBeaconContent[%ld] = %08lx\n",
                    j, au4DummyBeaconContent[j]));
                break;
            }
        }

        if (fgIsFail) {
            break;
        }


        /* Test Case III: Port Write and Port Read */
        DBGLOG(HAL, INFO, ("\n\nTest Case III: Port Write and Port Read\n\n"));

        au4DummyBeaconContent[0] = u4BeaconTfb;
        for (j = 1; j < u4LengthDW; j++) {
            au4DummyBeaconContent[j] = TEST_PATTERN_III(j);
        }

        HAL_PORT_WR(prAdapter,
                    MCR_HBDR,
                    (UINT_16)DWORD_TO_BYTE(u4LengthDW),
                    (PUINT_8)&au4DummyBeaconContent[0],
                    (UINT_16)DWORD_TO_BYTE(u4LengthDW));

        HAL_MCR_WR(prAdapter, MCR_HWTCR, HWTCR_B_RMODE);

        kalMemZero(&au4DummyBeaconContent[0],
                   sizeof(au4DummyBeaconContent));

        HAL_PORT_RD(prAdapter,
                    MCR_HBDR,
                    (UINT_16)DWORD_TO_BYTE(u4LengthDW),
                    (PUINT_8)&au4DummyBeaconContent[0],
                    (UINT_16)DWORD_TO_BYTE(u4LengthDW));

        if (u4BeaconTfb != au4DummyBeaconContent[0]) {
            fgIsFail = TRUE;
            ASSERT_REPORT(0, ("Port Write and Port Read Fail, au4DummyBeaconContent[0] = %08lx\n",
                au4DummyBeaconContent[0]));
            break;
        }

        for (j = 1; j < u4LengthDW; j++) {
            DBGLOG(HAL, LOUD, ("au4DummyBeaconContent[%ld] = %08lx\n", j, au4DummyBeaconContent[j]));

            if (au4DummyBeaconContent[j] != TEST_PATTERN_III(j)) {
                fgIsFail = TRUE;
                ASSERT_REPORT(0, ("Port Write and Port Read Fail, au4DummyBeaconContent[%ld] = %08lx\n",
                    j, au4DummyBeaconContent[j]));
                break;
            }
        }

        if (fgIsFail) {
            break;
        }

    }


    /* summary */
    if (fgIsFail) {
        DBGLOG(INIT, ERROR, ("Data Port Access test fail.\n"));
    }
    else {
        DBGLOG(INIT, TRACE, ("Data Port Access test ok.\n"));
    }

    return;

}
#endif /* CFG_DATA_PORT_ACCESS_TEST */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function used to flush the Rx FIFO, not received,
*             general used for Rx len incorrect
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRxReadDone (
    IN P_ADAPTER_T prAdapter
    )
{

    ASSERT(prAdapter);

    HAL_MCR_WR(prAdapter,
               MCR_HCR,
               HCR_RX_DATA_RD_DONE);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Config the RX status group, by spec, driver can got more info from
*        Chip if enable these bit,
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRxConfigRxStatusGroup (
    IN P_ADAPTER_T prAdapter
    )
{
    P_RX_CTRL_T prRxCtrl;
    UINT_32     u4MSCR;

    ASSERT(prAdapter);
    prRxCtrl = &prAdapter->rRxCtrl;

    HAL_MCR_RD(prAdapter, MCR_MSCR, &u4MSCR);

    if (prRxCtrl->fgIsRxStatusG0) {
        u4MSCR |= MSCR_RX_STATUS_G0_EN;
    }
    if (prRxCtrl->fgIsRxStatusG1) {
        u4MSCR |= MSCR_RX_STATUS_G1_EN;
    }
    if (prRxCtrl->fgIsRxStatusG2) {
        u4MSCR |= MSCR_RX_STATUS_G2_EN;
    }
    if (prRxCtrl->fgIsRxStatusG0Rssi) {
        u4MSCR |= MSCR_RX_BBP_RXSTS_SEL;
    }

    HAL_MCR_WR(prAdapter, MCR_MSCR, u4MSCR);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Enabled the Rx header Translation from,
*        Chip will tranform the 802.11 non-fragment data to 802.3 format
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halSetRxHeaderTranslation (
    IN P_ADAPTER_T      prAdapter,
    IN BOOLEAN          fgEnable
    )
{
    UINT_32             u4tmp;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_MSCR, &u4tmp);
    if (fgEnable) {
        u4tmp |= MSCR_RX_TRANSLATION_EN;
    }
    else {
        u4tmp &= ~MSCR_RX_TRANSLATION_EN;
    }
    HAL_MCR_WR(prAdapter, MCR_MSCR, u4tmp);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief In this function, we compose the HW_TFCB_T for incoming SW TFCB Frame.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prSwTfcb       Pointer of SW_TFCB_T
* \param[in] pucDA          Pointer of DA field of 802.3(Ethernet) frame
* \param[out] prHwTfcb      Pointer of HW_TFCB_T
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halTxComposeFrameControlBlock (
    IN P_ADAPTER_T  prAdapter,
    IN P_SW_TFCB_T  prSwTfcb,
    IN PUINT_8      pucDA,
    OUT P_HW_TFCB_T prHwTfcb
    )
{
#if CFG_TX_DBG_TFCB_CHKSUM || CFG_TX_DBG_INCREASED_PID
    P_TX_CTRL_T prTxCtrl;
#endif /* CFG_TX_DBG_TFCB_CHKSUM || CFG_TX_DBG_INCREASED_PID */
    P_MSDU_INFO_T prMsduInfo;
    UINT_16 u2RemainingLifeTimeIn2TU;

    ASSERT(prAdapter);
    ASSERT(prSwTfcb);
    ASSERT(prHwTfcb);

#if CFG_TX_DBG_TFCB_CHKSUM || CFG_TX_DBG_INCREASED_PID
    prTxCtrl = &prAdapter->rTxCtrl;
#endif /* CFG_TX_DBG_TFCB_CHKSUM || CFG_TX_DBG_INCREASED_PID */
    prMsduInfo = prSwTfcb->prMsduInfo;

    kalMemZero((PVOID)prHwTfcb, sizeof(HW_TFCB_T));

    // Calculate Remain Lifetime in unit of 2TU.
    if (prMsduInfo->ucControlFlag & MSDU_INFO_CTRL_FLAG_LIFETIME_NEVER_EXPIRE) {
        u2RemainingLifeTimeIn2TU = 0;
    }
    else {
        OS_SYSTIME rCurrentTime;
        UINT_32 u4CurrentTimeTU, u4ArrivalTimeTU;

        GET_CURRENT_SYSTIME(&rCurrentTime);
        u4CurrentTimeTU = SYSTIME_TO_TU(rCurrentTime);
        u4ArrivalTimeTU = SYSTIME_TO_TU(prMsduInfo->rArrivalTime);

        if ( TIME_AFTER(u4CurrentTimeTU,
            (u4ArrivalTimeTU + DOT11_TRANSMIT_MSDU_LIFETIME_TU_DEFAULT) ) ) {
            /* Case of Lifetime expired excluding the same time */
            /* TODO(Kevin 2007/12/04):
             * Actually we should drop this frame immediately, but it need revise
             * part of TX flow. To reduce the coding overhead, we assign its
             * Remaining Lifetime to 1(2TU) for last tryout in current design.
             */
            u2RemainingLifeTimeIn2TU = 1;
        }
        else {
            /* Case of Lifetime didn't expire */
            u2RemainingLifeTimeIn2TU = (UINT_16)(DOT11_TRANSMIT_MSDU_LIFETIME_TU_DEFAULT -
                (u4CurrentTimeTU - u4ArrivalTimeTU)) / 2;

            if (u2RemainingLifeTimeIn2TU > TFCB_MAX_LIFETIME_IN_2TU) {
                u2RemainingLifeTimeIn2TU = TFCB_MAX_LIFETIME_IN_2TU;
            }
            // For the case of "at the same time" and round down because of division.
            else if (u2RemainingLifeTimeIn2TU == 0) {
                u2RemainingLifeTimeIn2TU = 1;
            }
        }
    }


#if CFG_TX_FRAGMENT
    if (prMsduInfo->ucFragTotalCount > 1) {
        UINT_16 u2FragPayloadLen;

        // For 1st ~ (N-1)th MPDU
        if (prMsduInfo->ucFragFinishedCount < (prMsduInfo->ucFragTotalCount - 1)) {
            u2FragPayloadLen = prMsduInfo->u2PayloadFragThreshold;
        }
        // For the last (Nth) MPDU
        else {
            UINT_16 u2OverallPayloadLength = prMsduInfo->u2PayloadLength;

            if (prMsduInfo->pucLLC) {
                u2OverallPayloadLength += (prMsduInfo->ucLLCLength + ETHER_TYPE_LEN);
            }

            if (prMsduInfo->ucControlFlag & MSDU_INFO_CTRL_FLAG_CALCULATE_MIC) {
                u2OverallPayloadLength += TKIP_MIC_LEN;
            }

            u2FragPayloadLen = u2OverallPayloadLength -
                               (prMsduInfo->u2PayloadFragThreshold * prMsduInfo->ucFragFinishedCount);
        }

        //4 <1> Fill Q_Idx, Header_format - 802.11 for SW Fragmentation, Remaining Life Time Field(<TODO>)
        prHwTfcb->u2LifeTimeQIdx = ( \
            (prSwTfcb->ucAC & TFCB_QIDX_MASK) | \
            TFCB_FLAG_HEADER_802_11 |
            ((u2RemainingLifeTimeIn2TU << TFCB_LIFETIME_OFFSET) & TFCB_LIFETIME_MASK));

        prHwTfcb->u2WlanHeaderLength = prMsduInfo->ucFragWlanHeaderLength;

        //4 <2> Fill Payload_length Field
        prHwTfcb->u2PayloadLength = u2FragPayloadLen & TFCB_PAYLOAD_LEN_MASK;

        /* Check the consistency between SW_TFCB and the contain of HW_TFCB. */
        ASSERT(prSwTfcb->u2OverallBufferLength ==
            (TFCB_SIZE + prHwTfcb->u2WlanHeaderLength + prHwTfcb->u2PayloadLength));
    }
    else
#endif /* CFG_TX_FRAGMENT */
    {

        //4 <1> Fill Q_Idx, Header_format, Remaining Life Time Field(<TODO>)
        if (prMsduInfo->fgIs802_11Frame) {
            prHwTfcb->u2LifeTimeQIdx = ( \
                (prSwTfcb->ucAC & TFCB_QIDX_MASK) | \
                TFCB_FLAG_HEADER_802_11 | \
                ((u2RemainingLifeTimeIn2TU << TFCB_LIFETIME_OFFSET) & TFCB_LIFETIME_MASK));

            prHwTfcb->u2WlanHeaderLength = prMsduInfo->ucMacHeaderLength;

#if SUPPORT_WAPI
            /* Todo: make sure the prHwTfcb->u2WlanHeaderLength is 24 or 26 */
            if (prAdapter->fgUseWapi && prMsduInfo->fgIs802_11Frame &&
                !prMsduInfo->fgIsFromInternalProtocolStack){

                if (prMsduInfo->ucChkSumWapiFlag & TX_WPI_OPEN) {
                    if (prSwTfcb->u2OverallBufferLength !=
                       (TFCB_SIZE + prHwTfcb->u2WlanHeaderLength + prMsduInfo->u2PayloadLength + prMsduInfo->ucLLCLength + ETHER_TYPE_LEN)) {
                        DBGLOG(WAPI, TRACE, (".Overall %d TFCB_SZ %d wlanHdrLen %d payload %d\r\n",
                            prSwTfcb->u2OverallBufferLength, TFCB_SIZE,
                            prHwTfcb->u2WlanHeaderLength, prMsduInfo->u2PayloadLength + prMsduInfo->ucLLCLength + ETHER_TYPE_LEN));
                    }
                }
                else if (prMsduInfo->ucChkSumWapiFlag & TX_WPI_ENCRYPT){
                    if (prSwTfcb->u2OverallBufferLength !=
                       (TFCB_SIZE + prHwTfcb->u2WlanHeaderLength + prMsduInfo->u2PayloadLength + prMsduInfo->ucLLCLength + ETHER_TYPE_LEN + KEYID_LEN + KEYID_RSV_LEN + PN_LEN + WPI_MIC_LEN)) {
                        DBGLOG(WAPI, TRACE, ("-Overall %d TFCB_SZ %d wlanHdrLen %d payload %d\r\n",
                            prSwTfcb->u2OverallBufferLength, TFCB_SIZE,
                            prHwTfcb->u2WlanHeaderLength, prMsduInfo->u2PayloadLength + prMsduInfo->ucLLCLength + ETHER_TYPE_LEN + KEYID_LEN + KEYID_RSV_LEN + PN_LEN + WPI_MIC_LEN));
                    }
                }
            }
            else {
#endif
            /* Check the consistency between SW_TFCB and the contain of HW_TFCB. */
            ASSERT(prSwTfcb->u2OverallBufferLength ==
                (TFCB_SIZE + prHwTfcb->u2WlanHeaderLength + prMsduInfo->u2PayloadLength));
#if SUPPORT_WAPI
            }
#endif
        }
        else {
            prHwTfcb->u2LifeTimeQIdx = ( \
                (prSwTfcb->ucAC & TFCB_QIDX_MASK) | \
                ((u2RemainingLifeTimeIn2TU << TFCB_LIFETIME_OFFSET) & TFCB_LIFETIME_MASK));

            /* Fill DA Field for figuring TFCB_checksum later */
#if CFG_TX_DBG_TFCB_CHKSUM
            if (pucDA) {
                kalMemCopy((PVOID)(&prHwTfcb->ucDA[0]), (PVOID)pucDA, MAC_ADDR_LEN);
            }
#endif /* CFG_TX_DBG_TFCB_CHKSUM */

            /* Check the consistency between SW_TFCB and the contain of HW_TFCB. */
            ASSERT(prSwTfcb->u2OverallBufferLength ==
                (prMsduInfo->ucMacHeaderLength + prMsduInfo->u2PayloadLength));
        }

        //4 <2> Fill Payload_length Field
        prHwTfcb->u2PayloadLength = prMsduInfo->u2PayloadLength & TFCB_PAYLOAD_LEN_MASK;
#if SUPPORT_WAPI
        if (prAdapter->fgUseWapi && prMsduInfo->fgIs802_11Frame &&
            !prMsduInfo->fgIsFromInternalProtocolStack){
            prHwTfcb->u2PayloadLength += (prMsduInfo->ucLLCLength + ETHER_TYPE_LEN);
            if (prMsduInfo->ucChkSumWapiFlag & TX_WPI_ENCRYPT)
                prHwTfcb->u2PayloadLength += (KEYID_LEN + KEYID_RSV_LEN + PN_LEN + WPI_MIC_LEN);
        }
#endif

    }


    //4 <3> Fill Packet_ID Field
#if CFG_TX_DBG_INCREASED_PID
    {
        P_TX_ACQ_PARAMETERS_T prTxACQPara;

        prTxACQPara = &prTxCtrl->arTxACQPara[prSwTfcb->ucAC];
        prSwTfcb->ucPID = prTxACQPara->ucPacketID++ & TFCB_PID_MASK;
        prTxACQPara->ucPacketID &= TFCB_PID_MASK; /* For next packet */
        prHwTfcb->ucWlanIdxCSUMPID = prSwTfcb->ucPID;
    };
#elif CFG_TX_DBG_FIXED_PID
    prSwTfcb->ucPID = prSwTfcb->ucAC & TFCB_PID_MASK;
    prHwTfcb->ucWlanIdxCSUMPID = prSwTfcb->ucPID;
#else
    prHwTfcb->ucWlanIdxCSUMPID = 0;
#endif /* CFG_TX_DBG_INCREASED_PID */

    //4 <4>Fill I, UT Field
#if CFG_TCP_IP_CHKSUM_OFFLOAD
    if (!prMsduInfo->fgIsFromInternalProtocolStack) {
    #if SUPPORT_WAPI
        if ((prMsduInfo->ucChkSumWapiFlag & TX_WPI_ENCRYPT) ||
            (prMsduInfo->ucChkSumWapiFlag & TX_WPI_OPEN)) {
            /* Not set the IP check sum */
        }
        else
    #endif
    #if CFG_TX_FRAGMENT
        if (prMsduInfo->ucFragTotalCount == 1)
    #endif
        {
            if (prAdapter->u4CSUMFlags &
                (CSUM_OFFLOAD_EN_TX_TCP |
                 CSUM_OFFLOAD_EN_TX_UDP |
                 CSUM_OFFLOAD_EN_TX_IP)) {
                prHwTfcb->ucWlanIdxCSUMPID |=
                    (prMsduInfo->ucChkSumWapiFlag & TX_CS_IP_GEN) ? TFCB_FLAG_IP_CSUM : 0;
                prHwTfcb->ucWlanIdxCSUMPID |=
                    (prMsduInfo->ucChkSumWapiFlag & TX_CS_TCP_UDP_GEN) ? TFCB_FLAG_TCP_UDP_CSUM : 0;
            }
        }
    }
#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */

    //4 <5> Fill WLAN_Idx Field
    prHwTfcb->ucWlanIdxCSUMPID |= (TFCB_WLAN_INDEX_DEFAULT << TFCB_WLAN_INDEX_OFFSET);

    //4 <6> Fill TID, NP, BR, DU, NA Field
    prHwTfcb->ucFlagTID = (prMsduInfo->ucTID & (UINT_8)TFCB_TID_MASK);

    if (prMsduInfo->ucControlFlag & MSDU_INFO_CTRL_FLAG_BASIC_RATE) {
        prHwTfcb->ucFlagTID |= TFCB_FLAG_BR;
    }

    if (prMsduInfo->ucControlFlag & MSDU_INFO_CTRL_FLAG_NO_ACK) {
        prHwTfcb->ucFlagTID |= TFCB_FLAG_NA;
    }

    //4 <7> Fill TFCB_checksum Field
#if CFG_TX_DBG_TFCB_CHKSUM
    {
        UINT_32 u4TFCBChksum = 0, u4DWValue = 0;
        PUINT_32 pu4TFCB = (PUINT_32)&prHwTfcb->ucDA[0];
        UINT_32 i;

        for (i = 0; i < (sizeof(HW_TFCB_T)/sizeof(UINT_32)); i++) {
            u4DWValue = *pu4TFCB++;
            for (;(u4DWValue);(u4DWValue >>= TFCB_CHECKSUM_BIT_WIDTH))
                u4TFCBChksum += (u4DWValue & (UINT_32)TFCB_CHKSUM_MASK);
        }
        u4TFCBChksum = (~u4TFCBChksum & (UINT_32)TFCB_CHKSUM_MASK);
        prHwTfcb->u2PayloadLength |= (UINT_16)(u4TFCBChksum << TFCB_CHECKSUM_OFFSET);
    }
#endif /* CFG_TX_DBG_TFCB_CHKSUM */

    return;

} /* end of halTxComposeFrameControlBlock() */


#if CFG_TX_FRAGMENT
/*----------------------------------------------------------------------------*/
/*!
* \brief In this function, we compose the 1st fragment frame into frag coalescing
*        buffer (prAdapter->pucFragCoalescingBufCached).
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prMsduInfo     Pointer of MSDU_INFO_T
* \param[in] prSwTfcb       Pointer of SW_TFCB_T
* \param[out] pucOutputBuf  Pointer of the output buffer
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halTxComposeFirstFragInCoalescingBuf (
    IN P_ADAPTER_T      prAdapter,
    IN P_MSDU_INFO_T    prMsduInfo,
    IN P_SW_TFCB_T      prSwTfcb,
    IN OUT PUINT_8      pucOutputBuf
    )
{
    P_HW_TFCB_T prHwTfcb = (P_HW_TFCB_T)pucOutputBuf;

    DEBUGFUNC("halTxComposeFirstFragInCoalescingBuf");

    ASSERT(prAdapter);
    ASSERT(prMsduInfo);
    ASSERT(prSwTfcb);
    ASSERT(pucOutputBuf);

    if (prMsduInfo->fgIsFromInternalProtocolStack) {
        if (prMsduInfo->fgIs802_11Frame) {
            PUINT_8 pucFrameBuf;
            P_MGT_PACKET_T prMgtPacket = (P_MGT_PACKET_T)prMsduInfo->pvPacket;

            pucFrameBuf = MGT_PACKET_GET_BUFFER(prMgtPacket);

            ASSERT(MGT_PACKET_GET_LENGTH(prMgtPacket) ==
                (UINT_32)(prMsduInfo->ucMacHeaderLength + prMsduInfo->u2PayloadLength));

            kalMemCopy((PVOID)&pucOutputBuf[TFCB_SIZE],
                       pucFrameBuf,
                       ((UINT_32)prMsduInfo->ucMacHeaderLength + (UINT_32)prMsduInfo->u2PayloadLength));

            halTxComposeFrameControlBlock(prAdapter, prSwTfcb, NULL, prHwTfcb);

        }
        else {
            ASSERT(0); /* Check txFragMmpdu(), we didn't support in this release */
        }
    }
    else {

        if (prMsduInfo->fgIs802_11Frame) {
            ASSERT(0); /* Check txFragMsduFromOS(), we didn't support in this release */
        }
        else {
            ETH_FRAME_T rEthFrame;
            UINT_16 u2FrameOffset;
            UINT_16 u2PayloadOffset;

            u2FrameOffset = TFCB_SIZE;
            u2FrameOffset += prMsduInfo->ucFragWlanHeaderLength;

            /* Decide the address of MPDU's payload */
            u2PayloadOffset = u2FrameOffset;
            if (prMsduInfo->pucLLC) {
                u2FrameOffset += (prMsduInfo->ucLLCLength + ETHER_TYPE_LEN);
                u2FrameOffset -= ETHER_HEADER_LEN;
            }
            else {
                u2FrameOffset -= ETHER_HEADER_LEN;
            }

            kalCopyFrame(prAdapter->prGlueInfo,
                         prMsduInfo->pvPacket,
                         &pucOutputBuf[u2FrameOffset]);

            DBGLOG_MEM8(KEVIN, TEMP, &pucOutputBuf[u2FrameOffset],
                (prMsduInfo->ucMacHeaderLength + prMsduInfo->u2PayloadLength));

            kalMemCopy(&rEthFrame.aucDestAddr[0],
                       &pucOutputBuf[u2FrameOffset],
                       ETHER_HEADER_LEN);

            /* Update the field of IP/TCP checksum */
            if (prMsduInfo->ucControlFlag & MSDU_INFO_CTRL_FLAG_CALCULATE_CSUM) {
                /* Call function of checksum offload */
                utilTxComputeCSUM(&pucOutputBuf[u2FrameOffset], prMsduInfo->ucMacHeaderLength + prMsduInfo->u2PayloadLength);
            }

            /* Overwrite the DA/SA field in coalescing buffer */
            if (prMsduInfo->pucLLC) {
                kalMemCopy((PVOID)&pucOutputBuf[u2PayloadOffset],
                           (PVOID)prMsduInfo->pucLLC,
                           (UINT_32)prMsduInfo->ucLLCLength);
            }

            /* Calculate MIC, the start address of payload may not at DW boundary */
            if (prMsduInfo->ucControlFlag & MSDU_INFO_CTRL_FLAG_CALCULATE_MIC) {
                UINT_16 u2PayloadLengthWithoutMIC = prMsduInfo->u2PayloadLength;

                if (prMsduInfo->pucLLC) {
                    u2PayloadLengthWithoutMIC +=
                        (prMsduInfo->ucLLCLength + ETHER_TYPE_LEN);
                }

                tkipMicEncapsulate(prAdapter,
                    &rEthFrame.aucDestAddr[0],
                    &rEthFrame.aucSrcAddr[0],
                    prMsduInfo->ucTID,
                    u2PayloadLengthWithoutMIC,
                    &pucOutputBuf[u2PayloadOffset],
                    &pucOutputBuf[u2PayloadOffset + u2PayloadLengthWithoutMIC]);
            }

            halTxComposeFrameControlBlock(prAdapter, prSwTfcb, NULL, prHwTfcb);

            txFragComposeWlanDataFrameHeader(prAdapter,
                                             &rEthFrame,
                                             prMsduInfo->ucTID,
                                             &pucOutputBuf[TFCB_SIZE]);
        }
    }

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief In this function, we compose the 2nd~last fragment frame into frag
*        coalescing buffer (prAdapter->pucFragCoalescingBufCached).
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prMsduInfo     Pointer of MSDU_INFO_T
* \param[in] prSwTfcb       Pointer of SW_TFCB_T
*
* \return Pointer of the output buffer
*/
/*----------------------------------------------------------------------------*/
PUINT_8
halTxComposeTfcbFragFrame (
    IN P_ADAPTER_T      prAdapter,
    IN P_MSDU_INFO_T    prMsduInfo,
    IN P_SW_TFCB_T      prSwTfcb
    )
{
    PUINT_8 pucOutputBuf; /* Pointer to TFCB Frame */
    P_HW_TFCB_T prHwTfcb;
    P_WLAN_MAC_HEADER_T prWlanHeader;
    UINT_16 u2FrameCtrl;
    UINT_16 u2SeqCtrl;

    DEBUGFUNC("halTxComposeTfcbFragFrame");

    ASSERT(prAdapter);
    ASSERT(prMsduInfo);
    ASSERT(prSwTfcb);

    pucOutputBuf = prAdapter->pucFragCoalescingBufCached;
    prWlanHeader = (P_WLAN_MAC_HEADER_T)&pucOutputBuf[TFCB_SIZE];
    prHwTfcb = (P_HW_TFCB_T)&pucOutputBuf[0];

    ASSERT((UINT_32)(prSwTfcb->u2OverallBufferLength) <= \
        prAdapter->u4FragCoalescingBufCachedSize);

    //4 <1> Compose 1st Fragmentation TFCB frame.
    if (prMsduInfo->ucFragFinishedCount == 0) {

        //4 <1.A> Clear the frag common coalescing buffer for debug.
        //kalMemZero(prAdapter->pucFragCoalescingBufCached,
            //prAdapter->u4FragCoalescingBufCachedSize); // For debug, mark later for speeding up the process.


        //4 <1.B> Copy MSDU into coalescing buffer and return the first fragment
        halTxComposeFirstFragInCoalescingBuf(prAdapter,
                                             prMsduInfo,
                                             prSwTfcb,
                                             pucOutputBuf);

        //4 <1.C> Update FC - More Fragment & Fragment No. of WLAN Header.
        WLAN_GET_FIELD_16(&prWlanHeader->u2FrameCtrl, &u2FrameCtrl);
        u2FrameCtrl |= MASK_FC_MORE_FRAG;

        if (prMsduInfo->ucControlFlag & MSDU_INFO_CTRL_FLAG_DISABLE_PRIVACY_BIT)
            u2FrameCtrl &= ~MASK_FC_PROTECTED_FRAME;

        WLAN_SET_FIELD_16(&prWlanHeader->u2FrameCtrl, u2FrameCtrl);
    }
    //4 <2> Compose 2nd~Last Fragmentation TFCB frame.
    else {
        UINT_16 u2PayloadOffset;
        UINT_16 u2CurrentFragPayloadOffset;
        UINT_16 u2FragPayloadLen;

        u2PayloadOffset = TFCB_SIZE;
        u2PayloadOffset += prMsduInfo->ucFragWlanHeaderLength;

        u2CurrentFragPayloadOffset = u2PayloadOffset +
                                     (prMsduInfo->u2PayloadFragThreshold *
                                      prMsduInfo->ucFragFinishedCount);

        DBGLOG(TX, INFO, ("u2PayloadOffset = %d, u2CurrentFragPayloadOffset = %d\n",
            u2PayloadOffset, u2CurrentFragPayloadOffset));

        // For 1st ~ (N-1)th MPDU
        if (prMsduInfo->ucFragFinishedCount < (prMsduInfo->ucFragTotalCount - 1)) {
            u2FragPayloadLen = prMsduInfo->u2PayloadFragThreshold;
        }
        // For the last (Nth) MPDU
        else {
            UINT_16 u2OverallPayloadLength = prMsduInfo->u2PayloadLength;

            if (prMsduInfo->pucLLC) {
                u2OverallPayloadLength += (prMsduInfo->ucLLCLength + ETHER_TYPE_LEN);
            }

            if (prMsduInfo->ucControlFlag & MSDU_INFO_CTRL_FLAG_CALCULATE_MIC) {
                u2OverallPayloadLength += TKIP_MIC_LEN;
            }

            u2FragPayloadLen = u2OverallPayloadLength -
                               (prMsduInfo->u2PayloadFragThreshold *
                                prMsduInfo->ucFragFinishedCount);

            DBGLOG(TX, INFO, ("u2OverallPayloadLength = %d\n", u2OverallPayloadLength));
        }

        DBGLOG(TX, INFO, ("u2FragPayloadLen = %d\n", u2FragPayloadLen));

        //4 <2.A> Copy current MPDU's payload to the right position
        kalMemCopy((PVOID)&pucOutputBuf[u2PayloadOffset],
                   (PVOID)&pucOutputBuf[u2CurrentFragPayloadOffset],
                   (UINT_32)u2FragPayloadLen);

        //4 <2.B> Compose HW TFCB for current MPDU - Update PID/Payload Length/TFCB Checksum
        halTxComposeFrameControlBlock(prAdapter, prSwTfcb, NULL, prHwTfcb);

        //4 <2.C> Update FC - More Fragment & Fragment No. of WLAN Header.
        if ((prMsduInfo->ucFragFinishedCount + 1) == prMsduInfo->ucFragTotalCount) {
            WLAN_GET_FIELD_16(&prWlanHeader->u2FrameCtrl, &u2FrameCtrl);
            u2FrameCtrl &= ~MASK_FC_MORE_FRAG;
            WLAN_SET_FIELD_16(&prWlanHeader->u2FrameCtrl, u2FrameCtrl);
        }

        WLAN_GET_FIELD_16(&prWlanHeader->u2SeqCtrl, &u2SeqCtrl);
        u2SeqCtrl = (prMsduInfo->ucFragFinishedCount & MASK_SC_FRAG_NUM);
        WLAN_SET_FIELD_16(&prWlanHeader->u2SeqCtrl, u2SeqCtrl);

    }

    return pucOutputBuf;

} /* end of halTxComposeTfcbFragFrame() */


#endif /* CFG_TX_FRAGMENT */


#if CFG_SDIO_TX_ENHANCE
/*----------------------------------------------------------------------------*/
/*!
* \brief In this function, we'll check if we can aggregate more frame to the
*        coalescing buffer according the TFCB frame's u2OverallBufferLength and
*        then return the Pointer of the output buffer for memory copy later.
*
* \param[in] prAdapter              Pointer to the Adapter structure.
* \param[in] u2OverallBufferLength  Outgoing TFCB Frame's length for aggregation
* \param[in] ppucOutputBuf          Pointer to Pointer of output buffer
*
* \retval TRUE  Bus access ok
* \retval FALSE Bus access error
*/
/*----------------------------------------------------------------------------*/
BOOL
halTxAggregateMpdu (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_16      u2OverallBufferLength,
    IN PPUINT_8     ppucOutputBuf
    )
{
    P_TX_CTRL_T prTxCtrl;
    UINT_32 u4BlkNumToBeUsed;
    BOOL fgResult = TRUE;

    ASSERT(prAdapter);
    prTxCtrl = &prAdapter->rTxCtrl;

    u4BlkNumToBeUsed = ((UINT_32)u2OverallBufferLength +
                        (prTxCtrl->u4WriteBlockSize - 1)) /
                        (prTxCtrl->u4WriteBlockSize);

    if ((u4BlkNumToBeUsed + prTxCtrl->u4TxCoalescingBufUsedBlkCount) >
        prTxCtrl->u4TxCoalescingBufMaxBlkNum) {

        UINT_16 u2AggregateTFCBFrameLength =
            (UINT_16)(prTxCtrl->u4TxCoalescingBufUsedBlkCount *
                      prTxCtrl->u4WriteBlockSize);

        HAL_PORT_WR(prAdapter,
            MCR_HTDR,
            TFCB_FRAME_PAD_TO_DW(u2AggregateTFCBFrameLength),
            prAdapter->pucCoalescingBufCached,
            (UINT_16)prAdapter->u4CoalescingBufCachedSize);

    #if CFG_SDIO_DEBUG_AGGREGATING_RATIO
        prTxCtrl->u4TxSDIOCmdCount++;
    #endif /* CFG_SDIO_DEBUG_AGGREGATING_RATIO */

        *ppucOutputBuf = prAdapter->pucCoalescingBufCached;

        prTxCtrl->pucTxCoalescingBufPtr =
            prAdapter->pucCoalescingBufCached +
            (u4BlkNumToBeUsed * prTxCtrl->u4WriteBlockSize);

        prTxCtrl->u4TxCoalescingBufUsedBlkCount = u4BlkNumToBeUsed;

    }
    else {
        *ppucOutputBuf = prTxCtrl->pucTxCoalescingBufPtr;

        prTxCtrl->pucTxCoalescingBufPtr +=
            (u4BlkNumToBeUsed * prTxCtrl->u4WriteBlockSize);

        prTxCtrl->u4TxCoalescingBufUsedBlkCount += u4BlkNumToBeUsed;
    }

    return fgResult;

} /* end of halTxAggregateMpdu() */


/*----------------------------------------------------------------------------*/
/*!
* \brief In this function, we'll check if we still have remain frame in coalescing
*        buffer, because no more TFCB frame for aggregation, thus we write the
*        remain frame to data port immediately.
*
* \param[in] prAdapter              Pointer to the Adapter structure.
*
* \retval TRUE  Bus access ok
* \retval FALSE Bus access error
*/
/*----------------------------------------------------------------------------*/
BOOL
halTxLeftClusteredMpdu (
    IN P_ADAPTER_T  prAdapter
    )
{
    P_TX_CTRL_T prTxCtrl;
    BOOL fgResult = TRUE;

    ASSERT(prAdapter);

    prTxCtrl = &prAdapter->rTxCtrl;

    if (prTxCtrl->u4TxCoalescingBufUsedBlkCount) {

        UINT_16 u2AggregateTFCBFrameLength =
            (UINT_16)(prTxCtrl->u4TxCoalescingBufUsedBlkCount *
                      prTxCtrl->u4WriteBlockSize);

        HAL_PORT_WR(prAdapter,
            MCR_HTDR,
            TFCB_FRAME_PAD_TO_DW(u2AggregateTFCBFrameLength),
            prAdapter->pucCoalescingBufCached,
            (UINT_16)prAdapter->u4CoalescingBufCachedSize);

    #if CFG_SDIO_DEBUG_AGGREGATING_RATIO
        prTxCtrl->u4TxSDIOCmdCount++;
    #endif /* CFG_SDIO_DEBUG_AGGREGATING_RATIO */

        prTxCtrl->pucTxCoalescingBufPtr =
            prAdapter->pucCoalescingBufCached;

        prTxCtrl->u4TxCoalescingBufUsedBlkCount = 0;

    }

    return fgResult;

} /* end of halTxLeftClusteredMpdu() */
#endif /* CFG_SDIO_TX_ENHANCE */


/*----------------------------------------------------------------------------*/
/*!
* \brief In this function, we'll write frame(MSDU_INFO_T) into data port, we'll
*        also compose fragment frame here if MGMT Layer request to do so.
*
* \param[in] prAdapter              Pointer to the Adapter structure
* \param[in] prMsduInfo             Pointer of MSDU_INFO_T
* \param[in] prTFCBsReadyToHwFIFO   Pointer to the queue of outgoing SW_TFCB_Ts
* \param[in] fgIsAggregate          True if require aggregation
*
* \retval TRUE  Bus access ok
* \retval FALSE Bus access error
*/
/*----------------------------------------------------------------------------*/
BOOL
halTxTfcbs (
    IN P_ADAPTER_T      prAdapter,
    IN P_MSDU_INFO_T    prMsduInfo,
    IN P_QUE_T          prTFCBsReadyToHwFIFO
#if CFG_SDIO_TX_ENHANCE
    ,IN BOOLEAN         fgIsAggregate
#endif /* CFG_SDIO_TX_ENHANCE */
    )
{
    P_TX_CTRL_T prTxCtrl;
    P_SW_TFCB_T prSwTfcb;
    P_TX_ACQ_PARAMETERS_T prTxACQPara;
    P_QUE_T prActiveChainList;
    HW_TFCB_T rHwTfcb;

    PUINT_8 pucOutputBuf = (PUINT_8)NULL; /* Pointer to TFCB Frame */

    UINT_16 u2ValidBufSize;
    BOOL fgResult = TRUE;

    BOOLEAN fgIsFrameContentNeedRestore = FALSE;

#if CFG_SDIO_TX_ENHANCE
    BOOLEAN fgIsTFCBFrameInSDIOCoalescingBuf;
#endif /* CFG_SDIO_TX_ENHANCE */

    DEBUGFUNC("halTxTfcbs");

    ASSERT(prAdapter);
    ASSERT(prMsduInfo);
    ASSERT(prTFCBsReadyToHwFIFO);

    prTxCtrl = &prAdapter->rTxCtrl;

    do {

        QUEUE_REMOVE_HEAD(prTFCBsReadyToHwFIFO, prSwTfcb, P_SW_TFCB_T);
        if (!prSwTfcb) {
            fgResult = FALSE;
            ASSERT(prSwTfcb);
            break;
        }

#if CFG_SDIO_TX_ENHANCE
        fgIsTFCBFrameInSDIOCoalescingBuf = FALSE;

    #if CFG_SDIO_DEBUG_AGGREGATING_RATIO
        prTxCtrl->u4TxPacketCount++;
    #endif /* CFG_SDIO_DEBUG_AGGREGATING_RATIO */

#endif /* CFG_SDIO_TX_ENHANCE */


        u2ValidBufSize = (UINT_16)TFCB_FRAME_PAD_TO_DW(prSwTfcb->u2OverallBufferLength);

#if CFG_TX_FRAGMENT
        /* TX fragmentation, one MSDU has several MPDUs */
        if (prMsduInfo->ucFragTotalCount > 1) {
            pucOutputBuf = halTxComposeTfcbFragFrame(prAdapter,
                                                     prMsduInfo,
                                                     prSwTfcb);

    #if CFG_TX_RET_TX_CTRL_EARLY
            /* Free the original buffer immediately once it copy to coalescing buffer */
            if (prMsduInfo->pvPacket && !prMsduInfo->fgIsFromInternalProtocolStack) {
                kalSendComplete(prAdapter->prGlueInfo, prMsduInfo->pvPacket, WLAN_STATUS_SUCCESS);
                prMsduInfo->pvPacket = NULL;
            }
    #endif /* CFG_TX_RET_TX_CTRL_EARLY && CFG_TX_RET_TX_CTRL_EARLY */

            u2ValidBufSize = (UINT_16)prAdapter->u4FragCoalescingBufCachedSize;

        }
        else
#endif /* CFG_TX_FRAGMENT */
        {
            /* Only one TFCB if not fragment */
            ASSERT(QUEUE_IS_EMPTY(prTFCBsReadyToHwFIFO));

            if (prTxCtrl->fgIsRfTestTxMode) {

                pucOutputBuf = RFTEST_BUFENT_GET_BUFFER(prMsduInfo->pvPacket);

                halTxComposeFrameControlBlock(prAdapter,
                                              prSwTfcb,
                                              NULL,
                                              &rHwTfcb);

                ASSERT(pucOutputBuf);
                kalMemCopy((PVOID)pucOutputBuf,
                           (PVOID)&rHwTfcb,
                           TFCB_SIZE);

                u2ValidBufSize = RF_AT_PARAM_TX_DATA_STRUCT_MAX;

            }
            //4 <1> Process MPDU which is coming from Internal Protocol Stack, no memory copy.
            else if (prMsduInfo->fgIsFromInternalProtocolStack) {
                //4 <1.1> Process 802.11 Frame.
                if (prMsduInfo->fgIs802_11Frame) {
                    P_MGT_PACKET_T prMgtPacket = (P_MGT_PACKET_T)prMsduInfo->pvPacket;

                    pucOutputBuf = MGT_PACKET_GET_BUFFER(prMgtPacket);

                    /* Check the reserved buffer of MGMT Packet */
                    if (mgtPacketCheckHeadroom(prMgtPacket, TFCB_SIZE)) {
                        pucOutputBuf -= TFCB_SIZE;
                    }
                    else {
                        ASSERT_REPORT(0, ("Reserved space in MGT Frame is not enough for TFCB\n"));
                        DBGLOG(TX, ERROR, ("Reserved space in MGT Frame is not enough for TFCB\n"));
                        /* Shouldn't enter here, or we will transmit an abnormal frame */
                    }

                    halTxComposeFrameControlBlock(prAdapter,
                                                  prSwTfcb,
                                                  NULL,
                                                  &rHwTfcb);

                    kalMemCopy((PVOID)pucOutputBuf,
                               (PVOID)&rHwTfcb,
                               TFCB_SIZE);

                }
                //4 <1.2> Process 802.3/Ethernet Frame.
                else {
                    P_ETH_FRAME_T prEthFrame;


                    pucOutputBuf = MGT_PACKET_GET_BUFFER(prMsduInfo->pvPacket);

                    prEthFrame = (P_ETH_FRAME_T)pucOutputBuf;

                    halTxComposeFrameControlBlock(prAdapter,
                                                  prSwTfcb,
                                                  &prEthFrame->aucDestAddr[0],
                                                  &rHwTfcb);

                    /* Overwrite the Source Address field with TFCB value without backup */
                    kalMemCopy((PVOID)(&pucOutputBuf[MAC_ADDR_LEN]),
                               (PVOID)(&rHwTfcb.u2LifeTimeQIdx),
                               (TFCB_SIZE - MAC_ADDR_LEN));
                }


                {
                    P_MGT_BUF_INFO_T prMgtBufInfo = &prAdapter->rMgtBufInfo;

                    if ((pucOutputBuf >= prMgtBufInfo->pucMgtBufPoolCached) &&
                        (pucOutputBuf < (prMgtBufInfo->pucMgtBufPoolCached + MGT_BUFFER_SIZE))) {
                        u2ValidBufSize = (UINT_16)(MGT_BUFFER_SIZE -
                            ((UINT_32)pucOutputBuf - (UINT_32)prMgtBufInfo->pucMgtBufPoolCached));
                    }
                    else {
                        ASSERT(0);
                    }
                }
            }
            //4 <2> Process MPDU which is coming from OS.
            else {

//4 <2A> Copy the frame to internal coalescing buffer before compose TFCB in it
#if CFG_TX_BUFFER_IS_SCATTER_LIST

    #if CFG_SDIO_TX_ENHANCE
                if (fgIsAggregate) {
                    if (halTxAggregateMpdu(prAdapter,
                                           prSwTfcb->u2OverallBufferLength,
                                           &pucOutputBuf) == FALSE) {

                        DBGLOG(TX, WARN, ("Write frame fail\n"));

                        /* Tx TFCB fail, let caller handle this TFCB */
                        QUEUE_INSERT_HEAD(prTFCBsReadyToHwFIFO, &prSwTfcb->rQueEntry);

                        break;
                    }

                    fgIsTFCBFrameInSDIOCoalescingBuf = TRUE;
                }
                else
    #endif /* CFG_SDIO_TX_ENHANCE */
                {
    #if CFG_TX_FRAGMENT
                    ASSERT((UINT_32)(prSwTfcb->u2OverallBufferLength) <= \
                        prAdapter->u4FragCoalescingBufCachedSize);

                    pucOutputBuf = prAdapter->pucFragCoalescingBufCached;

                    u2ValidBufSize = (UINT_16)prAdapter->u4FragCoalescingBufCachedSize;
    #else
                    ASSERT((UINT_32)(prSwTfcb->u2OverallBufferLength) <= \
                        prAdapter->u4CoalescingBufCachedSize);

                    pucOutputBuf = prAdapter->pucCoalescingBufCached;

                    u2ValidBufSize = (UINT_16)prAdapter->u4CoalescingBufCachedSize;
    #endif /* CFG_TX_FRAGMENT */
                }

                //4 <2A.1> Process 802.11 Frame.
                if (prMsduInfo->fgIs802_11Frame) {
                    #if SUPPORT_WAPI
                    if (prAdapter->fgUseWapi && !prMsduInfo->fgIsFromInternalProtocolStack &&
                        ((prMsduInfo->ucChkSumWapiFlag & TX_WPI_ENCRYPT) ||
                        (prMsduInfo->ucChkSumWapiFlag & TX_WPI_OPEN))) {
                        pucOutputBuf = halTxComposeWpiPktInCoalescingBuf(prAdapter,
                                                          prMsduInfo,
                                                          prSwTfcb);
                    }
                    else
                    #endif
                    {
                        kalCopyFrame(prAdapter->prGlueInfo,
                                     prMsduInfo->pvPacket,
                                     &pucOutputBuf[TFCB_SIZE]);

                        halTxComposeFrameControlBlock(prAdapter,
                                                      prSwTfcb,
                                                      NULL,
                                                      &rHwTfcb);

                        kalMemCopy((PVOID)pucOutputBuf,
                                   (PVOID)&rHwTfcb,
                                   TFCB_SIZE);
                    }
                }
                //4 <2A.2> Process 802.3/Ethernet Frame.
                else {
                    P_ETH_FRAME_T prEthFrame;


                    kalCopyFrame(prAdapter->prGlueInfo,
                                 prMsduInfo->pvPacket,
                                 &pucOutputBuf[0]);

                    prEthFrame = (P_ETH_FRAME_T)pucOutputBuf;

                    halTxComposeFrameControlBlock(prAdapter,
                                                  prSwTfcb,
                                                  &prEthFrame->aucDestAddr[0],
                                                  &rHwTfcb);

                    kalMemCopy((PVOID)&pucOutputBuf[MAC_ADDR_LEN],
                               (PVOID)&rHwTfcb.u2LifeTimeQIdx,
                               (TFCB_SIZE - MAC_ADDR_LEN));
                }

    #if CFG_TX_RET_TX_CTRL_EARLY
                if (prMsduInfo->pvPacket) {
                    kalSendComplete(prAdapter->prGlueInfo, prMsduInfo->pvPacket, WLAN_STATUS_SUCCESS);
                    prMsduInfo->pvPacket = NULL;
                }
    #endif /* CFG_TX_RET_TX_CTRL_EARLY */


//4 <2B> Compose TFCB and overwrite the content of original frame buffer.
#else /* !CFG_TX_BUFFER_IS_SCATTER_LIST */

/* NOTE(Kevin): If we didn't use any coalescing buffer for LINUX, we should
 * note that:
 * 1. SW will replace the Source Address Field of outgoing ethernet frame before
 *    write it to HW AC FIFO. So if we use this driver in Gateway Router, the BCAST
 *    ethernet frame may get abnormal(wrong SA field) in another network interface.
 * 2. SW will access some bytes after the last byte of incoming ethernet frame for
 *    DW padding. It may be illegal to access memory outside the boundary of frame
 *    buffer.(I think this won't happen in Linux).
 * 3. Apply such scheme for 802.3 frame only.
 */

                //4 <2B.1> Process 802.11 Frame.
                if (prMsduInfo->fgIs802_11Frame) {
                    #if SUPPORT_WAPI
                    if (prAdapter->fgUseWapi && !prMsduInfo->fgIsFromInternalProtocolStack &&
                        ((prMsduInfo->ucChkSumWapiFlag & TX_WPI_ENCRYPT) ||
                        (prMsduInfo->ucChkSumWapiFlag & TX_WPI_OPEN))) {
                        pucOutputBuf = halTxComposeWpiPktInCoalescingBuf(prAdapter,
                                                          prMsduInfo,
                                                          prSwTfcb);
                    }
                    else
                    #endif
                    {
    #if defined(LINUX)
                        DBGLOG(TX, ERROR,
                            ("Can't handle Native 802.11 frame for LINUX in this version."));
    #endif /* LINUX */

                        /* Tx TFCB abort, let caller handle this TFCB */
                        QUEUE_INSERT_HEAD(prTFCBsReadyToHwFIFO, &prSwTfcb->rQueEntry);
                        fgResult = FALSE;
                        break;
                    }
                }
                //4 <2B.2> Process 802.3/Ethernet Frame.
                else {
                    P_ETH_FRAME_T prEthFrame;


                    pucOutputBuf = kalQueryBufferPointer(prAdapter->prGlueInfo,
                                                         prMsduInfo->pvPacket);

                    ASSERT(pucOutputBuf);

                    prEthFrame = (P_ETH_FRAME_T)pucOutputBuf;

                    halTxComposeFrameControlBlock(prAdapter,
                                                  prSwTfcb,
                                                  &prEthFrame->aucDestAddr[0],
                                                  &rHwTfcb);

                    /* Backup Source Address of ethernet frame to &rHwTfcb.ucDA[0] */
                    kalMemCopy((PVOID)(&rHwTfcb.ucDA[0]),
                               (PVOID)(&prEthFrame->aucSrcAddr[0]),
                               MAC_ADDR_LEN);

                    /* Overwrite the Source Address field with TFCB value */
                    kalMemCopy((PVOID)(&pucOutputBuf[MAC_ADDR_LEN]),
                               (PVOID)(&rHwTfcb.u2LifeTimeQIdx),
                               (TFCB_SIZE - MAC_ADDR_LEN));

                    fgIsFrameContentNeedRestore = TRUE;


                    u2ValidBufSize = (UINT_16)kalQueryValidBufferLength(prAdapter->prGlueInfo,
                                                                        prMsduInfo->pvPacket);

                }

#endif /* CFG_TX_BUFFER_IS_SCATTER_LIST */

            }
        }

        //DBGLOG_MEM8(KEVIN, TEMP, pucOutputBuf, prSwTfcb->u2OverallBufferLength);

#if CFG_SDIO_TX_ENHANCE
        /* NOTE: Here we handle the case for supporting Aggregation of Fragmentation Frames.
         */
        if (fgIsAggregate) {
            if (!fgIsTFCBFrameInSDIOCoalescingBuf) {
                PUINT_8 pucCoalescingBuffer;

                if (halTxAggregateMpdu(prAdapter,
                                       prSwTfcb->u2OverallBufferLength,
                                       &pucCoalescingBuffer) == FALSE) {

                    DBGLOG(TX, WARN, ("Write frame fail\n"));

                    /* Tx TFCB fail, let caller handle this TFCB */
                    QUEUE_INSERT_HEAD(prTFCBsReadyToHwFIFO, &prSwTfcb->rQueEntry);

                    break;
                }

                kalMemCopy((PVOID)pucCoalescingBuffer,
                           (PVOID)pucOutputBuf,
                           prSwTfcb->u2OverallBufferLength);

                fgIsTFCBFrameInSDIOCoalescingBuf = TRUE;
            }
        }
        else
#endif /* CFG_SDIO_TX_ENHANCE */
        {
            HAL_PORT_WR(prAdapter,
                        MCR_HTDR,
                        TFCB_FRAME_PAD_TO_DW(prSwTfcb->u2OverallBufferLength),
                        (PUINT_8)pucOutputBuf,
                        u2ValidBufSize);

#if CFG_SDIO_DEBUG_AGGREGATING_RATIO
            prTxCtrl->u4TxSDIOCmdCount++;
#endif /* CFG_SDIO_DEBUG_AGGREGATING_RATIO */
        }

        /* Restore the original Source Address field of ethernet frame */
        if (fgIsFrameContentNeedRestore) {
            P_ETH_FRAME_T prEthFrame;

            prEthFrame = (P_ETH_FRAME_T)pucOutputBuf;

            kalMemCopy((PVOID)(&prEthFrame->aucSrcAddr[0]),
                       (PVOID)&rHwTfcb.ucDA[0],
                       MAC_ADDR_LEN);
        }

        if (fgResult) {
            prTxACQPara = &prTxCtrl->arTxACQPara[prSwTfcb->ucAC];
            prActiveChainList = &prTxACQPara->rActiveChainList;
            QUEUE_INSERT_TAIL(prActiveChainList, &prSwTfcb->rQueEntry);

            /* Update the bitmap of "Nonempty AC Queues" */
            prTxCtrl->ucTxNonEmptyACQ |= BIT(prSwTfcb->ucAC);

            /* Increase 1 once a MPDU has been successfully composed and send to
             * HW FIFO.
             */
            prMsduInfo->ucFragFinishedCount++;

            TX_ACQ_INC_CNT(prTxCtrl, prSwTfcb->ucAC, TX_ACQ_TFCB_COUNT);
        }
        else {

            DBGLOG(TX, WARN, ("Write frame fail\n"));

            /* Tx TFCB fail, let caller handle this TFCB */
            QUEUE_INSERT_HEAD(prTFCBsReadyToHwFIFO, &prSwTfcb->rQueEntry);

            break;
        }
    }
    while (QUEUE_IS_NOT_EMPTY(prTFCBsReadyToHwFIFO));

    return fgResult;

} /* end of halTxTfcbs() */


#if CFG_TX_DBG_TFCB_CHKSUM || CFG_TX_DBG_SEQ_NUM
/*----------------------------------------------------------------------------*/
/*!
* \brief Set the MAC address to the chip
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \param pucMACAddr
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
halTxEnableDebugOption (
    IN P_ADAPTER_T  prAdapter
    )
{
    UINT_32 u4RegValue;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_MSCR, &u4RegValue);

#if CFG_TX_DBG_TFCB_CHKSUM
    u4RegValue |= MSCR_TX_PKT_CS_EN;
#endif /* CFG_TX_DBG_TFCB_CHKSUM */

#if CFG_TX_DBG_SEQ_NUM
    u4RegValue |= MSCR_TX_SEQCTRL_EN;
#endif /* CFG_TX_DBG_SEQ_NUM */

    HAL_MCR_WR(prAdapter, MCR_MSCR, u4RegValue);

    return;
} /* end of halTxEnableTfcbChecksum() */
#endif /* CFG_TX_DBG_TFCB_CHKSUM || CFG_TX_DBG_SEQ_NUM */


/*----------------------------------------------------------------------------*/
/*!
* \brief Function to flush and disable specific queue
*
* \param prAdapter      a pointer to adapter private data structure.
* \param ucFlushQues    bit define value for specific queue flush
* \param ucStopQues     bit define value for specific queue disable
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
halFlushStopQueues (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8 ucFlushQues,
    IN UINT_8 ucStopQues
    )
{
    UINT_32 u4RegValue = 0;

    DEBUGFUNC("halFlushStopQueues");

    ASSERT(prAdapter);

    u4RegValue |= ((ucFlushQues & HW_QUE_MASK) << QCR_QUE_FLUSH_OFFSET);
    u4RegValue |= ((ucStopQues & HW_QUE_MASK) << QCR_QUE_STOP_OFFSET);

    HAL_MCR_WR(prAdapter, MCR_QCR, u4RegValue);

#if DBG
    DBGLOG(HAL, TRACE, ("Write QCR = %08lx\n", u4RegValue));
    HAL_MCR_RD(prAdapter, MCR_QCR, &u4RegValue);
    DBGLOG(HAL, TRACE, ("Read back QCR = %08lx\n", u4RegValue));
#endif /* DBG */

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Function to start the specific queue
*
* \param prAdapter      a pointer to adapter private data structure.
* \param ucStartQues    bit define value for specific queue to start operation
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
halStartQueues (
    IN P_ADAPTER_T     prAdapter,
    IN UINT_8          ucStartQues
    )
{
    UINT_32 u4RegValue = 0;

    DEBUGFUNC("halStartQueues");

    ASSERT(prAdapter);

    u4RegValue = ((ucStartQues & HW_QUE_MASK) << QCR_QUE_START_OFFSET);
    HAL_MCR_WR(prAdapter, MCR_QCR, u4RegValue);

#if DBG
    DBGLOG(HAL, TRACE, ("Write QCR = %08lx\n", u4RegValue));
    HAL_MCR_RD(prAdapter, MCR_QCR, &u4RegValue);
    DBGLOG(HAL, TRACE, ("Read back QCR = %08lx\n", u4RegValue));
#endif /* DBG */

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Function to get the FIFO Queue Info
*
* \param prAdapter      a pointer to adapter private data structure.
* \param rQueueId       the specific queue index
* \param pu4DwOffset    the offset of queue
* \param pu4DwSize    the length of the queue
*
* \return -
*/
/*----------------------------------------------------------------------------*/
BOOL
halGetQueueInfo (
    IN P_ADAPTER_T        prAdapter,
    IN ENUM_QUEUE_ID_T    rQueueId,
    OUT PUINT_32          pu4DwOffset,
    OUT PUINT_32          pu4DwSize
    )
{
    UINT_32 u4QueueId;
    BOOL fgStatus = TRUE;

    DEBUGFUNC("halGetQueueInfo");

    ASSERT(prAdapter);
    ASSERT(pu4DwOffset);
    ASSERT(pu4DwSize);

    /* find scan queue start address */
    for (u4QueueId = 0; u4QueueId < (sizeof(arQInitTbl) / sizeof(QINFO_T));
         u4QueueId++) {
        if (rQueueId == arQInitTbl[u4QueueId].ucQueueId) {
            *pu4DwOffset = arQInitTbl[u4QueueId].u4OffsetDW & BITS(0, 12);
            *pu4DwSize = arQInitTbl[u4QueueId].u4SizeDW;
            break;
        }
    }

    if (u4QueueId >= sizeof(arQInitTbl) / sizeof(QINFO_T)) {
       fgStatus = FALSE;
    }
    return fgStatus;
}


/* autorate */
/*----------------------------------------------------------------------------*/
/*!
* \brief Autorate initialize
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halARInitialize (
    IN  P_ADAPTER_T prAdapter
    )
{
    P_AR_CTRL_T prARCtrl;
    UINT_32 u4ARCR = 0;
    UINT_8 i = 0;

    ASSERT(prAdapter);
    prARCtrl = &prAdapter->rARCtrl;

    for (i = 0; i < WLAN_TABLE_SIZE; i++) {
        prARCtrl->au2ARBits[i] = ARCR_SUPPORT_RATES_DEFAULT;
        prARCtrl->aucARRate1Index[i] = ARCR_54M_IDX;
    }
    u4ARCR = ARCR_WRITE | ARCR_RESET | ((0 & 0xf) << 24) | ((prARCtrl->aucARRate1Index[0] & 0xf) << 16) | prARCtrl->au2ARBits[0];
    HAL_MCR_WR(prAdapter, MCR_ARCR, u4ARCR);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Setup HW Autorate parameter
*
* \param prAdapter               a pointer to adapter private data structure.
* \param u2FailCount_up_limit    up threshold of retry fail count
* \param u2FailCount_down_limit  down threshold of retry fail count
* \param ucARRCParam             Retry count parameter
* \param ucARPERParam            PER parameter
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halARSetParam (
    IN P_ADAPTER_T      prAdapter,
    IN UINT_16          u2FailCount_up_limit,
    IN UINT_16          u2FailCount_down_limit,
    IN UINT_8           ucARRCParam,
    IN UINT_8           ucARPERParam
    )
{
    UINT_32 u4Temp;

    ASSERT(prAdapter);

    ASSERT(ucARRCParam <= 0x3 && ucARPERParam<= 0x3);

    /* Write up/down threshold of retry fail count */
    u4Temp = ((UINT_32)u2FailCount_up_limit << 16) |
                (UINT_32) u2FailCount_down_limit;
    HAL_MCR_WR(prAdapter, MCR_ARPR1, u4Temp);

    /* Write weighting parameters of AR models */
    HAL_MCR_RD(prAdapter, MCR_TXCR, &u4Temp);
    u4Temp &= 0xfffffff0;
    HAL_MCR_WR(prAdapter, MCR_TXCR, u4Temp|ucARRCParam<<2|ucARPERParam);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Set the support rate bitmap and rate1 index for a specific wlan entry
*
* \param prAdapter      a pointer to adapter private data structure.
* \param ucWlanIdx      the wlan table entry index
* \param u2RateSet      the rate set
* \param fgIsShortPreamble use shortpremble or longpremble
* \param ucRate1Index   the rate1 index
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halARSetRate (
    IN P_ADAPTER_T         prAdapter,
    IN UINT_8              ucWlanIdx,
    IN UINT_16             u2RateSet,
    IN BOOLEAN             fgIsShortPreamble,
    IN UINT_8              ucRate1Index
    )
{
    P_AR_CTRL_T prARCtrl;
    UINT_32 u4PreambleOptionIndex =
        (fgIsShortPreamble ? PREAMBLE_OPTION_SHORT : PREAMBLE_DEFAULT_LONG_NONE);

    UINT_16 u2ARBits = 0;
    UINT_32 u4ARCR = 0;
    UINT_32 i;

    ASSERT(prAdapter);
    ASSERT(ucWlanIdx < WLAN_TABLE_SIZE);
    ASSERT(ucRate1Index < RATE_NUM);

    prARCtrl = &prAdapter->rARCtrl;

    for (i = 0; i < RATE_NUM; i++) {
        if (u2RateSet & BIT(i)) {
            u2ARBits |= BIT(aucRateIndex2ARIndex[u4PreambleOptionIndex][i]);
        }
    }

    prARCtrl->au2ARBits[ucWlanIdx] = u2ARBits;
    prARCtrl->aucARRate1Index[ucWlanIdx] = aucRateIndex2ARIndex[u4PreambleOptionIndex][ucRate1Index];

    u4ARCR = ARCR_WRITE |
             ARCR_RESET |
             (UINT_32)((UINT_32)(ucWlanIdx /* & 0xf */) << ARCR_ENTRY_INDEX_OFFSET) |
             (UINT_32)((UINT_32)(prARCtrl->aucARRate1Index[ucWlanIdx]) << ARCR_RATE1_INDEX_OFFSET) |
             (UINT_32)u2ARBits;

    /* NOTE(Kevin): For Windows CE 5.0 release build, if we add the "& 0xf"
     * operation in above equation, we will make CE compiler confused and generate
     * an assembly instruction = 'mvn r3, #0x30' which is 0xCF but we need 0xC0
     * for 0xC0000000.
     * The unexpected 0xF will be OR into u4ARCR and then write to wrong AutoRate Entry.
     */

    HAL_MCR_WR(prAdapter, MCR_ARCR, u4ARCR);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Try to get the current rate 1 from auto rate register
*
* \param prAdapter      a pointer to adapter private data structure.
* \param ucWlanIdx      the wlan table entry index
* \param pucRate1Index  the current rate 1 index
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halARGetRate (
    IN P_ADAPTER_T     prAdapter,
    IN UINT_8          ucWlanIdx,
    OUT PUINT_8        pucRate1Index
    )
{
    UINT_32 u4ARCR = 0;
    UINT_8 ucARRate1Index;

    ASSERT(prAdapter);
    ASSERT(pucRate1Index);

    HAL_MCR_RD(prAdapter, MCR_ARCR, &u4ARCR);

    ucARRate1Index = (UINT_8)((u4ARCR &= ARCR_CURR_RATE1_INDEX_MASK) >>
                              ARCR_CURR_RATE1_INDEX_OFFSET);

    /* NOTE(Kevin 2008/04/16): Because we can't assign the WLAN Index Field in MP.
     * Thus we shouldn't do ASSERT here for checking the ucARRate1Index & au2ARBits[].
     */
    //ASSERT(BIT(ucARRate1Index) & prAdapter->rARCtrl.au2ARBits[ucWlanIdx]);

    if (ucARRate1Index <= ARCR_54M_IDX) {
        *pucRate1Index = aucARIndex2RateIndex[ucARRate1Index];
    }
    else {
        ERRORLOG(("abnormal rate1 index:%d in ARCR\n", ucARRate1Index));
        ASSERT(FALSE);
    }

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Reset the autorate for a specific entry
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \param ucIdx          the wlan table entry for reset
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halARReset (
    IN P_ADAPTER_T      prAdapter,
    IN UINT_8           ucWlanIdx
    )
{
    P_AR_CTRL_T         prARCtrl;
    UINT_32             u4ARCR = 0;

    ASSERT(prAdapter);

    prARCtrl = &prAdapter->rARCtrl;

    u4ARCR = ARCR_WRITE |
             ARCR_RESET |
             ((ucWlanIdx & 0xf) << 24) |
             ((prARCtrl->aucARRate1Index[ucWlanIdx] & 0xf) << 16) |
             prARCtrl->au2ARBits[ucWlanIdx];

    HAL_MCR_WR(prAdapter, MCR_ARCR, u4ARCR);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Enable the CTS protection mode
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \param ucType         0: as 802.11 spec, 1:the CTS-to-self will protect one data frame
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halEnableCTSProtectionMode (
    IN P_ADAPTER_T        prAdapter,
    IN UINT_8             ucType
    )
{
    UINT_32 u4RCCR = 0;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_RCCR, &u4RCCR);

    u4RCCR |= RCCR_CTS_PROTECTION;
    if (ucType == CTS_PROTECTION_TYPE_802_11) {
        u4RCCR &= ~RCCR_CTS_MODE_PROPRIETARY;
    }
    else {
        u4RCCR |= RCCR_CTS_MODE_PROPRIETARY;
    }

    HAL_MCR_WR(prAdapter, MCR_RCCR, u4RCCR);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Disable the CTS protection mode
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halDisableCTSProtectionMode (
    IN P_ADAPTER_T         prAdapter
    )
{
    UINT_32 u4RCCR = 0;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_RCCR, &u4RCCR);
    u4RCCR &= ~RCCR_CTS_PROTECTION;
    HAL_MCR_WR(prAdapter, MCR_RCCR, u4RCCR);

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Set the CTS Rate
*
* \param prAdapter      a pointer to adapter private data structure.
* \param ucRateIndex    the new CTS/RTS rate
* \param fgIsShortPreamble  indicate to use long or short preamble
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halSetCTSRTSRate (
    IN P_ADAPTER_T       prAdapter,
    IN UINT_8            ucRateIndex,
    IN BOOLEAN           fgIsShortPreamble
    )
{
    UINT_32 u4PreambleOptionIndex =
        (fgIsShortPreamble ? PREAMBLE_OPTION_SHORT : PREAMBLE_DEFAULT_LONG_NONE);
    UINT_32 u4RCCR = 0;

    ASSERT(prAdapter);
    ASSERT(ucRateIndex < RATE_NUM);

    HAL_MCR_RD(prAdapter, MCR_RCCR, &u4RCCR);

    u4RCCR &= ~RCCR_RC_BR_MASK;
    u4RCCR |= ((UINT_32) aucRateIndex2RateCode[u4PreambleOptionIndex][ucRateIndex] << RCCR_RC_BR_OFFSET);

    HAL_MCR_WR(prAdapter, MCR_RCCR, u4RCCR);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Set the Basic Rate
*
* \param prAdapter      a pointer to adapter private data structure.
* \param ucRateIndex    the new basic rate
* \param fgIsShortPreamble  indicate to use long or short preamble
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halSetBasicRate (
    IN P_ADAPTER_T      prAdapter,
    IN UINT_8           ucRateIndex,
    IN BOOLEAN          fgIsShortPreamble
    )
{
    UINT_32 u4PreambleOptionIndex =
        (fgIsShortPreamble ? PREAMBLE_OPTION_SHORT : PREAMBLE_DEFAULT_LONG_NONE);
    UINT_32 u4RCCR = 0;

    ASSERT(prAdapter);

    ASSERT(ucRateIndex < RATE_NUM);

    HAL_MCR_RD(prAdapter, MCR_RCCR, &u4RCCR);

    u4RCCR &= ~RCCR_BR_MASK;
    u4RCCR |= ((UINT_32) aucRateIndex2RateCode[u4PreambleOptionIndex][ucRateIndex] << 16);

    HAL_MCR_WR(prAdapter, MCR_RCCR, u4RCCR);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Set RTS Threshold
*
* \param prAdapter      a pointer to adapter private data structure.
* \param u2RTSThreshold New RTS threshold
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halSetRTSThreshold (
    IN P_ADAPTER_T     prAdapter,
    IN UINT_16         u2RTSThreshold
    )
{
    UINT_32 u4RCCR = 0;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_RCCR, &u4RCCR);

    u4RCCR &= ~RCCR_RTS_THRESHOLD_MASK;
    u4RCCR |= (u2RTSThreshold & RCCR_RTS_THRESHOLD_MASK);

    HAL_MCR_WR(prAdapter, MCR_RCCR, u4RCCR);

    return;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Set the Basic Rate
*
* \param prAdapter      a pointer to adapter private data structure.
* \param aucAckCtsRateIndex[]         Ctrl Response Frame Rate Table
* \param fgCtrlRespPresmbleMode  indicate that the preamble mode for CCK packets
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halSetAckCtsRate(
    IN P_ADAPTER_T      prAdapter,
    IN UINT_8           aucAckCtsRateIndex[],
    IN BOOLEAN          fgIsShortPreamble
    )
{
    UINT_32 u4CRFR = 0;

    ASSERT(prAdapter);

    ASSERT(aucAckCtsRateIndex);

    u4CRFR = 0x80000000;

    u4CRFR |= ((UINT_32) aucRateIndex2ACKRateCode[ aucAckCtsRateIndex[RATE_1M_INDEX  ] ] & BITS(0,4));
    u4CRFR |= ((UINT_32)(aucRateIndex2ACKRateCode[ aucAckCtsRateIndex[RATE_2M_INDEX  ] ] & BITS(0,4)) << 5);
    u4CRFR |= ((UINT_32)(aucRateIndex2ACKRateCode[ aucAckCtsRateIndex[RATE_5_5M_INDEX] ] & BITS(0,4)) << 10);
    u4CRFR |= ((UINT_32)(aucRateIndex2ACKRateCode[ aucAckCtsRateIndex[RATE_11M_INDEX ] ] & BITS(0,4)) << 15);
    u4CRFR |= ((UINT_32)(aucRateIndex2ACKRateCode[ aucAckCtsRateIndex[RATE_6M_INDEX  ] ] & BITS(0,4)) << 20);
    u4CRFR |= ((UINT_32)(aucRateIndex2ACKRateCode[ aucAckCtsRateIndex[RATE_9M_INDEX  ] ] & BITS(0,4)) << 25);

    HAL_MCR_WR(prAdapter, MCR_CRFR0, u4CRFR);

    u4CRFR = 0;
    u4CRFR |= ((UINT_32) aucRateIndex2ACKRateCode[ aucAckCtsRateIndex[RATE_12M_INDEX ] ] & BITS(0,4));
    u4CRFR |= ((UINT_32)(aucRateIndex2ACKRateCode[ aucAckCtsRateIndex[RATE_18M_INDEX ] ] & BITS(0,4)) << 5);
    u4CRFR |= ((UINT_32)(aucRateIndex2ACKRateCode[ aucAckCtsRateIndex[RATE_24M_INDEX ] ] & BITS(0,4)) << 10);
    u4CRFR |= ((UINT_32)(aucRateIndex2ACKRateCode[ aucAckCtsRateIndex[RATE_36M_INDEX ] ] & BITS(0,4)) << 15);
    u4CRFR |= ((UINT_32)(aucRateIndex2ACKRateCode[ aucAckCtsRateIndex[RATE_48M_INDEX ] ] & BITS(0,4)) << 20);
    u4CRFR |= ((UINT_32)(aucRateIndex2ACKRateCode[ aucAckCtsRateIndex[RATE_54M_INDEX ] ] & BITS(0,4)) << 25);

    HAL_MCR_WR(prAdapter, MCR_CRFR1, u4CRFR);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Set BSSID to MT5921
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \param aucBSSID       New BSSID
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halSetBSSID (
    IN P_ADAPTER_T     prAdapter,
    IN PUINT_8         aucBSSID
    )
{
    UINT_32 u4CBR0, u4CBR1;

    DEBUGFUNC("halSetBSSID");

    ASSERT(prAdapter);

    /* Write the new BSSID to the Current BSSID registers. */
    if (aucBSSID == NULL) {
        u4CBR0 = 0;
        u4CBR1 = 0;
    } else {
        u4CBR0 = ((UINT_32) aucBSSID[0]) |
            ((UINT_32) aucBSSID[1] << 8) |
            ((UINT_32) aucBSSID[2] << 16) |
            ((UINT_32) aucBSSID[3] << 24);
        u4CBR1 = ((UINT_32) aucBSSID[4]) |
            ((UINT_32) aucBSSID[5] << 8);
    }

    HAL_MCR_WR(prAdapter, MCR_CBR0, u4CBR0);
    HAL_MCR_WR(prAdapter, MCR_CBR1, u4CBR1);

#if DBG
    HAL_MCR_RD(prAdapter, MCR_CBR0, &u4CBR0);
    HAL_MCR_RD(prAdapter, MCR_CBR1, &u4CBR1);

    DBGLOG(HAL, INFO, ("CBR0 = %#lx, CBR1 = %#lx\n", u4CBR0, u4CBR1));
#endif

}


/*----------------------------------------------------------------------------*/
/*!
* \brief Set Operation Mode to MT5921
*
* \param prAdapter     a pointer to adapter private data structure.
* \param eOPMode       Operation Mode, OP_MODE_IBSS: IBSS, OP_MODE_INFRASTRUCTURE: Infrastructure
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halSetOPMode (
    IN P_ADAPTER_T      prAdapter,
    IN ENUM_OP_MODE_T   eOPMode
    )
{
    UINT_32 u4SCR = 0;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_SCR, &u4SCR);
    u4SCR &= ~SCR_OP_MODE_MASK;
    if (eOPMode == OP_MODE_IBSS) {
        u4SCR |= SCR_OP_MODE_ADHOC;
    }
    HAL_MCR_WR(prAdapter, MCR_SCR, u4SCR);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Set Slot Time to MT5921
*
* \param prAdapter      a pointer to adapter private data structure.
* \param u4SlotTime     Slot Time
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halSetSlotTime (
    IN P_ADAPTER_T      prAdapter,
    IN UINT_32          u4aSlotTime
    )
{
    UINT_32 u4BPDR = 0;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_BPDR, &u4BPDR);

    u4BPDR &= ~BPDR_SLOTTIME_MASK;
    u4BPDR |= ((u4aSlotTime << BPDR_SLOTTIME_OFFSET) & BPDR_SLOTTIME_MASK);

    HAL_MCR_WR(prAdapter, MCR_BPDR, u4BPDR);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Set the AC AIFS, CWmin, CWmax and TXOP value
*
* \param prAdapter      a pointer to adapter private data structure.
* \param arTxAcParamAifsCw     The structure of AC parameters
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halSetACParameters (
    IN P_ADAPTER_T           prAdapter,
    IN TX_AC_PARAM_AIFS_CW_T arTxAcParamAifsCw[]
    )
{
    UINT_32 u4RegValue;

    ASSERT(prAdapter);

    ASSERT(arTxAcParamAifsCw);

    //4 <1> AC0~AC3 : AIFS
    /* Update AIFS0~AIFS3 */
    HAL_MCR_RD(prAdapter, MCR_AIFSR, &u4RegValue);
    u4RegValue &= ~AIFSR_AIFS0_MASK;
    u4RegValue |= ((UINT_32)(arTxAcParamAifsCw[AC0].u2Aifsn & AIFSR_AIFS_MASK) << AIFSR_AIFS0_OFFSET);
    u4RegValue &= ~AIFSR_AIFS1_MASK;
    u4RegValue |= ((UINT_32)(arTxAcParamAifsCw[AC1].u2Aifsn & AIFSR_AIFS_MASK) << AIFSR_AIFS1_OFFSET);
    u4RegValue &= ~AIFSR_AIFS2_MASK;
    u4RegValue |= ((UINT_32)(arTxAcParamAifsCw[AC2].u2Aifsn & AIFSR_AIFS_MASK) << AIFSR_AIFS2_OFFSET);
    u4RegValue &= ~AIFSR_AIFS3_MASK;
    u4RegValue |= ((UINT_32)(arTxAcParamAifsCw[AC3].u2Aifsn & AIFSR_AIFS_MASK) << AIFSR_AIFS3_OFFSET);

    HAL_MCR_WR(prAdapter, MCR_AIFSR, u4RegValue);

    //4 <2> AC0~AC3 : CWmax
    /* Update ACCWXR0 */
    u4RegValue = ((UINT_32)arTxAcParamAifsCw[AC0].u2CWmax << ACCWXR0_AC0_CWMAX_OFFSET);
    u4RegValue |= ((UINT_32)arTxAcParamAifsCw[AC1].u2CWmax << ACCWXR0_AC1_CWMAX_OFFSET);

    HAL_MCR_WR(prAdapter, MCR_ACCWXR0, u4RegValue);

    /* Update ACCWXR1 */
    u4RegValue = ((UINT_32)arTxAcParamAifsCw[AC2].u2CWmax << ACCWXR1_AC2_CWMAX_OFFSET);
    u4RegValue |= ((UINT_32)arTxAcParamAifsCw[AC3].u2CWmax << ACCWXR1_AC3_CWMAX_OFFSET);

    HAL_MCR_WR(prAdapter, MCR_ACCWXR1, u4RegValue);

    //4 <3> AC0~AC3 : CWmin
    /* Update ACCWIR */
    u4RegValue = ((UINT_32)(arTxAcParamAifsCw[AC0].u2CWmin & ACCWIR_AC_CWMIN_MASK) << ACCWIR_AC0_CWMIN_OFFSET);
    u4RegValue |= ((UINT_32)(arTxAcParamAifsCw[AC1].u2CWmin & ACCWIR_AC_CWMIN_MASK) << ACCWIR_AC1_CWMIN_OFFSET);
    u4RegValue |= ((UINT_32)(arTxAcParamAifsCw[AC2].u2CWmin & ACCWIR_AC_CWMIN_MASK) << ACCWIR_AC2_CWMIN_OFFSET);
    u4RegValue |= ((UINT_32)(arTxAcParamAifsCw[AC3].u2CWmin & ACCWIR_AC_CWMIN_MASK) << ACCWIR_AC3_CWMIN_OFFSET);

    HAL_MCR_WR(prAdapter, MCR_ACCWIR, u4RegValue);

    //4 <4> AC0~AC3 : TXOP Limit
    /* Update ACTXOPLR0 */
    u4RegValue = ((UINT_32)arTxAcParamAifsCw[AC0].u2TxopLimit << ACTXOPLR0_AC0_LIMIT_OFFSET);
    u4RegValue |= ((UINT_32)arTxAcParamAifsCw[AC1].u2TxopLimit << ACTXOPLR0_AC1_LIMIT_OFFSET);

    HAL_MCR_WR(prAdapter, MCR_ACTXOPLR0, u4RegValue);

    /* Update ACTXOPLR1 */
    u4RegValue = ((UINT_32)arTxAcParamAifsCw[AC2].u2TxopLimit << ACTXOPLR1_AC2_LIMIT_OFFSET);
    u4RegValue |= ((UINT_32)arTxAcParamAifsCw[AC3].u2TxopLimit << ACTXOPLR1_AC3_LIMIT_OFFSET);

    HAL_MCR_WR(prAdapter, MCR_ACTXOPLR1, u4RegValue);

    //4 <4> AC4 : AIFS, CWmax and CWmin
    u4RegValue = ((UINT_32)arTxAcParamAifsCw[AC4].u2CWmax << AC4CWR_AC4_CWMAX_OFFSET);
    u4RegValue |= ((UINT_32)(arTxAcParamAifsCw[AC4].u2CWmin & AC4CWR_AC4_CWMIN_MASK) << AC4CWR_AC4_CWMIN_OFFSET);
    u4RegValue |= ((UINT_32)(arTxAcParamAifsCw[AC4].u2Aifsn & AC4CWR_AIFS4_MASK) << AC4CWR_AIFS4_OFFSET);

    HAL_MCR_WR(prAdapter, MCR_AC4CWR, u4RegValue);

    return;
}   /* pauSetACParameters */


/*----------------------------------------------------------------------------*/
/*!
* \brief Set the Rx packet filter setting,
*
* \param prAdapter      a pointer to adapter private data structure.
* \param u4RxFilter     The Rx filter parameter
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halSetRxFilters (
    IN P_ADAPTER_T      prAdapter,
    IN UINT_32          u4RxFilter
    )
{
    ASSERT(prAdapter);

    HAL_MCR_WR(prAdapter, MCR_RFCR, u4RxFilter);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Set the Rx packet filter setting,
*
* \param prAdapter        a pointer to adapter private data structure.
* \param pucBeaconContent The beacon content
* \param u4BcnLen         The beacon length
* \param ucRateIndex      Which rate to send the beacon
* \param fgIsShortPreamble indicate use short or long premble to send
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
halSetBeaconContent (
    IN P_ADAPTER_T  prAdapter,
    IN PUINT_8      pucBeaconContent,
    IN UINT_32      u4BcnLen,
    IN UINT_8       ucRateIndex,
    IN BOOLEAN      fgIsShortPreamble
    )
{
    UINT_32 u4PreambleOptionIndex =
        (fgIsShortPreamble ? PREAMBLE_OPTION_SHORT : PREAMBLE_DEFAULT_LONG_NONE);
    UINT_32 u4BeaconTfb;
    UINT_8 ucOffset = 0;
    UINT_16 j = 0;
    BOOLEAN fgResult = TRUE;

    ASSERT(prAdapter);
    ASSERT(pucBeaconContent);
    ASSERT(ucRateIndex < RATE_NUM);

    u4BeaconTfb = 0; // Antenna 0
    u4BeaconTfb |= ((UINT_32) aucRateIndex2RateCode[u4PreambleOptionIndex][ucRateIndex] << BCN_TFCB_RATE_INDEX_OFFSET);
    u4BeaconTfb |= (u4BcnLen & BCN_TFCB_PAYLOAD_LEN_MASK);

    if (u4BcnLen & ~BCN_TFCB_PAYLOAD_LEN_MASK) {
        ASSERT(0);
    }

    if (u4BcnLen & 3) {
        for (j = 0; j < 4 - (UINT_16)(u4BcnLen & 3); j++) {
            pucBeaconContent[u4BcnLen + j] = 0;
            ucOffset++;
        }
    }

    //Write Beacon Tfb
    HAL_MCR_WR(prAdapter, MCR_HBDR, (UINT_32)u4BeaconTfb);

    //Write Beacon content
    HAL_PORT_WR(prAdapter,
                MCR_HBDR,
                (UINT_16)(u4BcnLen+ucOffset),
                (PUINT_8)pucBeaconContent,
                (UINT_16)(u4BcnLen+ucOffset));

    if (!fgResult) {
        return FALSE;
    }

    return TRUE;
}

#if CFG_TCP_IP_CHKSUM_OFFLOAD
/*----------------------------------------------------------------------------*/
/*!
* \brief The Check Sum offload enable function
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[in] u4CSUMFlags The bit mask to enable the TCP/UDP/IP offload
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halSetCSUMOffload (
    IN P_ADAPTER_T      prAdapter,
    IN UINT_32          u4CSUMFlags
    )
{
    UINT_32 u4HCR = 0;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_HCR, &u4HCR);
    u4HCR &= ~HCR_CSUM_OFFLOAD_MASK;
    if( u4CSUMFlags & CSUM_OFFLOAD_EN_TX_MASK) {
        u4HCR |= HCR_TCPIP_TX_OFFLOAD_EN;
    }
    if (u4CSUMFlags & CSUM_OFFLOAD_EN_RX_IPv6) {
        u4HCR |= HCR_IPV6_RX_OFFLOAD_EN;
    }
    if (u4CSUMFlags & CSUM_OFFLOAD_EN_RX_IPv4) {
        u4HCR |= HCR_IP_RX_OFFLOAD_EN;
    }
    if (u4CSUMFlags & CSUM_OFFLOAD_EN_RX_UDP) {
        u4HCR |= HCR_UDP_RX_OFFLOAD_EN;
    }
    if (u4CSUMFlags & CSUM_OFFLOAD_EN_RX_TCP) {
        u4HCR |= HCR_TCP_RX_OFFLOAD_EN;
    }
    HAL_MCR_WR(prAdapter, MCR_HCR, u4HCR);


}
#endif


/*----------------------------------------------------------------------------*/
/*!
* \brief The RR enable function
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halRREnable (
    IN P_ADAPTER_T  prAdapter,
    IN RCPI         rRCPIUpperThreshold,
    IN RCPI         rRCPILowerThreshold
    )
{
    RCPI rRCPILowBound = RCPI_LOW_BOUND;
    UINT_32 u4RCPIUpperThreshold, u4RCPILowerThreshold;
    UINT_32 u4McrRR = 0;

    ASSERT(prAdapter);
    ASSERT(rRCPILowerThreshold <= rRCPIUpperThreshold);

    if (rRCPIUpperThreshold >= RCPI_HIGH_BOUND) {
        /* Set to maximum value to disable low threshold interrupt */
        u4RCPIUpperThreshold = RR_RCPI_HIGH_MAXIMUM;
    }
    else {
        u4RCPIUpperThreshold = (UINT_32)rRCPIUpperThreshold;
    }

    if (rRCPILowerThreshold <= rRCPILowBound) {
        /* Set to minimum value to disable low threshold interrupt */
        u4RCPILowerThreshold = RR_RCPI_LOW_MINIMUM;
    }
    else {
        u4RCPILowerThreshold = (UINT_32)rRCPILowerThreshold;
    }

    u4McrRR = RR_RCPI_PARM_1_OF_8;

    u4McrRR |= (RR_ENABLE_MA |
                RR_SET_HIGH_RCPI_THRESHOLD(u4RCPIUpperThreshold) |
                RR_SET_LOW_RCPI_THRESHOLD(u4RCPILowerThreshold));

    HAL_MCR_WR(prAdapter, MCR_RR, u4McrRR);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief The RR disable function
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halRRDisable (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4McrRR;

    ASSERT(prAdapter);

    u4McrRR = (RR_SET_HIGH_RCPI_THRESHOLD(RR_RCPI_HIGH_MAXIMUM) |
               RR_SET_LOW_RCPI_THRESHOLD(RR_RCPI_LOW_MINIMUM));

    HAL_MCR_WR(prAdapter, MCR_RR, u4McrRR);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Read RCPI function
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halRRGetRCPI (
    IN P_ADAPTER_T  prAdapter,
    OUT P_RCPI      prRCPI
    )
{
    UINT_32 u4McrRR = 0;
    RCPI rRcpiLowBound = RCPI_LOW_BOUND;
    RCPI rRcpi;

    ASSERT(prAdapter);
    ASSERT(prRCPI);

    HAL_MCR_RD(prAdapter, MCR_RR, &u4McrRR);

    DBGLOG(ROAMING, INFO, ("Read MCR_RR = %08lx\n", u4McrRR));

    rRcpi = RR_GET_RCPI(u4McrRR);

    if (rRcpi > RCPI_HIGH_BOUND) {
        rRcpi = RCPI_MEASUREMENT_NOT_AVAILABLE;
    }
    else if (rRcpi < rRcpiLowBound) {
        rRcpi = RCPI_MEASUREMENT_NOT_AVAILABLE;
    }

    *prRCPI = rRcpi;

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Enable the ALCR function
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halALCREnable (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_32      u4AvePara,
    IN ALC_VAL      rALCMaxThreshold,
    IN ALC_VAL      rALCMinThreshold,
    IN ALC_VAL      rALCInitVal
    )
{
    UINT_32 u4McrALCR = 0;

    DEBUGFUNC("halALCREnable");

    ASSERT(prAdapter);

    //Disalbe ALCR function first.
    HAL_MCR_WR(prAdapter, MCR_ALCR0, u4McrALCR);
    u4McrALCR = ALCR_ALC_CALCULATION_EN |
              ALCR_SET_MOV_AVE_PARA(u4AvePara) |
              ALCR_SET_MIN_THRESHOLD(rALCMinThreshold) |
              ALCR_SET_MAX_THRESHOLD(rALCMaxThreshold) |
              ALCR_SET_ALC_INIT_VALUE(rALCInitVal);

    HAL_MCR_WR(prAdapter, MCR_ALCR0, u4McrALCR);

}


/*----------------------------------------------------------------------------*/
/*!
* \brief Disable the ALCR function
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halALCRDisable (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4McrALCR;

    ASSERT(prAdapter);

    DEBUGFUNC("halALCRDisable");
    HAL_MCR_RD(prAdapter, MCR_ALCR0, &u4McrALCR);
    u4McrALCR &= ~ALCR_ALC_CALCULATION_EN;
    HAL_MCR_WR(prAdapter, MCR_ALCR0, u4McrALCR);

}


/*----------------------------------------------------------------------------*/
/*!
* \brief The ALCR get raw function
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halALCRGetRawValue (
    IN P_ADAPTER_T  prAdapter,
    OUT P_ALC_VAL   prRawValue
    )
{
    UINT_32 u4McrALCR = 0;

    ASSERT(prAdapter);
    ASSERT(prRawValue);

    HAL_MCR_RD(prAdapter, MCR_ALCR0, &u4McrALCR);
    *prRawValue = ALCR_GET_ALC_RAW_VALUE(u4McrALCR);

}


/*----------------------------------------------------------------------------*/
/*!
* \brief The ALCR get calbration function
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halALCRGetCalValue (
    IN P_ADAPTER_T  prAdapter,
    OUT P_ALC_VAL   prCalValue
    )
{
    UINT_32 u4McrALCR = 0;

    ASSERT(prAdapter);
    ASSERT(prCalValue);

    HAL_MCR_RD(prAdapter, MCR_ALCR0, &u4McrALCR);
    *prCalValue = ALCR_GET_ALC_CAL_VALUE(u4McrALCR);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief The ALCR trigger function
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halALCRTriggerALC (
    IN P_ADAPTER_T  prAdapter
    )
{
    UINT_32 u4McrALCR = 0;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_ALCR0, &u4McrALCR);
    u4McrALCR = u4McrALCR | ( ALCR_ALC_CALCULATION_EN | ALCR_ALC_TRIGGER);
    HAL_MCR_WR(prAdapter, MCR_ALCR0, u4McrALCR);

    return;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Reset the chip to the default state
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halChipReset (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4RegV;

    DEBUGFUNC("halChipReset");

    ASSERT(prAdapter);

    DBGLOG(INIT, TRACE, ("@@ Chip reset @@"));

    HAL_MCR_RD(prAdapter, MCR_CIR, &u4RegV);
    if (u4RegV & CIR_PLL_READY) {
        /* PLL is ready */
        DBGLOG(INIT, TRACE, ("\n\nPLL is ready\n\n"));

        HAL_MCR_WR(prAdapter, MCR_HLPCR, HLPCR_CHIP_RESET);

    } else {
        /* PLL is "not" ready */
        DBGLOG(INIT, TRACE, ("\n\nPLL is NOT ready\n\n"));

        HAL_MCR_WR(prAdapter, MCR_HLPCR, HLPCR_CHIP_RESET);
        nicpmPowerOn(prAdapter);
    }

}


/*----------------------------------------------------------------------------*/
/*!
* \brief
*
* \param[in] prAdapter Pointer to the Adapter structure
*
* \retval WLAN_STATUS_SUCCESS
*
* \note
*/
/*----------------------------------------------------------------------------*/
VOID
halLogicReset (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4RegV;

    DEBUGFUNC("halLogicReset");

    ASSERT(prAdapter);

    INITLOG(("@@ Logic reset @@"));

    HAL_MCR_RD(prAdapter, MCR_CIR, &u4RegV);
    if (u4RegV & CIR_PLL_READY) {
        /* PLL is ready */
        INITLOG(("PLL is ready"));

        // Clear LP own for preventing reset on WLAN_on, initial state
        // logic reset (HIFMAC: bit 29, BB: B25)
        HAL_MCR_WR(prAdapter, MCR_HLPCR, HLPCR_BB_LOGRST | HLPCR_HIFMAC_LOGRST | HLPCR_LP_OWN_CLR);
    } else {
        /* PLL is "not" ready */
        INITLOG(("PLL is NOT ready"));

        nicpmPowerOn(prAdapter);
    }

}


/*----------------------------------------------------------------------------*/
/*!
* \brief Set the given MAC address to the MCR.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] ucIdx          0: Own mac addr, 1-32: multicast addr or multi-mac addr.
* \param[in] pucMACAddr     Pointer to the given MAC Address.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halSetMACAddr (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_8       ucIdx,
    IN PUINT_8      pucMACAddr
    )
{
    UINT_32 u4MUAR0, u4MUAR1;

    ASSERT(prAdapter);

    if (ucIdx > MAX_NUM_GROUP_ADDR) { /* NOTE: Accept 0: UCAST, 1~32: MCAST */
        return;
    }

    if (pucMACAddr == NULL) {
        u4MUAR0 = 0;
        u4MUAR1 = 0;
    }
    else {
        /* modified by CM's proposal */
        u4MUAR0 = ((UINT_32)pucMACAddr[0])       |
                  ((UINT_32)pucMACAddr[1]) << 8  |
                  ((UINT_32)pucMACAddr[2]) << 16 |
                  ((UINT_32)pucMACAddr[3]) << 24;
        u4MUAR1 = ((UINT_32)pucMACAddr[4]) |
                  ((UINT_32)pucMACAddr[5]) << 8;
    }

    u4MUAR1 |= MUAR1_WRITE | MUAR1_ACCESS_START | (ucIdx << 24);

    HAL_MCR_WR(prAdapter, MCR_MUAR0, u4MUAR0);
    HAL_MCR_WR(prAdapter, MCR_MUAR1, u4MUAR1);

    return;
} /* end of halSetMACAddr() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Clear all Multicast MAC addresses in MCR.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halClearMulticastAddrList (
    IN P_ADAPTER_T     prAdapter
    )
{
    UINT_32 u4MUAR0, u4MUAR1;
    UINT_8 ucIdx = 1;

    ASSERT(prAdapter);

    u4MUAR0 = 0;
    for (ucIdx = 1; ucIdx <= MAX_NUM_GROUP_ADDR; ucIdx++) {
        u4MUAR1 = MUAR1_WRITE | MUAR1_ACCESS_START | (ucIdx << MUAR1_ADDR_INDEX_OFFSET);
        HAL_MCR_WR(prAdapter, MCR_MUAR0, u4MUAR0);
        HAL_MCR_WR(prAdapter, MCR_MUAR1, u4MUAR1);

        /* NOTE(Kevin): Do we need to read MUAR1 for assuring that previous
         * accessing was completed ?
         */
    }

    return;
} /* end of halClearMulticastAddrList() */


/*----------------------------------------------------------------------------*/
/*!
* \brief To set the AC's admin time.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] ucTxQueueId    The AC mask to disable
* \param[in] u2MediumTime   The admin time
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halSetAdminCtrlMediumTime (
    IN P_ADAPTER_T     prAdapter,
    IN UINT_8          ucTxQueueId,
    IN UINT_16         u2MediumTime
    )
{
    UINT_32 u4RegV;

    ASSERT(prAdapter);

    switch (ucTxQueueId) {
    case TXQ_AC3:
        HAL_MCR_RD(prAdapter, MCR_MTR0, &u4RegV);
        u4RegV &= ~MTR0_AC3_ADMIT_TIME_MASK;
        u4RegV |= MTR_ACQ_ADMIT_TIME(ucTxQueueId, u2MediumTime);
        HAL_MCR_WR(prAdapter, MCR_MTR0, u4RegV);
        break;
    case TXQ_AC2:
        HAL_MCR_RD(prAdapter, MCR_MTR0, &u4RegV);
        u4RegV &= ~MTR0_AC2_ADMIT_TIME_MASK;
        u4RegV |= MTR_ACQ_ADMIT_TIME(ucTxQueueId, u2MediumTime);
        HAL_MCR_WR(prAdapter, MCR_MTR0, u4RegV);
        break;
    case TXQ_AC1:
        HAL_MCR_RD(prAdapter, MCR_MTR1, &u4RegV);
        u4RegV &= ~MTR1_AC1_ADMIT_TIME_MASK;
        u4RegV |= MTR_ACQ_ADMIT_TIME(ucTxQueueId, u2MediumTime);
        HAL_MCR_WR(prAdapter, MCR_MTR1, u4RegV);
        break;
    case TXQ_AC0:
        HAL_MCR_RD(prAdapter, MCR_MTR1, &u4RegV);
        u4RegV &= ~MTR1_AC0_ADMIT_TIME_MASK;
        u4RegV |= MTR_ACQ_ADMIT_TIME(ucTxQueueId, u2MediumTime);
        HAL_MCR_WR(prAdapter, MCR_MTR1, u4RegV);
        break;
    default:
        ASSERT(0);
        break;
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief To enable AC's admin control.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] ucTxQueueId    The AC mask to enable
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halEnableAdminCtrl (
    IN P_ADAPTER_T      prAdapter,
    IN UINT_8           ucTxQueueId
    )
{
#define DEFAULT_AVERAGING_PERIOD    1

    UINT_32 u4RegV;

    ASSERT(prAdapter);

    switch (ucTxQueueId) {
    case TXQ_AC3:
        HAL_MCR_RD(prAdapter, MCR_MTCR0, &u4RegV);
        u4RegV |= MTCR0_AC3_ADMIT_TIME_EN | (DEFAULT_AVERAGING_PERIOD << 24);
        HAL_MCR_WR(prAdapter, MCR_MTCR0, u4RegV);
        break;
    case TXQ_AC2:
        HAL_MCR_RD(prAdapter, MCR_MTCR0, &u4RegV);
        u4RegV |= MTCR0_AC2_ADMIT_TIME_EN | (DEFAULT_AVERAGING_PERIOD << 16);
        HAL_MCR_WR(prAdapter, MCR_MTCR0, u4RegV);
        break;
    case TXQ_AC1:
        HAL_MCR_RD(prAdapter, MCR_MTCR1, &u4RegV);
        u4RegV |= MTCR1_AC1_ADMIT_TIME_EN | (DEFAULT_AVERAGING_PERIOD << 24);
        HAL_MCR_WR(prAdapter, MCR_MTCR1, u4RegV);
        break;
    case TXQ_AC0:
        HAL_MCR_RD(prAdapter, MCR_MTCR1, &u4RegV);
        u4RegV |= MTCR1_AC0_ADMIT_TIME_EN | (DEFAULT_AVERAGING_PERIOD << 16);
        HAL_MCR_WR(prAdapter, MCR_MTCR1, u4RegV);
        break;
    default:
        ASSERT(0);
        break;
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief To disable AC's admin time.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] ucTxQueueId    The AC mask to disable
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halDisableAdminCtrl (
    IN P_ADAPTER_T      prAdapter,
    IN UINT_8           ucTxQueueId
    )
{
    UINT_32 u4RegV;

    ASSERT(prAdapter);

    switch (ucTxQueueId) {
    case TXQ_AC3:
        HAL_MCR_RD(prAdapter, MCR_MTCR0, &u4RegV);
        HAL_MCR_WR(prAdapter, MCR_MTCR0, u4RegV & ~MTCR0_AC3_ADMIT_TIME_EN);
        break;
    case TXQ_AC2:
        HAL_MCR_RD(prAdapter, MCR_MTCR0, &u4RegV);
        HAL_MCR_WR(prAdapter, MCR_MTCR0, u4RegV & ~MTCR0_AC2_ADMIT_TIME_EN);
        break;
    case TXQ_AC1:
        HAL_MCR_RD(prAdapter, MCR_MTCR1, &u4RegV);
        HAL_MCR_WR(prAdapter, MCR_MTCR1, u4RegV & ~MTCR1_AC1_ADMIT_TIME_EN);
        break;
    case TXQ_AC0:
        HAL_MCR_RD(prAdapter, MCR_MTCR1, &u4RegV);
        HAL_MCR_WR(prAdapter, MCR_MTCR1, u4RegV & ~MTCR1_AC0_ADMIT_TIME_EN);
        break;
    default:
        ASSERT(0);
        break;
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief write 16-bit data to EEPRom
*
* \param prAdapter      a pointer to adapter private data structure.
* \param ucEepromWordOffset    Word offset of EEPROM
* \param u2EepromData    Value to be written to EEPROM
*
* \return TRUE - EEPROM is write ok
*            FALSe - Otherwise
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
halEepromWrite16 (
    IN P_ADAPTER_T      prAdapter,
    IN UINT_8           ucEepromWordOffset,
    IN UINT_16          u2EepromData
    )
{
    BOOLEAN     fgReady;
    UINT_32     u4wdValue;
    UINT_32     u4regValue = 0;

    DEBUGFUNC("halEepromWrite16");

    ASSERT(prAdapter);

    DBGLOG(HAL, INFO, ("Offset 0x%02X, Value:0x%04X.\n",\
        ucEepromWordOffset,  u2EepromData));
    u4wdValue = ( ((UINT_32) ucEepromWordOffset) << EADR_EE_ADDRESS_OFFSET) \
                            | u2EepromData;
    /* Issue an EEPROM write operation. */
    HAL_MCR_WR(prAdapter, MCR_EADR , (u4wdValue | EADR_EE_WRITE));

    /* Wait for the completion of the EEPROM write operation. */
    HAL_MCR_RD_AND_WAIT(prAdapter,
                          MCR_EADR,
                          &u4regValue,
                          (u4regValue & EADR_EE_RDY) == EADR_EE_RDY,
                          EEPROM_TTL_ACCESS_RDY_MSEC,
                          EEPROM_MAX_LOOP_ACCESS_RDY,
                          fgReady
                          );

    return fgReady;

}   /* halEepromWrite16 */


/*----------------------------------------------------------------------------*/
/*!
* \brief read 16-bit data from EEPRom
*
* \param prAdapter      a pointer to adapter private data structure.
* \param ucEepromWordOffset    Word offset of EEPROM
* \param pu2EepromData    a pointer to Value from EEPROM
*
* \return TRUE - EEPROM is read ok
*            FALSe - Otherwise
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
halEepromRead16 (
    IN      P_ADAPTER_T     prAdapter,
    IN      UINT_8          ucEepromWordOffset,
    OUT     PUINT_16        pu2EepromData
    )
{

    BOOLEAN     fgReady;
    UINT_32     u4wdValue;
    UINT_32     u4regValue;

    DEBUGFUNC("halEepromRead16");

    ASSERT(prAdapter);
    ASSERT(pu2EepromData);

    u4wdValue = ((UINT_32) ucEepromWordOffset) << EADR_EE_ADDRESS_OFFSET;

    /* Issue an EEPROM read operation. */
    HAL_MCR_WR(prAdapter, MCR_EADR, (EADR_EE_READ | u4wdValue));

    /* Wait for the completion of the EEPROM read operation. */
    HAL_MCR_RD_AND_WAIT(prAdapter,
                          MCR_EADR,
                          &u4regValue,
                          (u4regValue & EADR_EE_RDY) == EADR_EE_RDY,
                          EEPROM_TTL_ACCESS_RDY_MSEC,
                          EEPROM_MAX_LOOP_ACCESS_RDY,
                          fgReady
                          );
    if (fgReady) {
        *pu2EepromData =(UINT_16) (u4regValue & EADR_EE_DATA_MASK);
        DBGLOG(HAL, INFO, ("Offset 0x%02X, Value:0x%04X.\n",\
            ucEepromWordOffset,  *pu2EepromData));

    }
    else {
        DBGLOG(HAL, ERROR, ("Read Error : Offset 0x%02X.\n", ucEepromWordOffset));

    }

    return fgReady;
}   /* ReadEEProm16 */


/*----------------------------------------------------------------------------*/
/*!
* \brief get EEPRom size
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \return 0 - EEPROM is not present
*            Non-Zero value - Eeprom Size
*/
/*----------------------------------------------------------------------------*/
UINT_16
halEepromGetSize (
    IN      P_ADAPTER_T     prAdapter
    )
{
    UINT_16     u2EepromSize = 0;
    UINT_32     u4Type;
    UINT_32     u4Status;

    DEBUGFUNC("halEepromGetSize");

    ASSERT(prAdapter);

    /* Check if the EEPROM is present and checksum correct. */
    HAL_MCR_RD(prAdapter, MCR_ESCR, &u4Type);
    HAL_MCR_RD(prAdapter, MCR_EADR, &u4Status);
    if ((u4Type & ESCR_EE_TYPE_MASK) == ESCR_EE_TYPE_NONE
            || (u4Status & (EADR_EE_CSERR | EADR_EE_RDY))
                 == (EADR_EE_CSERR | EADR_EE_RDY)) {
        DBGLOG(HAL, WARN, ("EEPROM not present/checksum error (MCR_ECSR %#08lx, MCR_EADR %#08lx) -- \n",\
            u4Type,  u4Status));
        return 0;
    }

    switch(u4Type & ESCR_EE_TYPE_MASK) {
        case ESCR_EE_TYPE_NONE:
            u2EepromSize = 0;
            break;
        case ESCR_128BYTE:
            u2EepromSize = 128;
            break;
        //case ESCR_256BYTE:
        case ESCR_512BYTE:
            u2EepromSize = 512;
            break;
        case ESCR_1024BYTE:
            u2EepromSize = 1024;
            break;
        case ESCR_2048BYTE:
            u2EepromSize = 2048;
            break;
    };

    DBGLOG(HAL, INFO, ("EEPROM size %d.\n", u2EepromSize));
    return u2EepromSize;

} /* nicGetEEPROMSize */

/*----------------------------------------------------------------------------*/
/*!
* \brief Let reload EEPROM content
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
halEepromRecall (
    IN      P_ADAPTER_T     prAdapter
    )
{
    UINT_32     i;
    UINT_32     u4Status;

    DEBUGFUNC("halEepromRecall");

    ASSERT(prAdapter);

    HAL_MCR_WR(prAdapter, MCR_EADR, EADR_EE_RECALL);
    kalMdelay(1);

    for (i = 0; i < 100; i++) {
        HAL_MCR_RD(prAdapter, MCR_EADR, &u4Status);
        if (u4Status & EADR_EE_RDY) {
            break;
        }
        kalUdelay(50);
    }
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Set HW packet TX rate to use autorate or basic rate
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \return  - VOID
*/
/*----------------------------------------------------------------------------*/
VOID
halSetHwTxByBasicRate (
    IN  P_ADAPTER_T      prAdapter,
    IN BOOLEAN           fgUseBasicRate
    )
{
    UINT_32 u4Value;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_TXCR, &u4Value);
    u4Value &= ~TXCR_HW_TX_RATE_SEL_BASIC_RATE;
    if (fgUseBasicRate) {
        u4Value |= TXCR_HW_TX_RATE_SEL_BASIC_RATE;
    }
    HAL_MCR_WR(prAdapter, MCR_TXCR, u4Value);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Use HW to generate a random number
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \return  - The 2 bytes random number
*/
/*----------------------------------------------------------------------------*/
VOID
halGetRandomNumber (
    IN P_ADAPTER_T prAdapter,
    OUT PUINT_16 pu2Number
    )
{
    UINT_32 u4Value = 0;

    ASSERT(prAdapter);
    ASSERT(pu2Number);

    HAL_MCR_RD(prAdapter, MCR_DRNGR, &u4Value);

    *pu2Number = (UINT_16)u4Value;

    return;
}


#if CFG_SDIO_STATUS_ENHANCE
/*----------------------------------------------------------------------------*/
/*!
* \brief For SDIO enhance mode, set the max rx len and tx status
*
* \param prAdapter      a pointer to adapter private data structure.
*
* \return  - none
*/
/*----------------------------------------------------------------------------*/
VOID
halSDIOInit (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4Value;

    ASSERT(prAdapter);

    //4 <1> Check STATUS Buffer is DW alignment.
    ASSERT( IS_ALIGN_4( (UINT_32)&prAdapter->rSDIOCtrl.u4Hisr ) );

    //4 <2> Setup STATUS count.
    HAL_MCR_RD(prAdapter, MCR_SDIOCSR, &u4Value);
    u4Value &= ~(SDIOCSR_MAX_RECEIVE_PKT | SDIOCSR_MAX_TXSTATUS_PKT);
    u4Value |= ((SDIO_MAXIMUM_RX_STATUS << SDIOCSR_MAX_RECEIVE_PKT_OFFSET) |
                (SDIO_MAXIMUM_TX_STATUS << SDIOCSR_MAX_TXSTATUS_PKT_OFFSET));
    HAL_MCR_WR(prAdapter, MCR_SDIOCSR, u4Value);

    return;

} /* end of halSDIOInit() */


/*----------------------------------------------------------------------------*/
/*!
* \brief Read interrupt status from hardware
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[out] the interrupts
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
#if CFG_WORKAROUND_HEC_5269
VOID
halSDIOReadIntStatus (
    IN P_ADAPTER_T       prAdapter,
    OUT UINT_32          au4IntStatus[],
    OUT PBOOLEAN         pfgValidTxStatus
    )
#else
VOID
halSDIOReadIntStatus (
    IN P_ADAPTER_T prAdapter,
    OUT UINT_32 au4IntStatus[]
    )
#endif /* CFG_WORKAROUND_HEC_5269 */
{
    P_SDIO_CTRL_T prSDIOCtrl;
    UINT_32 u4RxLenCount = 0;
    UINT_32 u4TxStatusCount = 0;
    BOOLEAN fgResult = TRUE;
    INT_32 i;

    DEBUGFUNC("halSDIOReadIntStatus");

    ASSERT(prAdapter);
    ASSERT(au4IntStatus);
#if CFG_WORKAROUND_HEC_5269
    ASSERT(pfgValidTxStatus);
#endif /* CFG_WORKAROUND_HEC_5269 */

    prSDIOCtrl = &prAdapter->rSDIOCtrl;

    au4IntStatus[INT_HISR] = 0;
    au4IntStatus[INT_HSCISR] = 0;
    //kalMemZero(&prSDIOCtrl->u4Hisr, sizeof(ISAR_BIND_STATUS_T));

    HAL_PORT_RD(prAdapter,
                MCR_HISR,
                sizeof(ISAR_BIND_STATUS_T),
                (PUINT_8)&prSDIOCtrl->u4Hisr,
                sizeof(ISAR_BIND_STATUS_T));

    if (!fgResult) {
        ASSERT(0);
        return;
    }

    au4IntStatus[INT_HISR] = prSDIOCtrl->u4Hisr;

    for (i = (SDIO_MAXIMUM_RX_STATUS - 1); i >= 0; i--) {
        if (prSDIOCtrl->au2RxLengthDW[i]) {
            u4RxLenCount++;
        }
    }

    for (i = (SDIO_MAXIMUM_TX_STATUS - 1); i >= 0; i--) {
        if (prSDIOCtrl->arTxStatus[i].ucStatusIndicationPID) {
            u4TxStatusCount++;
        }
    }

#if DBG
    if (u4RxLenCount > (UINT_32)prSDIOCtrl->ucMaxNumOfRxLen) {
        prSDIOCtrl->ucMaxNumOfRxLen = (UINT_8)u4RxLenCount;

        DBGLOG(INTR, TRACE,
            ("SDIO STATUS ENHANCE: New Rx Len count record ==> %ld\n", u4RxLenCount));
    }

    if (u4TxStatusCount > (UINT_32)prSDIOCtrl->ucMaxNumOfTxStatus) {
        prSDIOCtrl->ucMaxNumOfTxStatus = (UINT_8)u4TxStatusCount;

        DBGLOG(INTR, TRACE,
            ("SDIO STATUS ENHANCE: Tx Status count record ==> %ld\n", u4TxStatusCount));
    }
#endif /* DBG */

    /* NOTE(Kevin 2007/10/22): Currently we won't process the Beacon_T_OK interrupt,
     * however the corresponding ISR will be updated even its IER didn't enable.
     * In order to suppress the warning message of INT mismatch at nicProcessIST(),
     * we'll ignore this Beacon_T_OK ISR event here after we read the value of
     * HISR each time.
     */
    au4IntStatus[INT_HISR] &= ~HISR_BEACON_T_OK;

    if (au4IntStatus[INT_HISR] & HISR_SLOW_WAKEUP) {
        au4IntStatus[INT_HISR] &= ~HISR_SLOW_WAKEUP;

        HAL_MCR_RD(prAdapter, MCR_HSCISR, &au4IntStatus[INT_HSCISR]);

        /* NOTE(Kevin 2008/01/21): Currently the Driver_Own_Back INT Status will always
         * indicate in HSCISR even when its HSCIER is not enable.
         */
        au4IntStatus[INT_HSCISR] &= ~HSCISR_DRIVER_OWN_BACK;
    }

    if (au4IntStatus[INT_HISR] & HISR_RX_DONE) {
        ASSERT(u4RxLenCount);
    }

    if (au4IntStatus[INT_HISR] & HISR_TX_DONE) {
#if CFG_WORKAROUND_HEC_5269
        *pfgValidTxStatus = TRUE;
#endif /* CFG_WORKAROUND_HEC_5269 */
        ASSERT(u4TxStatusCount);
    }

    if (u4RxLenCount) {
        /* For HEC 5354 */
        //ASSERT(au4IntStatus[INT_HISR] & HISR_RX_DONE);
        au4IntStatus[INT_HISR] |= HISR_RX_DONE;
    }

    if (u4TxStatusCount) {
        //ASSERT(au4IntStatus[INT_HISR] & HISR_TX_DONE);
        au4IntStatus[INT_HISR] |= HISR_TX_DONE;

#if CFG_WORKAROUND_HEC_5269
        *pfgValidTxStatus = TRUE;
#endif /* CFG_WORKAROUND_HEC_5269 */
    }

    return;
} /* end of halSDIOReadIntStatus() */


BOOL
halSDIOTxProcessTxStatus (
    IN P_ADAPTER_T      prAdapter,
    IN P_TX_STATUS_T    prTxStatusDone,
    OUT PP_SW_TFCB_T    pprSwTfcbDone
    )
{
    P_TX_CTRL_T prTxCtrl;
    P_TX_ACQ_PARAMETERS_T prTxACQPara;
    P_SW_TFCB_T prSwTfcb;
    P_QUE_T prActiveChainList;
    UINT_8 ucQueueIndex;
#if DBG
    PUINT_32 pu4Value = (PUINT_32)prTxStatusDone;
#endif

    DEBUGFUNC("halSDIOTxProcessTxStatus");

    ASSERT(prAdapter);
    ASSERT(prTxStatusDone);

    prTxCtrl = &prAdapter->rTxCtrl;

    DBGLOG(TX, TRACE, ("TX STATUS = [%08lx %08lx]\n", pu4Value[0], pu4Value[1]));

    //4 <1> TX STATUS Field should not empty
    if (!prTxStatusDone->ucStatusIndicationPID) { /* At least one of TX_status bit should be assert */
        return FALSE;
    }

    //4 <2> Parse the Queue Index
    ucQueueIndex = (prTxStatusDone->ucWIdxQIdx & TX_STATUS_QIDX_MASK);
    ASSERT(ucQueueIndex <= AC4);
    if (ucQueueIndex > AC4) {
        return FALSE;
    }

    //4 <3> Get the corresponding SW_TFCB_T and update flags.
    prTxACQPara = &prTxCtrl->arTxACQPara[ucQueueIndex];
    prActiveChainList = &prTxACQPara->rActiveChainList;
    QUEUE_REMOVE_HEAD(prActiveChainList, prSwTfcb, P_SW_TFCB_T);
    if (!prSwTfcb) {
        ASSERT(0);
        /* NOTE(Kevin): When JOIN_TO_NORMAL_TR, flush queue first, but
         * we didn't flush the TX_STATUS in buffer.
         * 20080129: We add the function of flush Status Buffer.
         */
        return FALSE;
    }
    ASSERT(prSwTfcb->ucAC == ucQueueIndex);

#if CFG_TX_DBG_SEQ_NUM
    DBGLOG(TX, LOUD, ("TX SEQ NUM = %04x\n", prTxStatusDone->u2FlagsALC));
#endif /* CFG_TX_DBG_SEQ_NUM */

    /* Update the bitmap of "Nonempty AC Queues" */
    if (QUEUE_IS_EMPTY(prActiveChainList)) {
        prTxCtrl->ucTxNonEmptyACQ &= ~BIT(ucQueueIndex);
    }

    TX_ACQ_INC_CNT(prTxCtrl, ucQueueIndex, TX_ACQ_TXDONE_COUNT);

#if (CFG_TX_DBG_INCREASED_PID || CFG_TX_DBG_FIXED_PID)
    ASSERT_REPORT((prSwTfcb->ucPID == \
        (prTxStatusDone->ucStatusIndicationPID & TX_STATUS_PID_MASK)), \
        ("prSwTfcb->ucPID = %d, PID in TX_STATUS = %ld", \
            prSwTfcb->ucPID, (prTxStatusDone->ucStatusIndicationPID & TX_STATUS_PID_MASK)));
#endif /* CFG_TX_DBG_INCREASED_PID || CFG_TX_DBG_FIXED_PID */

    *pprSwTfcbDone = prSwTfcb;

    return TRUE;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Read the rx data from data port and setup RFB
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[out] prSWRfb the RFB to receive rx data
*
* \retval WLAN_STATUS_SUCCESS: SUCCESS
* \retval WLAN_STATUS_FAILURE: FAILURE
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
halSDIORxFillRFB (
    IN P_ADAPTER_T prAdapter,
    IN UINT_16 u2RxLengthDW,
    IN OUT P_SW_RFB_T prSWRfb
    )
{
    P_RX_CTRL_T prRxCtrl;
    PUINT_8 pucBuf;
    P_RX_STATUS_T prRxStatus;
    UINT_16 u2RfbDWSize = 0;
    UINT_16 u2PktLen = 0;
    UINT_8 ucExtOffset = 0;
    WLAN_STATUS u4Status = WLAN_STATUS_FAILURE;
    BOOLEAN fgResult = TRUE;
#if CFG_LP_PATTERN_SEARCH_SLT
    PUINT_16 pu2ProtocolType = NULL;
#endif

    DEBUGFUNC("halSDIORxFillRFB");

    ASSERT(prAdapter);
    ASSERT(prSWRfb);

    prRxCtrl = &prAdapter->rRxCtrl;
    pucBuf = (PUINT_8)prSWRfb->pucRecvBuff;
    prRxStatus = prSWRfb->prRxStatus;

    ASSERT(prRxStatus);

    do {

        //4 <1> Check RFB frame length for maximum acceptable length
        u2RfbDWSize = u2RxLengthDW & RX_STATUS_BUFFER_LENGTH_MASK;
        if (u2RfbDWSize > BYTE_TO_DWORD(CFG_RX_MAX_PKT_SIZE)) {
            halRxReadDone(prAdapter);
            break;
        }

        //4 <2> Read RFB frame from HRDR
        HAL_PORT_RD(prAdapter,
                    MCR_HRDR,
                    DWORD_TO_BYTE(u2RxLengthDW & RX_STATUS_BUFFER_LENGTH_MASK),
                    pucBuf,
                    CFG_RX_MAX_PKT_SIZE);

        if (!fgResult) {
            DBGLOG(HAL, ERROR, ("Read RX Packet Lentgh Error\n"));
            break;
        }

        ASSERT(u2RfbDWSize ==
            (prRxStatus->u2OverallBufferLengthDW & RX_STATUS_BUFFER_LENGTH_MASK));

        u2PktLen = prRxStatus->u2PacketLength & RX_STATUS_PACKET_LENGTH_MASK;
        //DBGLOG(HAL, TRACE, ("RFB DW Size = %d, Packet Length = %d\n", prRxStatus->u2OverallBufferLength, prRxStatus->u2PacketLength));

        //4 <3> if the RFB dw size or packet size is zero
        if (u2RfbDWSize == 0 || u2PktLen == 0) {
            DBGLOG(HAL, ERROR, ("RFB DW Size = %d, Packet Length = %d\n", u2RfbDWSize, u2PktLen));
            ASSERT(0);
            break;
        }

        //4 <4> if the packet is too large or too small
        if (u2PktLen > CFG_RX_MAX_PKT_SIZE || u2PktLen < CFG_RX_MIN_PKT_SIZE) {
            DBGLOG(HAL, TRACE, ("Read RX Packet Lentgh Error (%d)\n", u2PktLen));

            RX_INC_CNT(prRxCtrl, RX_SIZE_ERR_DROP_COUNT);
            ASSERT(0);
            break;
        }

        //4 <5> Update Packet Drop count due to FIFO full
        if (prRxStatus->ucDropPacketNum > 0) {
            RX_ADD_CNT(prRxCtrl, RX_FIFO_FULL_DROP_COUNT, prRxStatus->ucDropPacketNum);
            DBGLOG(HAL, TRACE, ("prRxStatus->ucDropPacketNum = %d\n", prRxStatus->ucDropPacketNum));
        }

        //4 <6> Check the error bits, FCS, ICV, KEY, FORMAT
        if (RX_STATUS_IS_ERROR(prRxStatus->u2StatusFlag)) {
            RX_INC_CNT(prRxCtrl, RX_ERROR_DROP_COUNT);

            if (RX_STATUS_IS_FCS_ERROR(prRxStatus->u2StatusFlag)) {
                RX_INC_CNT(prRxCtrl, RX_FCS_ERR_DROP_COUNT);
                DBGLOG(HAL, TRACE, ("RX_STATUS_IS_FCS_ERROR\n"));
                break;
            }
            if (RX_STATUS_IS_ICV_ERROR(prRxStatus->u2StatusFlag)) {
                RX_INC_CNT(prRxCtrl, RX_ICV_ERR_DROP_COUNT);
                DBGLOG(HAL, TRACE, ("RX_STATUS_IS_ICV_ERROR\n"));
                break;
            }
            if (
                #if SUPPORT_WAPI
                !prAdapter->fgUseWapi &&
                #endif
                RX_STATUS_IS_KEY_ERROR(prRxStatus->u2StatusFlag)) {
                RX_INC_CNT(prRxCtrl, RX_KEY_ERR_DROP_COUNT);
                DBGLOG(HAL, TRACE, ("RX_STATUS_IS_KEY_ERROR\n"));
                break;
            }
            if (RX_STATUS_IS_FORMAT_ERROR(prRxStatus->u2StatusFlag)) {
                RX_INC_CNT(prRxCtrl, RX_FORMAT_ERR_DROP_COUNT);
                DBGLOG(HAL, TRACE, ("RX_STATUS_IS_FORMAT_ERROR\n"));
                break;
            }
        }

        //4 <7><todo> look up the station record for the incoming packet
#if 1
        prSWRfb->prStaRec =
            staRecGetStaRecordByAddr(prAdapter, prRxStatus->aucTA);
        if (!prSWRfb->prStaRec) {

        }
#endif

#if CFG_IBSS_POWER_SAVE & CFG_IBSS_POWER_SAVE_WITH_THROUGHPUT_ENHANCE
        if (PM_IS_UNDER_IBSS_POWER_SAVE_MODE(prAdapter)) {
            if (prSWRfb->prStaRec && RX_STATUS_IS_DATA_FRAME(prRxStatus->u2StatusFlag)) {
                prSWRfb->prStaRec->fgIsAdhocStaAwake = TRUE;
            }
        }
#endif /* CFG_IBSS_POWER_SAVE & CFG_IBSS_POWER_SAVE_WITH_THROUGHPUT_ENHANCE */

        prSWRfb->ucQosTID= prRxStatus->u2QoSCtrl & RX_STATUS_QOS_TID_MASK;
        prSWRfb->fgIs8023 = !RX_STATUS_IS_802_11(prRxStatus->u2StatusFlag);
        prSWRfb->fgIsNullData = FALSE;


        //4 <8> process Extension field.
        if (prRxCtrl->fgIsRxStatusG0) {

            prSWRfb->prG0 = (P_RX_STATUS_G0_T)((UINT_32)prSWRfb->pucRecvBuff +
                                sizeof(RX_STATUS_T));
            ucExtOffset += sizeof(RX_STATUS_G0_T);
        }
        if (prRxCtrl->fgIsRxStatusG1) {
            prSWRfb->prG1 = (P_RX_STATUS_G1_T)((UINT_32)prSWRfb->pucRecvBuff +
                                sizeof(RX_STATUS_T)+ucExtOffset);
            ucExtOffset += sizeof(RX_STATUS_G1_T);
        }
        if (prRxCtrl->fgIsRxStatusG2) {
            prSWRfb->prG2 = (P_RX_STATUS_G2_T)((UINT_32)prSWRfb->pucRecvBuff +
                               sizeof(RX_STATUS_T)+ucExtOffset);
            ucExtOffset += sizeof(RX_STATUS_G2_T);
            /*Update short long preamble count for CCK packet*/
            if ( (prSWRfb->prG2->u2NFRate & RX_STATUS_G2_RATE_MASK) <= RATE_CCK_11M_SHORT ) {
                if ((prSWRfb->prG2->u2NFRate & RATE_CCK_SHORT_PREAMBLE) ) {
                    RX_INC_CNT(prRxCtrl, RX_MPDU_CCK_SHORT_PREAMBLE_COUNT);
                }
                else {
                    RX_INC_CNT(prRxCtrl, RX_MPDU_CCK_LONG_PREAMBLE_COUNT);
                }

            }
        }


        if (prSWRfb->fgIs8023) {

            prSWRfb->pvHeader = (PVOID)((UINT_32)prSWRfb->pucRecvBuff +
                                sizeof(RX_STATUS_T) + RX_HEADER_OFFSET+ucExtOffset);


            prSWRfb->pvBody = (PVOID)((UINT_32)prSWRfb->pvHeader + ETHER_HEADER_LEN);

            prSWRfb->fgIsDataFrame = TRUE;
            prSWRfb->u2MACHeaderLength= ETHER_HEADER_LEN;
            RX_INC_CNT(prRxCtrl, RX_DATA_FRAME_COUNT);

            if (RX_STATUS_IS_BMC(prRxStatus->u2StatusFlag)) {
                RX_INC_CNT(prRxCtrl, RX_BMCAST_DATA_FRAME_COUNT);
            }
            else {
                RX_INC_CNT(prRxCtrl, RX_UCAST_DATA_FRAME_COUNT);
                if (!prSWRfb->fgIsNullData) {
                    ARB_INDICATE_UC_DATA_FRAME_RECEICED(prAdapter,
                                                        RX_STATUS_IS_MORE_DATA(prRxStatus));
                }
            }
        }
        else {
            if (RX_STATUS_IS_QoS(prRxStatus->u2StatusFlag)) {
                prSWRfb->pvHeader = (PVOID)((UINT_32)prSWRfb->pucRecvBuff +
                                 sizeof(RX_STATUS_T) + ((prRxStatus->ucKIdxSecMode & 0xc0)>>6)+ucExtOffset);
                prSWRfb->pvBody = (PVOID)((UINT_32)prSWRfb->pvHeader + WLAN_MAC_HEADER_QOS_LEN);
                prSWRfb->u2MACHeaderLength = WLAN_MAC_HEADER_QOS_LEN;
            }
            else {
                prSWRfb->pvHeader = (PVOID)(((UINT_32)prSWRfb->pucRecvBuff) +
                                 sizeof(RX_STATUS_T) + ((prRxStatus->ucKIdxSecMode & 0xc0)>>6)+ucExtOffset);
                prSWRfb->pvBody = (PVOID)((UINT_32)prSWRfb->pvHeader + WLAN_MAC_HEADER_LEN);
                prSWRfb->u2MACHeaderLength = WLAN_MAC_HEADER_LEN;

            }


            if (((P_WLAN_MAC_HEADER_T)prSWRfb->pvHeader)->u2FrameCtrl & MAC_FRAME_DATA) {
                UINT_16 frameType = (UINT_16)(((P_WLAN_MAC_HEADER_T)prSWRfb->pvHeader)->u2FrameCtrl & MASK_FRAME_TYPE);
                prSWRfb->fgIsDataFrame = TRUE;

                RX_INC_CNT(prRxCtrl, RX_DATA_FRAME_COUNT);

                if (frameType == MAC_FRAME_NULL ||
                    frameType == MAC_FRAME_QOS_NULL ||
                    frameType == MAC_FRAME_QOS_CF_POLL ||
                    prRxStatus->u2PacketLength <= WLAN_MAC_HEADER_LEN) {
                    prSWRfb->fgIsNullData = TRUE;
                }

                if (RX_STATUS_IS_BMC(prRxStatus->u2StatusFlag)) {
                    RX_INC_CNT(prRxCtrl, RX_BMCAST_DATA_FRAME_COUNT);
                }
                else {
                    RX_INC_CNT(prRxCtrl, RX_UCAST_DATA_FRAME_COUNT);
                    if (!prSWRfb->fgIsNullData) {
                        ARB_INDICATE_UC_DATA_FRAME_RECEICED(prAdapter,
                                                            RX_STATUS_IS_MORE_DATA(prRxStatus));
                    }
                }
            }
            else{

                RX_INC_CNT(prRxCtrl, RX_MGMT_FRAME_COUNT);

                if (RX_STATUS_IS_BMC(prRxStatus->u2StatusFlag)) {
                    RX_INC_CNT(prRxCtrl, RX_BMCAST_MGMT_FRAME_COUNT);
                }
                else {
                    RX_INC_CNT(prRxCtrl, RX_UCAST_MGMT_FRAME_COUNT);
                }


                prSWRfb->fgIsDataFrame = FALSE;
            }
        }

#if CFG_LP_PATTERN_SEARCH_SLT
    if (prAdapter->eSLTModeSel == SLT_MODE_PATTERN_SEARCH) {
        if (prRxStatus->ucReserved) {
            prAdapter->fgPatternSearchMatch = TRUE;
            if (prSWRfb->fgIs8023) {
                pu2ProtocolType = (PUINT_16)(((PUINT_8)prSWRfb->pvHeader) + MAC_ADDR_LEN * 2);
                ASSERT(*pu2ProtocolType == 0x608);
            }
            else {
                ASSERT(FALSE);   /* Unwanted packet match */
            }
        }
        else {
            if ((RX_STATUS_IS_BMC(prRxStatus->u2StatusFlag)) &&
                (prSWRfb->fgIs8023)) {
                pu2ProtocolType = (PUINT_16)(((PUINT_8)prSWRfb->pvHeader) + MAC_ADDR_LEN * 2);
                if (*pu2ProtocolType == 0x608) {
                    prAdapter->fgPatternSearchMatch = TRUE;
                }
            }
        }
    }
#endif


        prSWRfb->u2FrameLength = u2PktLen;

#if CFG_TCP_IP_CHKSUM_OFFLOAD
        if(prAdapter->u4CSUMFlags != CSUM_NOT_SUPPORTED){
            UINT_32 u4TcpUdpIpCksStatus = *((PUINT_32)((UINT_32)prRxStatus +
                (UINT_32)((prRxStatus->u2OverallBufferLengthDW - 1) << 2)));

            if (u4TcpUdpIpCksStatus & RX_CS_TYPE_IPv4) { // IPv4 packet
                prSWRfb->aeCSUM[CSUM_TYPE_IPV6] = CSUM_RES_NONE;
                if(u4TcpUdpIpCksStatus & RX_CS_STATUS_IP) { //IP packet csum failed
                    prSWRfb->aeCSUM[CSUM_TYPE_IPV4] = CSUM_RES_FAILED;
                } else {
                    prSWRfb->aeCSUM[CSUM_TYPE_IPV4] = CSUM_RES_SUCCESS;
                }

                if (u4TcpUdpIpCksStatus & RX_CS_TYPE_TCP) { //TCP packet
                    prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_NONE;
                    if(u4TcpUdpIpCksStatus & RX_CS_STATUS_TCP) { //TCP packet csum failed
                        prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_FAILED;
                    } else {
                        prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_SUCCESS;
                    }
                }
                else if (u4TcpUdpIpCksStatus & RX_CS_TYPE_UDP) { //UDP packet
                    prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_NONE;
                    if(u4TcpUdpIpCksStatus & RX_CS_STATUS_UDP) { //UDP packet csum failed
                        prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_FAILED;
                    } else {
                        prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_SUCCESS;
                    }
                }
                else {
                    prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_NONE;
                    prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_NONE;
                }

            }
            else if (u4TcpUdpIpCksStatus & RX_CS_TYPE_IPv6) {//IPv6 packet
                prSWRfb->aeCSUM[CSUM_TYPE_IPV4] = CSUM_RES_NONE;
                prSWRfb->aeCSUM[CSUM_TYPE_IPV6] = CSUM_RES_SUCCESS;

                if (u4TcpUdpIpCksStatus & RX_CS_TYPE_TCP) { //TCP packet
                    prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_NONE;
                    if(u4TcpUdpIpCksStatus & RX_CS_STATUS_TCP) { //TCP packet csum failed
                        prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_FAILED;
                    } else {
                        prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_SUCCESS;
                    }
                }
                else if (u4TcpUdpIpCksStatus & RX_CS_TYPE_UDP) { //UDP packet
                    prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_NONE;
                    if(u4TcpUdpIpCksStatus & RX_CS_STATUS_UDP) { //UDP packet csum failed
                        prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_FAILED;
                    } else {
                        prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_SUCCESS;
                    }
                }
                else {
                    prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_NONE;
                    prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_NONE;
                }
            }
            else {
                prSWRfb->aeCSUM[CSUM_TYPE_IPV4] = CSUM_RES_NONE;
                prSWRfb->aeCSUM[CSUM_TYPE_IPV6] = CSUM_RES_NONE;
            }

        }

#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */

        u4Status = WLAN_STATUS_SUCCESS;
    }
    while (FALSE);

    return u4Status;
}

#else

/*----------------------------------------------------------------------------*/
/*!
* \brief Read interrupt status from hardware
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[out] the interrupts
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halReadIntStatus (
    IN P_ADAPTER_T     prAdapter,
    OUT UINT_32        au4IntStatus[]
    )
{

    ASSERT(au4IntStatus);

    au4IntStatus[INT_HISR] = 0;
    au4IntStatus[INT_HSCISR] = 0;

    ASSERT(prAdapter);

    HAL_MCR_RD(prAdapter, MCR_HISR, &au4IntStatus[INT_HISR]);

    /* NOTE(Kevin 2007/10/22): Currently we won't process the Beacon_T_OK interrupt,
     * however the corresponding ISR will be updated even its IER didn't enable.
     * In order to suppress the warning message of INT mismatch at nicProcessIST(),
     * we'll ignore this Beacon_T_OK ISR event here after we read the value of
     * HISR each time.
     */
    au4IntStatus[INT_HISR] &= ~HISR_BEACON_T_OK;


#if CFG_INT_WRITE_CLEAR
    HAL_MCR_WR(prAdapter, MCR_HISR, (au4IntStatus[INT_HISR] & ~(HISR_TX_DONE | HISR_RX_DONE)));
#endif /* CFG_INT_WRITE_CLEAR */

    if (au4IntStatus[INT_HISR] & HISR_SLOW_WAKEUP) {
        au4IntStatus[INT_HISR] &= ~HISR_SLOW_WAKEUP;

        HAL_MCR_RD(prAdapter, MCR_HSCISR, &au4IntStatus[INT_HSCISR]);
#if CFG_INT_WRITE_CLEAR
        HAL_MCR_WR(prAdapter, MCR_HSCISR, au4IntStatus[INT_HSCISR]);
#endif /* CFG_INT_WRITE_CLEAR */

        /* NOTE(Kevin 2008/01/21): Currently the Driver_Own_Back INT Status will always
         * indicate in HSCISR even when its HSCIER is not enable.
         */
        au4IntStatus[INT_HSCISR] &= ~HSCISR_DRIVER_OWN_BACK;
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Read the rx data from data port and setup RFB
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[out] prSWRfb the RFB to receive rx data
*
* \retval WLAN_STATUS_SUCCESS: SUCCESS
* \retval WLAN_STATUS_FAILURE: FAILURE
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
halRxFillRFB (
    IN P_ADAPTER_T prAdapter,
    OUT P_SW_RFB_T prSWRfb
    )
{
    P_RX_CTRL_T prRxCtrl;
    PUINT_8 pucBuf;
    P_RX_STATUS_T prRxStatus;
    UINT_16 u2RfbDWSize = 0;
    UINT_16 u2PktLen = 0;
    BOOLEAN fgIsReadDone = FALSE;
    UINT_8 ucExtOffset = 0;
    WLAN_STATUS u4Status = WLAN_STATUS_SUCCESS;
    BOOLEAN fgResult = TRUE;

    ASSERT(prAdapter);
    ASSERT(prSWRfb);

    prRxCtrl = &prAdapter->rRxCtrl;
    pucBuf = (PUINT_8)prSWRfb->pucRecvBuff;
    prRxStatus = prSWRfb->prRxStatus;
    do {
        /* Read the RFB DW length and packet length */
        HAL_PORT_RD(prAdapter, MCR_HRDR, RX_RFB_LEN_FIELD_LEN, pucBuf, RX_RFB_LEN_FIELD_LEN);
        if(!fgResult) {
            DBGLOG(HAL, ERROR, ("Read RX Packet Lentgh Error\n"));
            return WLAN_STATUS_FAILURE;
        }

        //4 <1> if the 1st DW of RFB is zero
        //ASSERT_REPORT(*(PUINT_32)pucBuf, "GET 0 from HRDR\n");
        if(*(PUINT_32)pucBuf == 0){
            DBGLOG(HAL, TRACE, ("Get 0 from HRDR\n"));
            return WLAN_STATUS_FAILURE;
        }

        u2RfbDWSize = prRxStatus->u2OverallBufferLengthDW & RX_STATUS_BUFFER_LENGTH_MASK;
        u2PktLen = prRxStatus->u2PacketLength & 0xfff;
        //DBGLOG(HAL, TRACE, ("RFB DW Size = %d, Packet Length = %d\n", prRxStatus->u2OverallBufferLength, prRxStatus->u2PacketLength));

        //4 <2> if the RFB dw size or packet size is zero
        if(u2RfbDWSize == 0 || u2PktLen == 0) {
            DBGLOG(HAL, ERROR, ("RFB DW Size = %d, Packet Length = %d\n", u2RfbDWSize, u2PktLen));
            u4Status = WLAN_STATUS_FAILURE;
            fgIsReadDone = TRUE;
            break;
        }

        //4 <3> if the packet is too large or too small
        if(u2PktLen > CFG_RX_MAX_PKT_SIZE || u2PktLen < CFG_RX_MIN_PKT_SIZE) {
            DBGLOG(HAL, TRACE, ("Read RX Packet Lentgh Error (%d)\n", u2PktLen));

            RX_INC_CNT(prRxCtrl, RX_SIZE_ERR_DROP_COUNT);
            fgIsReadDone = TRUE;
            u4Status = WLAN_STATUS_FAILURE;
            break;
        }

        //4 <4> Read Entire RFB and packet
        HAL_PORT_RD(prAdapter,
                    MCR_HRDR,
                    DWORD_TO_BYTE(u2RfbDWSize - 1),
                    pucBuf + RX_RFB_LEN_FIELD_LEN,
                    (CFG_RX_MAX_PKT_SIZE - RX_RFB_LEN_FIELD_LEN));

        if(!fgResult) {
            //DBGLOG(HAL, ERROR, ("Status: 0x%08x RX Byte Count:%d %d 0x%08x\n", (u2RfbDWSize-1)*4));
            return WLAN_STATUS_FAILURE;
        }


        if(prRxStatus->ucDropPacketNum > 0){
            RX_ADD_CNT(prRxCtrl, RX_FIFO_FULL_DROP_COUNT, prRxStatus->ucDropPacketNum);
            DBGLOG(HAL, TRACE, ("prRxStatus->ucDropPacketNum = %d\n", prRxStatus->ucDropPacketNum));
        }

        ASSERT(prRxStatus);

#if CFG_LP_PATTERN_SEARCH_SLT
        if (prAdapter->eSLTModeSel == SLT_MODE_PATTERN_SEARCH) {
            if (RX_STATUS_IS_PACKET_WANTED(prRxStatus->ucReserved)) {
                prAdapter->fgPatternSearchMatch = TRUE;
            }
        }
#endif

        //DBGLOG(HAL, TRACE, ("RFB DW Size = %d, Packet Length = %d\n", prRxStatus->u2OverallBufferLength, prRxStatus->u2PacketLength));

        //4 <5> Check the error bits, FCS, ICV, KEY, FORMAT
        if (RX_STATUS_IS_ERROR(prRxStatus->u2StatusFlag)) {
            RX_INC_CNT(prRxCtrl, RX_ERROR_DROP_COUNT);

            if (RX_STATUS_IS_FCS_ERROR(prRxStatus->u2StatusFlag)) {
                RX_INC_CNT(prRxCtrl, RX_FCS_ERR_DROP_COUNT);
                DBGLOG(HAL, TRACE, ("RX_STATUS_IS_FCS_ERROR\n"));
                u4Status = WLAN_STATUS_FAILURE;
                break;
            }
            if (RX_STATUS_IS_ICV_ERROR(prRxStatus->u2StatusFlag)) {
                RX_INC_CNT(prRxCtrl, RX_ICV_ERR_DROP_COUNT);
                DBGLOG(HAL, TRACE, ("RX_STATUS_IS_ICV_ERROR\n"));
                u4Status = WLAN_STATUS_FAILURE;
                break;
            }
            if (
                #if SUPPORT_WAPI
                !prAdapter->fgUseWapi &&
                #endif
                RX_STATUS_IS_KEY_ERROR(prRxStatus->u2StatusFlag)) {
                RX_INC_CNT(prRxCtrl, RX_KEY_ERR_DROP_COUNT);
                DBGLOG(HAL, TRACE, ("RX_STATUS_IS_KEY_ERROR\n"));
                u4Status = WLAN_STATUS_FAILURE;
                break;
            }
            if (RX_STATUS_IS_FORMAT_ERROR(prRxStatus->u2StatusFlag)) {
                RX_INC_CNT(prRxCtrl, RX_FORMAT_ERR_DROP_COUNT);
                DBGLOG(HAL, TRACE, ("RX_STATUS_IS_FORMAT_ERROR\n"));
                u4Status = WLAN_STATUS_FAILURE;
                break;
            }
        }

        //DBGLOG(HAL, TRACE, ("RFB DW Size = %d, Packet Length = %d\n", prRxStatus->u2OverallBufferLength, prRxStatus->u2PacketLength));
        //4 <6><todo> look up the station record for the incoming packet
#if 1
        prSWRfb->prStaRec =
            staRecGetStaRecordByAddr(prAdapter, prRxStatus->aucTA);
        if(!prSWRfb->prStaRec) {

        }
#endif

#if CFG_IBSS_POWER_SAVE & CFG_IBSS_POWER_SAVE_WITH_THROUGHPUT_ENHANCE
        if (PM_IS_UNDER_IBSS_POWER_SAVE_MODE(prAdapter)) {
            if (prSWRfb->prStaRec && RX_STATUS_IS_DATA_FRAME(prRxStatus->u2StatusFlag)) {
                prSWRfb->prStaRec->fgIsAdhocStaAwake = TRUE;
            }
        }
#endif /* CFG_IBSS_POWER_SAVE & CFG_IBSS_POWER_SAVE_WITH_THROUGHPUT_ENHANCE */

        prSWRfb->ucQosTID= prRxStatus->u2QoSCtrl & RX_STATUS_QOS_TID_MASK;
        prSWRfb->fgIs8023 = !RX_STATUS_IS_802_11(prRxStatus->u2StatusFlag);
        prSWRfb->fgIsNullData = FALSE;

        //DBGLOG(HAL, TRACE, ("RFB DW Size = %d, Packet Length = %d\n", prRxStatus->u2OverallBufferLength, prRxStatus->u2PacketLength));

        //4 <7> process Extension field.
        if(prRxCtrl->fgIsRxStatusG0) {

            prSWRfb->prG0 = (P_RX_STATUS_G0_T)((UINT_32)prSWRfb->pucRecvBuff +
                                sizeof(RX_STATUS_T));
            ucExtOffset += sizeof(RX_STATUS_G0_T);
        }
        if(prRxCtrl->fgIsRxStatusG1){
            prSWRfb->prG1 = (P_RX_STATUS_G1_T)((UINT_32)prSWRfb->pucRecvBuff +
                                sizeof(RX_STATUS_T)+ucExtOffset);
            ucExtOffset += sizeof(RX_STATUS_G1_T);
            }
        if(prRxCtrl->fgIsRxStatusG2){
            prSWRfb->prG2 = (P_RX_STATUS_G2_T)((UINT_32)prSWRfb->pucRecvBuff +
                               sizeof(RX_STATUS_T)+ucExtOffset);
            ucExtOffset += sizeof(RX_STATUS_G2_T);
            /*Update short long preamble count for CCK packet*/
            if( (prSWRfb->prG2->u2NFRate & RX_STATUS_G2_RATE_MASK) <= RATE_CCK_11M_SHORT ) {
                if((prSWRfb->prG2->u2NFRate & RATE_CCK_SHORT_PREAMBLE) ) {
                    RX_INC_CNT(prRxCtrl, RX_MPDU_CCK_SHORT_PREAMBLE_COUNT);
                }
                else {
                    RX_INC_CNT(prRxCtrl, RX_MPDU_CCK_LONG_PREAMBLE_COUNT);
                }

            }
            }


        if (prSWRfb->fgIs8023) {

            prSWRfb->pvHeader = (PVOID)((UINT_32)prSWRfb->pucRecvBuff +
                                sizeof(RX_STATUS_T) + RX_HEADER_OFFSET+ucExtOffset);


            prSWRfb->pvBody = (PVOID)((UINT_32)prSWRfb->pvHeader + ETHER_HEADER_LEN);

            prSWRfb->fgIsDataFrame = TRUE;
            prSWRfb->u2MACHeaderLength= ETHER_HEADER_LEN;
            RX_INC_CNT(prRxCtrl, RX_DATA_FRAME_COUNT);

            if (RX_STATUS_IS_BMC(prRxStatus->u2StatusFlag)) {
                RX_INC_CNT(prRxCtrl, RX_BMCAST_DATA_FRAME_COUNT);
            }
            else {
                RX_INC_CNT(prRxCtrl, RX_UCAST_DATA_FRAME_COUNT);
                if (!prSWRfb->fgIsNullData) {
                    ARB_INDICATE_UC_DATA_FRAME_RECEICED(prAdapter,
                                                        RX_STATUS_IS_MORE_DATA(prRxStatus));
                }
            }
        }
        else {
            if (RX_STATUS_IS_QoS(prRxStatus->u2StatusFlag)) {
                prSWRfb->pvHeader = (PVOID)((UINT_32)prSWRfb->pucRecvBuff +
                                 sizeof(RX_STATUS_T) + ((prRxStatus->ucKIdxSecMode & 0xc0)>>6)+ucExtOffset);
                prSWRfb->pvBody = (PVOID)((UINT_32)prSWRfb->pvHeader + WLAN_MAC_HEADER_QOS_LEN);
                prSWRfb->u2MACHeaderLength = WLAN_MAC_HEADER_QOS_LEN;
            }
            else {
                prSWRfb->pvHeader = (PVOID)(((UINT_32)prSWRfb->pucRecvBuff) +
                                 sizeof(RX_STATUS_T) + ((prRxStatus->ucKIdxSecMode & 0xc0)>>6)+ucExtOffset);
                prSWRfb->pvBody = (PVOID)((UINT_32)prSWRfb->pvHeader + WLAN_MAC_HEADER_LEN);
                prSWRfb->u2MACHeaderLength = WLAN_MAC_HEADER_LEN;

            }


            if (((P_WLAN_MAC_HEADER_T)prSWRfb->pvHeader)->u2FrameCtrl & MAC_FRAME_DATA) {
                UINT_16 frameType = (UINT_16)(((P_WLAN_MAC_HEADER_T)prSWRfb->pvHeader)->u2FrameCtrl & MASK_FRAME_TYPE);
                prSWRfb->fgIsDataFrame = TRUE;

                RX_INC_CNT(prRxCtrl, RX_DATA_FRAME_COUNT);

                if (frameType == MAC_FRAME_NULL ||
                    frameType == MAC_FRAME_QOS_NULL ||
                    frameType == MAC_FRAME_QOS_CF_POLL ||
                    prRxStatus->u2PacketLength <= WLAN_MAC_HEADER_LEN) {
                    prSWRfb->fgIsNullData = TRUE;
                }

                if (RX_STATUS_IS_BMC(prRxStatus->u2StatusFlag)) {
                    RX_INC_CNT(prRxCtrl, RX_BMCAST_DATA_FRAME_COUNT);
                }
                else {
                    RX_INC_CNT(prRxCtrl, RX_UCAST_DATA_FRAME_COUNT);
                    if (!prSWRfb->fgIsNullData) {
                        ARB_INDICATE_UC_DATA_FRAME_RECEICED(prAdapter,
                                                            RX_STATUS_IS_MORE_DATA(prRxStatus));
                    }
                }
            }
            else{

                RX_INC_CNT(prRxCtrl, RX_MGMT_FRAME_COUNT);

                if (RX_STATUS_IS_BMC(prRxStatus->u2StatusFlag)) {
                    RX_INC_CNT(prRxCtrl, RX_BMCAST_MGMT_FRAME_COUNT);
                }
                else {
                    RX_INC_CNT(prRxCtrl, RX_UCAST_MGMT_FRAME_COUNT);
                }


                prSWRfb->fgIsDataFrame = FALSE;
            }
        }


        prSWRfb->u2FrameLength = u2PktLen;


#if CFG_TCP_IP_CHKSUM_OFFLOAD
    if(prAdapter->u4CSUMFlags != CSUM_NOT_SUPPORTED){
        UINT_32 u4TcpUdpIpCksStatus = *((PUINT_32)((UINT_32)prRxStatus +
            (UINT_32)((prRxStatus->u2OverallBufferLengthDW - 1) << 2)));

        if (u4TcpUdpIpCksStatus & RX_CS_TYPE_IPv4) { // IPv4 packet
            prSWRfb->aeCSUM[CSUM_TYPE_IPV6] = CSUM_RES_NONE;
            if(u4TcpUdpIpCksStatus & RX_CS_STATUS_IP) { //IP packet csum failed
                prSWRfb->aeCSUM[CSUM_TYPE_IPV4] = CSUM_RES_FAILED;
            } else {
                prSWRfb->aeCSUM[CSUM_TYPE_IPV4] = CSUM_RES_SUCCESS;
            }

            if (u4TcpUdpIpCksStatus & RX_CS_TYPE_TCP) { //TCP packet
                prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_NONE;
                if(u4TcpUdpIpCksStatus & RX_CS_STATUS_TCP) { //TCP packet csum failed
                    prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_FAILED;
                } else {
                    prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_SUCCESS;
                }
            }
            else if (u4TcpUdpIpCksStatus & RX_CS_TYPE_UDP) { //UDP packet
                prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_NONE;
                if(u4TcpUdpIpCksStatus & RX_CS_STATUS_UDP) { //UDP packet csum failed
                    prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_FAILED;
                } else {
                    prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_SUCCESS;
                }
            }
            else {
                prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_NONE;
                prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_NONE;
            }

        }
        else if (u4TcpUdpIpCksStatus & RX_CS_TYPE_IPv6) {//IPv6 packet
            prSWRfb->aeCSUM[CSUM_TYPE_IPV4] = CSUM_RES_NONE;
            prSWRfb->aeCSUM[CSUM_TYPE_IPV6] = CSUM_RES_SUCCESS;

            if (u4TcpUdpIpCksStatus & RX_CS_TYPE_TCP) { //TCP packet
                prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_NONE;
                if(u4TcpUdpIpCksStatus & RX_CS_STATUS_TCP) { //TCP packet csum failed
                    prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_FAILED;
                } else {
                    prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_SUCCESS;
                }
            }
            else if (u4TcpUdpIpCksStatus & RX_CS_TYPE_UDP) { //UDP packet
                prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_NONE;
                if(u4TcpUdpIpCksStatus & RX_CS_STATUS_UDP) { //UDP packet csum failed
                    prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_FAILED;
                } else {
                    prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_SUCCESS;
                }
            }
            else {
                prSWRfb->aeCSUM[CSUM_TYPE_UDP] = CSUM_RES_NONE;
                prSWRfb->aeCSUM[CSUM_TYPE_TCP] = CSUM_RES_NONE;
            }
        }
        else {
            prSWRfb->aeCSUM[CSUM_TYPE_IPV4] = CSUM_RES_NONE;
            prSWRfb->aeCSUM[CSUM_TYPE_IPV6] = CSUM_RES_NONE;
        }

    }

#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */

    } while (FALSE);

    //DBGLOG(HAL, TRACE, ("RFB DW Size = %d, Packet Length = %d\n", prRxStatus->u2OverallBufferLength, prRxStatus->u2PacketLength));

    if(fgIsReadDone){
        halRxReadDone(prAdapter);
    }

    return u4Status;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Read Tx status status from hardware
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[out] prTxStatusDone the tx done status
* \param[out] pprSwTfcbDone The SW tfcb pointer
*
* \return TRUE - Got tx status
*            FALSE - Not got tx status
*
*/
/*----------------------------------------------------------------------------*/
BOOL
halTxReadTxStatus (
    IN P_ADAPTER_T      prAdapter,
    OUT P_TX_STATUS_T   prTxStatusDone,
    OUT PP_SW_TFCB_T    pprSwTfcbDone
    )
{
    P_TX_CTRL_T prTxCtrl;
    UINT_32 au4Value[2] = {0};
    P_TX_STATUS_T prTxStatus;
    P_TX_ACQ_PARAMETERS_T prTxACQPara;
    P_SW_TFCB_T prSwTfcb;
    P_QUE_T prActiveChainList;
    UINT_8 ucQueueIndex;

    DEBUGFUNC("halTxReadTxStatus");

    ASSERT(prAdapter);
    ASSERT(prTxStatusDone);

    prTxCtrl = &prAdapter->rTxCtrl;
    prTxStatus = (P_TX_STATUS_T)&au4Value[0];

    if (HAL_TEST_FLAG(prAdapter->rArbInfo, ADAPTER_FLAG_HW_ERR)){
        return FALSE;
    }

    do {
        //4 <1> Read a DW from HTSR.
        HAL_MCR_RD(prAdapter, MCR_HTSR, &au4Value[0]);

#if CFG_TX_DBG_INT_FALSE_ALARM

        if (prTxCtrl->fgIsSkipTxFalseAlarmCheck) {
            /* Skip this time, but we will continue check next time */
            prTxCtrl->fgIsSkipTxFalseAlarmCheck = FALSE;
        }
        else {
            ASSERT(au4Value[0]);
        }

#endif /* CFG_TX_DBG_INT_FALSE_ALARM */

        if (au4Value[0] == 0) {

            /* If we do "Logical Reset" before processing TX_STATUS, all TX_STATUSs
             * will be cleared to 0.
             */

            *prTxStatusDone = *prTxStatus; /* Also clear the return TX STATUS */

            return FALSE;
        }

        //4 <2> TX STATUS Field should not empty
        ASSERT(prTxStatus->ucStatusIndicationPID); /* At least one of TX_status bit should be assert */

        //4 <3> Read additional DW from HTSR.
        HAL_MCR_RD(prAdapter, MCR_HTSR, &au4Value[1]);
        *prTxStatusDone = *prTxStatus;

        DBGLOG(TX, TRACE, ("TX STATUS = [%08lx %08lx]\n", au4Value[0], au4Value[1]));

        //4 <4> Parse the Queue Index
        ucQueueIndex = (prTxStatus->ucWIdxQIdx & TX_STATUS_QIDX_MASK);
        ASSERT(ucQueueIndex <= AC4);
        if (ucQueueIndex > AC4) {
            return FALSE;
        }

        //4 <5> Get the corresponding SW_TFCB_T and update flags.
        prTxACQPara = &prTxCtrl->arTxACQPara[ucQueueIndex];
        prActiveChainList = &prTxACQPara->rActiveChainList;
        QUEUE_REMOVE_HEAD(prActiveChainList, prSwTfcb, P_SW_TFCB_T);
        if (!prSwTfcb) {
            ASSERT(0);
            return FALSE;
        }
        ASSERT(prSwTfcb->ucAC == ucQueueIndex);

#if CFG_TX_DBG_SEQ_NUM
        DBGLOG(TX, LOUD, ("TX SEQ NUM = %04x\n", prTxStatusDone->u2FlagsALC));
#endif /* CFG_TX_DBG_SEQ_NUM */

        /* Update the bitmap of "Nonempty AC Queues" */
        if (QUEUE_IS_EMPTY(prActiveChainList)) {
            prTxCtrl->ucTxNonEmptyACQ &= ~BIT(ucQueueIndex);
        }

        TX_ACQ_INC_CNT(prTxCtrl, ucQueueIndex, TX_ACQ_TXDONE_COUNT);

#if (CFG_TX_DBG_INCREASED_PID || CFG_TX_DBG_FIXED_PID)
        ASSERT_REPORT((prSwTfcb->ucPID == \
            (prTxStatus->ucStatusIndicationPID & TX_STATUS_PID_MASK)), \
            ("prSwTfcb->ucPID = %d, PID in TX_STATUS = %ld", \
                prSwTfcb->ucPID, (prTxStatus->ucStatusIndicationPID & TX_STATUS_PID_MASK)));
#endif /* CFG_TX_DBG_INCREASED_PID || CFG_TX_DBG_FIXED_PID */

        ASSERT(pprSwTfcbDone);
        *pprSwTfcbDone = prSwTfcb;

    }
    while (FALSE);

    return TRUE;
}
#endif /* CFG_SDIO_STATUS_ENHANCE */


/*----------------------------------------------------------------------------*/
/*!
* \brief Apply different temperature BB/RF Rx setting for MT5921
*
* \param prAdapter          Pointer to the Adapter structure
* \param ucThermo           Current Thermo Value
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
halThermoUpdateRxSetting (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_8       ucThermo
    )
{
    P_THERMO_INFO_T     prThermoInfo;
    P_EEPROM_CTRL_T     prEEPROMCtrl;
    INT_8               cCurTemp;

    DEBUGFUNC("halThermoUpdateRxSetting");

    ASSERT(prAdapter);

    prThermoInfo = &prAdapter->rThermoInfo;
    prEEPROMCtrl = &prAdapter->rEEPROMCtrl;

    DBGLOG(HAL, TRACE, ("Before change, Temp state = %d\n",\
        prThermoInfo->rState));

    ASSERT(prEEPROMCtrl->ucThermoSensorSlop);
    /*Transfer to degree*/
    HAL_THERMO_2_DEGREE(prEEPROMCtrl, ucThermo, cCurTemp );


    if(cCurTemp <= THERMO_CONDITION_NOR2LOW_TEMP) {
        /*~-5.0*/
        if(prThermoInfo->rState != LOW_TEMP) {
            prThermoInfo->rState = LOW_TEMP;
            halBBAdoptTempChange( prAdapter, prThermoInfo->rState);
            halRFAdoptTempChange( prAdapter, prThermoInfo->rState);
        }
    }
    else if (cCurTemp < THERMO_CONDITION_LOW2NOR_TEMP){
        /*-4.9~14.9*/
        switch (prThermoInfo->rState) {
        case LOW_TEMP:
            break;
        case NORMAL_TEMP:
            break;
        case HIGH_TEMP:
        case UNDEF_TEMP:
            prThermoInfo->rState = NORMAL_TEMP;
            halBBAdoptTempChange( prAdapter, prThermoInfo->rState);
            halRFAdoptTempChange( prAdapter, prThermoInfo->rState);
            break;
        default:
            DBGLOG(HAL, ERROR, ("Temperature %d is not supported\n", prThermoInfo->rState));
            return;
        }
    }
    else if (cCurTemp <= THERMO_CONDITION_HI2NOR_TEMP){
        /*15.0~35.0*/
        if(prThermoInfo->rState != NORMAL_TEMP) {
            prThermoInfo->rState = NORMAL_TEMP;
            halBBAdoptTempChange( prAdapter, prThermoInfo->rState);
            halRFAdoptTempChange( prAdapter, prThermoInfo->rState);
        }


    }
    else if (cCurTemp < THERMO_CONDITION_NOR2HI_TEMP){
        /*35.1~54.9*/
        switch (prThermoInfo->rState) {
        case LOW_TEMP:
        case UNDEF_TEMP:
            prThermoInfo->rState = NORMAL_TEMP;
            halBBAdoptTempChange( prAdapter, prThermoInfo->rState);
            halRFAdoptTempChange( prAdapter, prThermoInfo->rState);
            break;
        case NORMAL_TEMP:
            break;
        case HIGH_TEMP:
            break;
        default:
            DBGLOG(HAL, ERROR, ("Temperature %d is not supported\n", prThermoInfo->rState));
            return;
        }
    }
    else {
        /*55.0~*/
        if(prThermoInfo->rState != HIGH_TEMP) {
            prThermoInfo->rState = HIGH_TEMP;
            halBBAdoptTempChange( prAdapter, prThermoInfo->rState);
            halRFAdoptTempChange( prAdapter, prThermoInfo->rState);
        }

    }

    DBGLOG(HAL, TRACE, ("Current Temp = %d degree. After change, Temp state = %d\n",\
        cCurTemp, prThermoInfo->rState));

}


/*----------------------------------------------------------------------------*/
/*!
* \brief Base on Thermo Value and EEPROM info to update Tx Gain
*
* \param[in] prAdapter      pointer to the Adapter handler
* \param[in] ucChannelNum   Channel number
* \param[in] eBand          band
* \param[in] ucThermo       current Thermo value
*
* \retval WLAN_STATUS_SUCCESS Success
*/
/*----------------------------------------------------------------------------*/
VOID
halThermoUpdateTxGain (
    IN P_ADAPTER_T  prAdapter,
    IN UINT_8       ucChannelNum,
    IN ENUM_BAND_T  eBand,
    IN UINT_8       ucThermo
    )
{
    P_THERMO_INFO_T            prThermoInfo;

    DEBUGFUNC("halThermoUpdateTxGain");

    ASSERT(prAdapter);

    prThermoInfo = &prAdapter->rThermoInfo;

    DBGLOG(HAL, INFO, ("Channel = %d, eBand= %d, Thermo = %d\n",\
         ucChannelNum, eBand,  ucThermo));

    prThermoInfo->ucHwAlcValue = ucThermo;
    if (!halSetTxPowerGain( prAdapter, ucChannelNum, eBand, NULL, NULL)){
        DBGLOG(HAL, INFO, (" Set failed!"));
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Base on Channel number and band info to update Tx Gain
*
* \param[in] prAdapter      pointer to the Adapter handler
* \param[in] ucChannelNum   Channel number
* \param[in] eBand          band
* \param[out] pu4McrCFPR    pointer to variable to stored CCK gain setting
* \param[out] pu4MCROFPR    pointer to variable to stored OFDM gain setting
*
* \retval WLAN_STATUS_SUCCESS Success
*/
/*----------------------------------------------------------------------------*/

WLAN_STATUS
halSetTxPowerGain (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8      ucChannelNum,
    IN ENUM_BAND_T eBand,
    OUT PUINT_32   pu4McrCFPR,
    OUT PUINT_32   pu4MCROFPR
    )
{
    P_EEPROM_CHANNEL_CFG_ENTRY prEepChCfg;
#if !CFG_ONLY_802_11A
    P_THERMO_INFO_T            prThermoInfo;
    INT_8       cVgaSlop;
    INT_8       cThermoSlop;
#endif
    UINT_8      ucPowerGainCCK;
    UINT_8      ucPowerGainOFDM6_9;
    UINT_8      ucPowerGainOFDM12_18;
    UINT_8      ucPowerGainOFDM24_36;
    UINT_8      ucPowerGainOFDM48_54;

    INT_8       cInThermoVal = 0;
    UINT_32     u4McrTmp;

    DEBUGFUNC("halSetTxPowerGain");

    ASSERT(prAdapter);

    DBGLOG(HAL, TRACE, ("Channel = %d, eBand= %d\n",\
         ucChannelNum, eBand));

#if !CFG_ONLY_802_11A
    if(eBand != BAND_24G) {
        DBGLOG(HAL, ERROR, ("Only support 2.4GHz\n"));
        return WLAN_STATUS_INVALID_DATA;
    }
#endif
    if (ucChannelNum == 0) {
        DBGLOG(HAL, ERROR, ("Channel number is 0!\n"));
        return WLAN_STATUS_INVALID_DATA;
    }

#if !CFG_ONLY_802_11A
    prThermoInfo = &prAdapter->rThermoInfo;
    if (prThermoInfo->fgUpdateTxGainFromAlcInt == TRUE) {
        cInThermoVal = (INT_8) prThermoInfo->ucHwAlcValue;
    }
#endif

    prEepChCfg = (P_EEPROM_CHANNEL_CFG_ENTRY)prAdapter->rEEPROMCtrl.pu4EepromChCfgTable_24;

#if !CFG_ONLY_802_11A
    cVgaSlop = prAdapter->rEEPROMCtrl.ucVgaGainSlop;
    cThermoSlop = prAdapter->rEEPROMCtrl.ucThermoSensorSlop;

    ASSERT(cThermoSlop != 0 );
#endif

    /* CCK */
    TX_GAIN_UPDATA_FROM_EEPROM_ALC(EEPROM_RATE_GROUP_CCK, ucPowerGainCCK );
    DBGLOG(HAL, LOUD, ("CCK new Gain= 0x%02X\n",ucPowerGainCCK));

    /* OFDM 6 9*/
    TX_GAIN_UPDATA_FROM_EEPROM_ALC(EEPROM_RATE_GROUP_OFDM_6_9M, ucPowerGainOFDM6_9 );
    DBGLOG(HAL, LOUD, ("OFDM 6,9 new Gain= 0x%02X\n",ucPowerGainOFDM6_9));

    /* OFDM 12 18*/
    TX_GAIN_UPDATA_FROM_EEPROM_ALC(EEPROM_RATE_GROUP_OFDM_12_18M, ucPowerGainOFDM12_18);
    DBGLOG(HAL, LOUD, ("OFDM 12,18 new Gain= 0x%02X\n",ucPowerGainOFDM12_18));

    /* OFDM 24 36*/
    TX_GAIN_UPDATA_FROM_EEPROM_ALC(EEPROM_RATE_GROUP_OFDM_24_36M, ucPowerGainOFDM24_36);
    DBGLOG(HAL, LOUD, ("OFDM 24,36 new Gain= 0x%02X\n",ucPowerGainOFDM24_36));

    /* OFDM 48 54*/
    TX_GAIN_UPDATA_FROM_EEPROM_ALC(EEPROM_RATE_GROUP_OFDM_48_54M, ucPowerGainOFDM48_54);
    DBGLOG(HAL, LOUD, ("OFDM 48,54 new Gain= 0x%02X\n",ucPowerGainOFDM48_54));

#if CFG_ONLY_802_11A
    ucPowerGainCCK = 0x28;
    ucPowerGainOFDM6_9 = 0x28;
    ucPowerGainOFDM12_18 = 0x28;
    ucPowerGainOFDM24_36 = 0x28;
    ucPowerGainOFDM48_54 = 0x28;
#endif

    u4McrTmp = (ucPowerGainCCK << CFPR_FRAME_POWER_STARTBIT ) & CFPR_FRAME_POWER_MASK;

    DBGLOG(HAL, LOUD, ("MCR_CFPR = %#010lX\n", u4McrTmp));
    if ( pu4McrCFPR != NULL) {
        DBGLOG(HAL, LOUD, ("pu4McrCFPR != NULL\n"));
        *pu4McrCFPR = u4McrTmp;
    }
    else{
        HAL_MCR_WR(prAdapter, MCR_CFPR, u4McrTmp);
    }
    u4McrTmp = ((ucPowerGainOFDM6_9 << OFPR_6_9_FRAME_POWER_STARTBIT ) & OFPR_6_9_FRAME_POWER_MASK) |\
        ((ucPowerGainOFDM12_18 << OFPR_12_18_FRAME_POWER_STARTBIT ) & OFPR_12_18_FRAME_POWER_MASK) |\
        ((ucPowerGainOFDM24_36 << OFPR_24_36_FRAME_POWER_STARTBIT ) & OFPR_24_36_FRAME_POWER_MASK) |\
        ((ucPowerGainOFDM48_54 << OFPR_48_54_FRAME_POWER_STARTBIT ) & OFPR_48_54_FRAME_POWER_MASK) ;

    DBGLOG(HAL, LOUD, ("MCR_OFPR = %#010lX\n", u4McrTmp));
    if ( pu4MCROFPR != NULL) {
        DBGLOG(HAL, LOUD, ("pu4MCROFPR != NULL\n"));
        *pu4MCROFPR = u4McrTmp;
    }
    else{
        HAL_MCR_WR(prAdapter, MCR_OFPR, u4McrTmp);
    }

    return WLAN_STATUS_SUCCESS;
}


