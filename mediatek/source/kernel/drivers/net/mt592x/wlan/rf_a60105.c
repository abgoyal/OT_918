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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/rf_a60105.c#1 $
*/

/*! \file   "rf_a60105_fpga.c"
    \brief  The collection of RF60105-specific FPGA hw functions

    N/A
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
** $Log: rf_a60105.c $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\11 2008-08-22 18:00:57 GMT mtk01088
**  add function declaration, add assert check
**  \main\maintrunk.MT5921\10 2008-04-11 00:26:53 GMT mtk01385
**  1. add update RF Rx setting based on thermo info function.
**  \main\maintrunk.MT5921\9 2008-02-01 11:37:58 GMT mtk01385
**  1. fix CE 4.2 compiling error.
**  \main\maintrunk.MT5921\8 2008-02-01 10:52:39 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\7 2007-12-29 16:34:32 GMT mtk01385
**  1. remove RICR_RF_START definition
**  \main\maintrunk.MT5921\6 2007-11-19 22:02:08 GMT mtk01084
**  update RF A60105 initial table
**  \main\maintrunk.MT5921\5 2007-11-19 10:26:01 GMT mtk01385
**  1. fix typo.
**  \main\maintrunk.MT5921\4 2007-11-17 15:05:00 GMT mtk01385
**  1. add halRFGetRFChnlProgEntryFromChannelFreq function.
**  \main\maintrunk.MT5921\3 2007-11-06 19:44:44 GMT mtk01088
**  add the a60105 code
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

extern UINT_32 u4ScanInstCount;
extern BOOLEAN fgScanInited;

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

/* A60105 RF initialization table for 2.4 GHz band */
const UINT_32 au4RFInitTableForA60105_24[] = {
    0x80c63000,
    0x8004109c, //cw0
    0x801c3200,
    0x80272400, //cw4
    0x802c3cf3,
    0x8034279d,
    0x803c6666,
    0x804483B8, //cw8
    0x804f0440,
    0x8055DFF8, //cw10
    0x805F8A64, //cw11
    0x8067c89e, //cw12
    0x806e4623,
    0x80740424,
    0x80967007,
    0x809d1fff,
    0x80ae11c9,
    0x80B44034,
    0x80BE5A93,
    0x809D1E7c, /* RF Settling time for VGA GC5 fast, CW19 */
    0x80BE7A93, /* RF Settling time for RXHP 1->0 fast, CW23 */
    0x802c381f  /* RF LO current setting, CW5 */
};

/* MTK A60105 channel table for 2.4 GHz band, 20 Mhz reference clock */
const RF_CHANNEL_PROG_ENTRY arRFChannelTableForA60105[] = {
    {   0,  0, 0, 0, {0,0,0,0}},
    { CH_1,    2412000,     BAND_24G, 3,  { 0x8034278d, 0x803e6666, 0x804f0460, 0 } },
    { CH_2,    2417000,     BAND_24G, 3,  { 0x8034278d, 0x803f6666, 0x804f0440, 0 } },
    { CH_3,    2422000,     BAND_24G, 3,  { 0x8034279d, 0x803c6666, 0x804f0440, 0 } },
    { CH_4,    2427000,     BAND_24G, 3,  { 0x8034279d, 0x803d6666, 0x804f0000, 0 } },
    { CH_5,    2432000,     BAND_24G, 3,  { 0x8034279d, 0x803e6666, 0x804f0020, 0 } },
    { CH_6,    2437000,     BAND_24G, 3,  { 0x8034279d, 0x803f6666, 0x804f0040, 0 } },
    { CH_7,    2442000,     BAND_24G, 3,  { 0x803427ad, 0x803c6666, 0x804f0481, 0 } },
    { CH_8,    2447000,     BAND_24G, 3,  { 0x803427ad, 0x803d6666, 0x804f0421, 0 } },
    { CH_9,    2452000,     BAND_24G, 3,  { 0x803427ad, 0x803e6666, 0x804f0441, 0 } },
    { CH_10,   2457000,     BAND_24G, 3,  { 0x803427ad, 0x803f6666, 0x804f0421, 0 } },
    { CH_11,   2462000,     BAND_24G, 3,  { 0x803427bd, 0x803c6666, 0x804f0001, 0 } },
    { CH_12,   2467000,     BAND_24G, 3,  { 0x803427bd, 0x803d6666, 0x804f0021, 0 } },
    { CH_13,   2472000,     BAND_24G, 3,  { 0x803427bd, 0x803e6666, 0x804f0041, 0 } },
    { CH_14,   2484000,     BAND_24G, 3,  { 0x803427cf, 0x803ccccc, 0x804f0081, 0 } }
};


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

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

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID
halRFCal60105_2412_2484(
    IN P_ADAPTER_T prAdapter
    );

VOID
halRFCalPreStep(
    IN P_ADAPTER_T prAdapter
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/


/*----------------------------------------------------------------------------*/
/*!
* \brief Set the default RF initial table to EEPROM configuration
*
* \param prEEPROMCtrl      a pointer to the EEPROM configuration
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFSetInitTable (
    IN P_EEPROM_CTRL_T prEEPROMCtrl
    )
{
    prEEPROMCtrl->pu4RFInitTable_24 = (PUINT_32)&au4RFInitTableForA60105_24[0];
    prEEPROMCtrl->u4RFInitTable_24_Size = sizeof(au4RFInitTableForA60105_24) / sizeof(UINT_32);

}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to read A60105 RF Control Register (RFCR)
*
* \param [in] prAdapter a pointer to the adapter handler
* \param [in] u4Offset offset of MCR to be read
* \param [out] pu4Value Output buffer for value read
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCrRD (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32     u4Offset,
    IN PUINT_32    pu4Value
    )
{
    UINT_32 u4Tmp;
    BOOLEAN fgStatus;

    DEBUGFUNC("halRFCrRD");

    kalMdelay(1);
    /* RFCR address locates at bit 23 - bit 19,
       for read operate bit 18 = 0 */
    u4Tmp = (u4Offset & BITS(0, 4))<< 19;

    /* For read operation, bit 30 of MCR_RSDR should be 1 */
    u4Tmp |= (BIT(31) | BIT(30));

    HAL_MCR_WR(prAdapter, MCR_RSDR, u4Tmp);
    HAL_MCR_RD_AND_WAIT(prAdapter, MCR_RSDR, &u4Tmp,
            (u4Tmp & RSDR_SYNT_PROG_START) == 0, 2, 5, fgStatus);

    if (fgStatus) {
        *pu4Value = u4Tmp & BITS(0, 17);
    }
    else {
        DBGLOG(PHY, ERROR, ("RDSR read operation error.\n"));
        *pu4Value = 0xffffffff;
    }
} /* halRFCrRD */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to write A60105 RF Control Register (RFCR)
*
* \param [in] prAdapter a pointer to the adapter handler
* \param [in] u4Offset offset of MCR to be written
* \param [out] u4Value value to be written
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCrWR (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32     u4Offset,
    IN UINT_32     u4Value)
{
    UINT_32 u4Tmp;
    BOOLEAN fgStatus;

    DEBUGFUNC("halRFCrWR");
    /* RFCR address locates at bit 23 - bit 19,
       for write operate bit 18 = 1 */
    u4Tmp = ((u4Offset & BITS(0, 4))<< 19) | BIT(18) | (u4Value & BITS(0, 17));

    /* For read operation, bit 30 of MCR_PSPR should be 0 */
    u4Tmp |= BIT(31);

    HAL_MCR_WR_AND_WAIT(prAdapter, MCR_RSDR, u4Tmp ,
            RSDR_SYNT_PROG_START, 2, 5, fgStatus);

    if (!fgStatus) {
        DBGLOG(PHY, ERROR,("RSDR write operation error.\n"));
    }

    kalMdelay(1);

} /* halRFCrWR */


/*----------------------------------------------------------------------------*/
/*!
* \brief Initialize the RF
*
* \param prAdapter          a pointer to the adapter handler
*
* \param prEEPROMCtrl      a pointer to the EEPROM configuration
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFInit (
    IN P_ADAPTER_T     prAdapter,
    IN P_EEPROM_CTRL_T prEEPROMCtrl
    )
{
    UINT_32 u4RICR = 0;
    UINT_32 u4Index = 0;
    BOOLEAN fgStatus = FALSE;
    UINT_32 u4tmp;

    ASSERT(prAdapter);
    ASSERT(prEEPROMCtrl);
    
    for (u4Index = 0; u4Index < prEEPROMCtrl->u4RFInitTable_24_Size; u4Index++) {
        HAL_MCR_WR_AND_WAIT(prAdapter, MCR_RSDR, prEEPROMCtrl->pu4RFInitTable_24[u4Index],
            RSDR_SYNT_PROG_START, 2, 5, fgStatus);

        kalUdelay(20);
    }


    /* Write the per-band RF initial table to the RF chipset. */

    halRFCrRD(prAdapter, 0x00, &u4tmp);
    u4tmp &= (~BIT(14));
    halRFCrWR(prAdapter, 0x00, u4tmp);
    HAL_MCR_WR(prAdapter, MCR_RFICR, 0x1C0F18);
    halRFCalPreStep(prAdapter);
    HAL_MCR_WR(prAdapter, MCR_RFICR, 0x1C0E00);


    /* post process for some RF init */
    halRFCal60105_2412_2484(prAdapter);

}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to do T2~T6 calibraion for MTK A60105 RF chipset
*
* \param [in] prAdapter a pointer to the adapter handler
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCalPreStep (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4tmp;

    DEBUGFUNC("halRFCalPreStep");
    DBGLOG(PHY, TRACE,("\n"));

    /* T2 */
    DBGLOG(PHY, TRACE,("T2 Phase\n"));
    halRFCrRD(prAdapter, 0x00, &u4tmp);
    u4tmp = (u4tmp & (~BITS(2, 5))) | BITS(3,4);
    halRFCrWR(prAdapter, 0x00, u4tmp);
    DBGLOG(PHY, TRACE,("CW0 is writen as: 0x%lx\n", u4tmp));
    kalUdelay(40);

    /* T3 */
    DBGLOG(PHY, TRACE,("T3 Phase\n"));
    halRFCrRD(prAdapter, 0x00, &u4tmp);
    u4tmp = u4tmp | BIT(15);
    //u4tmp = 0x9098;
    halRFCrWR(prAdapter, 0x00, u4tmp);
    DBGLOG(PHY, TRACE,("CW0 is writen as: 0x%lx\n", u4tmp));
    kalUdelay(40);

    /* T4 */
    DBGLOG(PHY, TRACE,("T4 Phase\n"));
    halRFCrRD(prAdapter, 0x00, &u4tmp);
    u4tmp = (u4tmp & (~BITS(2, 5))) | BIT(3);
    //u4tmp = 0x9088;
    halRFCrWR(prAdapter, 0x00, u4tmp);
    DBGLOG(PHY, TRACE,("CW0 is writen as: 0x%lx\n", u4tmp));
    kalUdelay(80);

    /* T5 */
    DBGLOG(PHY, TRACE,("T5 Phase\n"));
    halRFCrRD(prAdapter, 0x08, &u4tmp);
    u4tmp = u4tmp | BIT(0);
    //u4tmp = 0x83b9;
    halRFCrWR(prAdapter, 0x08, u4tmp);
    DBGLOG(PHY, TRACE,("CW8 is writen as: 0x%lx\n", u4tmp));
    kalMdelay(3);

    /* T6 */
    DBGLOG(PHY, TRACE,("T6 Phase\n"));
    HAL_BBCR_WR(prAdapter, 100,  0x8080);
    HAL_BBCR_RD(prAdapter, 97, &u4tmp);
    u4tmp &= 0x00ff;
    HAL_BBCR_WR(prAdapter, 97, u4tmp | 0x0200);
    halRFCrRD(prAdapter, 0x00, &u4tmp);
    u4tmp = (u4tmp & (~BITS(2,5))) | BITS(2, 3);
    //u4tmp = 0x908c;
    halRFCrWR(prAdapter, 0x00, u4tmp);
    DBGLOG(PHY, TRACE,("CW0 is writen as: 0x%lx\n", u4tmp));
    kalMdelay(1);

    halRFCrRD(prAdapter, 0x10, &u4tmp);
    DBGLOG(PHY, TRACE,("CW16 is read as: 0x%lx\n", u4tmp));

    kalUdelay(3000);
    HAL_BBCR_RD(prAdapter, 97, &u4tmp);
    u4tmp &= ~BIT(9);
    HAL_BBCR_WR(prAdapter, 97, u4tmp);

}   /* halRFCalPreStep */



/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to do the Tx QDC, IDC, Tx gain, Tx phase
*
* \param [in] prAdapter a pointer to the adapter handler
* \param [in] ucFreqRange The range for 2.4 and 5G
*             0, 2412 ~
*             1, 4920 ~ 5080
*             2, 5170 ~ 5320
*             3, 5500 ~ 5805
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCalTxSet (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8      ucFreqRange
    )
{
    UINT_32 u4tmp;

    DEBUGFUNC("halRFCalTxSet");

    halRFCrRD(prAdapter, 0x00, &u4tmp);
    u4tmp |= BITS(0, 1);
    u4tmp &= ~BITS(2, 5);
    u4tmp |= BIT(4);
    u4tmp |= BITS(6, 9);
    u4tmp &= ~BIT(7);
    if (ucFreqRange == 1 || ucFreqRange == 2 || ucFreqRange == 3) {
        u4tmp |= BIT(14);
    }
    halRFCrWR(prAdapter, 0x00, u4tmp);
    DBGLOG(PHY, TRACE,("CW 0 is written as: 0x%08lx\n", u4tmp));

    halRFCrRD(prAdapter, 0x05, &u4tmp);
    if (ucFreqRange == 0) {
        u4tmp &= ~BITS(2, 4);
        u4tmp |= BIT(4);
    }
    else if (ucFreqRange == 1 || ucFreqRange == 2 || ucFreqRange == 3) {
        u4tmp |= BITS(5, 7);
    }
    halRFCrWR(prAdapter, 0x05, u4tmp);
    DBGLOG(PHY, TRACE,("CW 5 is written as: 0x%08lx\n", u4tmp));

    if (ucFreqRange == 0) {
    }
    else if (ucFreqRange == 1 || ucFreqRange == 2 || ucFreqRange == 3) {
        halRFCrRD(prAdapter, 0x0a, &u4tmp);
        u4tmp &= ~BITS(11, 16);
        u4tmp |= BIT(13);
        u4tmp |= BIT(14);
        u4tmp |= BIT(17);
        halRFCrWR(prAdapter, 0x0a, u4tmp);
        DBGLOG(PHY, TRACE,("CW 10 is written as: 0x%08lx\n", u4tmp));

        halRFCrRD(prAdapter, 0x0b, &u4tmp);
        u4tmp &= ~BIT(15);
        halRFCrWR(prAdapter, 0x0b, u4tmp);
        DBGLOG(PHY, TRACE,("CW 11 is written as: 0x%08lx\n", u4tmp));
    }

    halRFCrRD(prAdapter, 0x0c, &u4tmp);
    u4tmp |= BITS(5, 6);
    halRFCrWR(prAdapter, 0x0c, u4tmp);
    DBGLOG(PHY, TRACE,("CW 12 is written as: 0x%08lx\n", u4tmp));

    halRFCrRD(prAdapter, 0x0d, &u4tmp);
    u4tmp &= ~BIT(2);
    halRFCrWR(prAdapter, 0x0d, u4tmp);
    DBGLOG(PHY, TRACE,("CW 13 is written as: 0x%08lx\n", u4tmp));

    halRFCrRD(prAdapter, 0x16, &u4tmp);
    if (ucFreqRange == 0 || ucFreqRange == 1 || ucFreqRange == 2) {
        u4tmp &= ~BITS(10, 13);
        u4tmp |= BIT(14);
    }
    else if (ucFreqRange == 3) {
        u4tmp |= BITS(10, 14);
        u4tmp &= ~BIT(11);
        u4tmp &= ~BIT(13);
    }
    halRFCrWR(prAdapter, 0x16, u4tmp);
    DBGLOG(PHY, TRACE,("CW 22 is written as: 0x%08lx\n", u4tmp));

    halRFCrRD(prAdapter, 0x17, &u4tmp);
    u4tmp &= ~BIT(12);
    u4tmp &= ~BIT(1);
    halRFCrWR(prAdapter, 0x17, u4tmp);
    DBGLOG(PHY, TRACE,("CW 23 is written as: 0x%08lx\n", u4tmp));

    HAL_BBCR_WR(prAdapter, 80, 0x0);
    HAL_BBCR_WR(prAdapter, 81, 0x0);

    //FORCE RXHP high
    HAL_BBCR_WR(prAdapter, 97, 0x0008);
    HAL_BBCR_WR(prAdapter, 98, 0x0080);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to do the Rx gain, Rx phase
*
* \param [in] prAdapter a pointer to the adapter handler
*             0, 2412 ~
*             1, 4920 ~ 5080
*             2, 5170 ~ 5320
*             3, 5500 ~ 5805
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCalRxSet (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8      ucFreqRange
    )
{
    UINT_32 u4tmp;

    DEBUGFUNC("halRFCalRxSet");

    halRFCrRD(prAdapter, 0x00, &u4tmp);
    u4tmp |= BITS(0, 2);
    u4tmp &= ~BITS(3, 5);
    u4tmp |= BIT(4);
    u4tmp |= BITS(6, 9);
    u4tmp &= ~BIT(7);
    if (ucFreqRange == 1 || ucFreqRange == 2 || ucFreqRange == 3) {
        u4tmp |= BIT(14);
    }
    halRFCrWR(prAdapter, 0x00, u4tmp);
    DBGLOG(PHY, TRACE,("CW 0 is written as: 0x%08lx\n", u4tmp));

    halRFCrRD(prAdapter, 0x05, &u4tmp);
    if (ucFreqRange ==0) {
        u4tmp &= ~BITS(2, 4);
        u4tmp |= BIT(4);
    }
    else if (ucFreqRange == 1 || ucFreqRange == 2 || ucFreqRange == 3) {
        u4tmp |= BITS(5, 7);
    }
    halRFCrWR(prAdapter, 0x05, u4tmp);
    DBGLOG(PHY, TRACE,("CW 5 is written as: 0x%08lx\n", u4tmp));

    halRFCrRD(prAdapter, 0x0a, &u4tmp);
    if (ucFreqRange ==0) {
        u4tmp &= ~BITS(5, 6);
    }
    else if (ucFreqRange == 1 || ucFreqRange == 2 || ucFreqRange == 3) {
        u4tmp &= ~BITS(11, 16);
        u4tmp |= BIT(13);
        u4tmp |= BIT(14);
        u4tmp |= BIT(17);
    }
    halRFCrWR(prAdapter, 0x0a, u4tmp);
    DBGLOG(PHY, TRACE,("CW 10 is written as: 0x%08lx\n", u4tmp));

    if (ucFreqRange == 1 || ucFreqRange == 2 || ucFreqRange == 3) {
        halRFCrRD(prAdapter, 0x0b, &u4tmp);
        u4tmp &= ~BIT(15);
        halRFCrWR(prAdapter, 0x0b, u4tmp);
        DBGLOG(PHY, TRACE,("CW 11 is written as: 0x%08lx\n", u4tmp));
    }

    halRFCrRD(prAdapter, 0x0c, &u4tmp);
    u4tmp |= BITS(5, 6);
    halRFCrWR(prAdapter, 0x0c, u4tmp);
    DBGLOG(PHY, TRACE,("CW 12 is written as: 0x%08lx\n", u4tmp));

    halRFCrRD(prAdapter, 0x0d, &u4tmp);
    u4tmp &= ~BIT(2);
    halRFCrWR(prAdapter, 0x0d, u4tmp);
    DBGLOG(PHY, TRACE,("CW 13 is written as: 0x%08lx\n", u4tmp));

    halRFCrRD(prAdapter, 0x16, &u4tmp);
    if (ucFreqRange == 0 || ucFreqRange == 1 || ucFreqRange == 2) {
        u4tmp &= ~BITS(13, 14);
        u4tmp |= BITS(10, 12);
    }
    else if (ucFreqRange == 3) {
        u4tmp |= BITS(10, 14);
        u4tmp &= ~BIT(10);
        u4tmp &= ~BIT(12);
        u4tmp &= ~BIT(14);
    }
    halRFCrWR(prAdapter, 0x16, u4tmp);
    DBGLOG(PHY, TRACE,("CW 22 is written as: 0x%08lx\n", u4tmp));

    halRFCrRD(prAdapter, 0x17, &u4tmp);
    u4tmp &= ~BIT(12);
    u4tmp &= ~BIT(1);
    halRFCrWR(prAdapter, 0x17, u4tmp);
    DBGLOG(PHY, TRACE,("CW 23 is written as: 0x%08lx\n", u4tmp));

    //FORCE RXHP high
    HAL_BBCR_WR(prAdapter, 97, 0x0008);
    HAL_BBCR_WR(prAdapter, 98, 0x0080);
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to do the Tx-QDC Calibration
*
* \param [in] prAdapter a pointer to the adapter handler
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCalTxQDC (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_8         temp8;
    UINT_32        u4tmp, result, loopcount;

    DEBUGFUNC("halRFCalTxQDC");
    
    //Do TX Q-DC calibration
    HAL_BBCR_WR(prAdapter, 77, 0x0);
    HAL_BBCR_WR(prAdapter, 77, 0xa180);

    kalUdelay(700);

    loopcount = 0;
    /* wait result */
    do {
        /* read BB CR 78 */
        HAL_BBCR_RD(prAdapter, 78, &u4tmp);
        temp8 = (UINT_8)u4tmp;

        if ((temp8 & 0x80) != 0) {
            temp8 = temp8 & 0x7f;
            result = 0;
            break;
        } else {
            loopcount ++;
            result = -1;
        }
    } while (loopcount < 2);

    if (result == 0) {
        //Write compensation value in BBCR79 D14-D8
        HAL_BBCR_RD(prAdapter, 79, &u4tmp);
        u4tmp &= 0x7f;
        u4tmp |= (temp8 << 8);
        HAL_BBCR_WR(prAdapter, 79, u4tmp);
        DBGLOG(PHY, TRACE,("The calibrated TX Q DC mis. is: (%d) 0x%04lx\n", temp8, u4tmp));
    } else {
        ERRORLOG(("The calibration is failed in TX Q DC.\n"));
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to do the Tx-IDC Calibration
*
* \param [in] prAdapter a pointer to the adapter handler
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCalTxIDC (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_8         temp8;
    UINT_32        u4tmp, result, loopcount;

    DEBUGFUNC("halRFCalTxIDC");

    HAL_BBCR_WR(prAdapter, 77, 0x0);
    HAL_BBCR_WR(prAdapter, 77, 0xc180);

    kalUdelay(500);

    loopcount = 0;
    /* wait result */
    do {
        /* read BB CR 78 */
        HAL_BBCR_RD(prAdapter, 78, &u4tmp);
        temp8 = (UINT_8)u4tmp;

        if ((temp8 & 0x80) != 0) {
            temp8 = temp8 & 0x7f;
            result = 0;
            break;
        } else {
            loopcount ++;
            result = -1;
        }
    } while (loopcount < 2);

    if (result == 0) {
        //Write compensation value in BBCR79 D6-D0
        HAL_BBCR_RD(prAdapter, 79, &u4tmp);
        u4tmp &= 0x7f00;
        u4tmp |= temp8;
        HAL_BBCR_WR(prAdapter, 79, u4tmp);
        DBGLOG(PHY, TRACE,("The calibrated TX I DC mis. is: (%d) 0x%04lx\n", temp8, u4tmp));
    } else {
        ERRORLOG(("The calibration is failed in TX I DC.\n"));
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to do the Tx Gain Calibration
*
* \param [in] prAdapter a pointer to the adapter handler
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCalTxGain (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_8         temp8;
    UINT_32        u4tmp, result, loopcount;

    DEBUGFUNC("halRFCalTxGain");

    //Do Tx gain calibration
    HAL_BBCR_WR(prAdapter, 77, 0x0);
    HAL_BBCR_WR(prAdapter, 77, 0x91c0);
    loopcount = 0;

    kalMdelay(1);

    /* wait result */
    do {
        HAL_BBCR_RD(prAdapter, 78, &u4tmp);
        temp8 = (UINT_8)u4tmp;

        if ((temp8 & 0x80) != 0) {
            result = 0;
            temp8 = temp8 & 0x7f;
            break;
        } else {
            loopcount ++;
            result = -1;
        }

    } while (loopcount < 2);

    if (result != 0) {
        ERRORLOG(("The calibration is failed due to step 1 calculation.\n"));
    }

    if (result == 0) {
        HAL_BBCR_RD(prAdapter, 80, &u4tmp);
        u4tmp &= 0x7f00;
        u4tmp |= temp8;
        HAL_BBCR_WR(prAdapter, 80, u4tmp);
        DBGLOG(PHY, TRACE, ("The calibrated TX Gain: (%d) 0x%04lx\n", temp8, u4tmp));
    } else {
        ERRORLOG(("The calibration is failed in TX Gain.\n"));
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to do the Tx Phase Calibration
*
* \param [in] prAdapter a pointer to the adapter handler
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCalTxPhase (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_8         temp8;
    UINT_32        u4tmp, result, loopcount;

    DEBUGFUNC("halRFCalTxPhase");

    //Do Tx Phase calibration
    HAL_BBCR_WR(prAdapter, 77, 0x0);
    HAL_BBCR_WR(prAdapter, 77, 0x89c0);
    loopcount = 0;

    kalMdelay(1);

    /* wait result */
    do {
        /* read BB CR 78 */
        HAL_BBCR_RD(prAdapter, 78, &u4tmp);
        temp8 = (UINT_8)u4tmp;

        if ((temp8 & 0x80) != 0) {
            result = 0;
            temp8 = temp8 & 0x7f;
            break;
        } else {
            loopcount ++;
            result = -1;
        }

    } while (loopcount < 2);

    if (result != 0) {
        ERRORLOG(("The calibration is failed due to step 1 calculation.\n"));
    }
    if (result == 0) {
        HAL_BBCR_RD(prAdapter, 80, &u4tmp);
        u4tmp &= 0x7f;
        u4tmp |= (temp8 << 8);
        HAL_BBCR_WR(prAdapter, 80, u4tmp);
        DBGLOG(PHY, TRACE, ("The calibrated TX Phase: (%d) 0x%04lx\n", temp8, u4tmp));
    } else {
        ERRORLOG(("The calibration is failed in TX Phase.\n"));
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to do the Rx Gain Calibration
*
* \param [in] prAdapter a pointer to the adapter handler
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCalRxGain (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_8         temp8;
    UINT_32        u4tmp, result, loopcount;

    DEBUGFUNC("halRFCalRxGain");

    //kalMdelay(10);
    HAL_BBCR_WR(prAdapter, 77, 0x0);
    //Do Rx gain calibration
    HAL_BBCR_WR(prAdapter, 77, 0x85C0);

    loopcount = 0;
    kalMdelay(1);
    /* wait result */
    do {
        HAL_BBCR_RD(prAdapter, 78, &u4tmp);
        temp8 = (UINT_8)u4tmp;

        if ((temp8 & 0x80) != 0) {
            result = 0;
            temp8 = temp8 & 0x7f;
            break;
        } else {
            loopcount ++;
            result = -1;
        }

    } while (loopcount < 2);

    if (result != 0) {
        ERRORLOG(("The calibration is failed due to Rx Gain step 1 calculation.\n"));
    }

    if (result == 0) {
        HAL_BBCR_RD(prAdapter, 81, &u4tmp);
        u4tmp &= 0x7f00;
        u4tmp |= temp8;
        HAL_BBCR_WR(prAdapter, 81, u4tmp);
        DBGLOG(PHY, TRACE, ("The calibrated RX Gain: (%d) 0x%04lx\n", temp8, u4tmp));
    } else {
        ERRORLOG(("The calibration is failed due to Rx Gain calculation.\n"));
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to do the Rx Phase Calibration
*
* \param [in] prAdapter a pointer to the adapter handler
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCalRxPhase (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_8         temp8;
    UINT_32        u4tmp, result, loopcount;

    DEBUGFUNC("halRFCalRxPhase");

    //kalMdelay(30);
    HAL_BBCR_WR(prAdapter, 77, 0x0);
    //Do Rx phase calibration
    HAL_BBCR_WR(prAdapter, 77, 0x83C0);

    loopcount = 0;
    kalMdelay(1);
    /* wait result */
    do {
        //kalMdelay(30);
        HAL_BBCR_RD(prAdapter, 78, &u4tmp);
        temp8 = (UINT_8)u4tmp;
        if ((temp8 & 0x80) != 0) {
            result = 0;
            temp8 = temp8 & 0x7f;
            break;
        } else {
            loopcount ++;
            result = -1;
        }

    } while (loopcount < 2);

    if (result != 0) {
        ERRORLOG(("The calibration is failed due to Rx Phase step 1 calculation.\n"));
    }

    if (result == 0) {
        HAL_BBCR_RD(prAdapter, 81, &u4tmp);
        u4tmp &= 0x7f;
        u4tmp |= (temp8 << 8);
        HAL_BBCR_WR(prAdapter, 81, u4tmp);
        DBGLOG(PHY, TRACE, ("The calibrated RX Phase: (%d) 0x%04lx\n", temp8, u4tmp));
    } else {
        ERRORLOG(("The calibration is failed due to Rx Phase step 2 calculation.\n"));
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Calibrate the MT60105 2.4G Calibration
*
* \param prAdapter          a pointer to the adapter handler
*
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCal60105_2412_2484 (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 i;
    UINT_32 u4tmp;
    UINT_32 u4bbcr1, u4bbcr97, u4mcr98, u4bbcr100;
    UINT_32 u4cw12tmp, u4cw13tmp, u4cw23tmp;
    UINT_32 u4cw0tmp,u4cw22tmp;
    UINT_32 oldTxDacPwdMode = 0;

    DEBUGFUNC("halRFCal60105_2412_2484");

    DBGLOG(PHY, TRACE,("\n"));

    ASSERT(prAdapter);

    HAL_BBCR_WR(prAdapter, 80, 0x0000);
    HAL_BBCR_WR(prAdapter, 81, 0x0000);

    HAL_MCR_RD(prAdapter, MCR_CCR, &u4tmp);
    oldTxDacPwdMode = u4tmp;
    u4tmp &=  ~CCR_TXDAC_PWD_MODE_MASK;
    u4tmp |=  CCR_TXDAC_PWD_MODE_ON;
    HAL_MCR_WR(prAdapter, MCR_CCR, u4tmp);
    DBGLOG(PHY, TRACE,("CCR_TXDAC_PWD_MODE_ON\n"));

    for (i = 0; i < 3; i++) {
        kalUdelay(50);
    }

    //Before TX DC/gain/phase calibration
    halRFCrRD(prAdapter, 0x00, &u4cw0tmp);
    halRFCrRD(prAdapter, 0x0c, &u4cw12tmp);
    halRFCrRD(prAdapter, 0x0d, &u4cw13tmp);
    halRFCrRD(prAdapter, 0x16, &u4cw22tmp);
    halRFCrRD(prAdapter, 0x17, &u4cw23tmp);
    DBGLOG(PHY, TRACE,("CW0 is read as: 0x%lx\n", u4cw0tmp));
    DBGLOG(PHY, TRACE,("CW12 is read as: 0x%lx\n", u4cw12tmp));
    DBGLOG(PHY, TRACE,("CW13 is read as: 0x%lx\n", u4cw13tmp));
    DBGLOG(PHY, TRACE,("CW22 is read as: 0x%lx\n", u4cw22tmp));
    DBGLOG(PHY, TRACE,("CW23 is read as: 0x%lx\n", u4cw23tmp));

    HAL_BBCR_RD(prAdapter, 1, &u4bbcr1);
    HAL_BBCR_RD(prAdapter, 97, &u4bbcr97);
    HAL_BBCR_RD(prAdapter, 100, &u4bbcr100);
    HAL_MCR_RD(prAdapter, MCR_RFICR, &u4mcr98);

    /* power on calibration */
    HAL_MCR_RD(prAdapter, MCR_HLPCR, &u4tmp);
    u4tmp &= (~HLPCR_RF_SX_PD);
    u4tmp |= HLPCR_RF_SX_EN;
    HAL_MCR_WR(prAdapter, MCR_HLPCR, u4tmp);

    HAL_MCR_RD(prAdapter, MCR_CCR, &u4tmp);
    oldTxDacPwdMode = u4tmp;
    u4tmp &=  ~CCR_TXDAC_PWD_MODE_MASK;
    u4tmp |=  CCR_TXDAC_PWD_MODE_ON;
    HAL_MCR_WR(prAdapter, MCR_CCR, u4tmp);
    DBGLOG(PHY, TRACE,("CCR_TXDAC_PWD_MODE_ON\n"));

    for (i = 0; i < 3; i++) {
        kalUdelay(50);
    }

    halRFCalTxSet(prAdapter, 0);

    //SWAP RXIQ
    HAL_BBCR_RD(prAdapter, 1, &u4tmp);
    u4tmp |= BIT(15);
    HAL_BBCR_WR(prAdapter, 1, u4tmp);
    DBGLOG(PHY, TRACE,("BBCR_CR1 is written as: 0x%04lx\n", u4tmp));

    //Clear Compensation values
    HAL_BBCR_WR(prAdapter, 79, 0x0);
    HAL_BBCR_WR(prAdapter, 80, 0x0);
    HAL_BBCR_WR(prAdapter, 81, 0x0);


    //Do TX I-DC calibration
    halRFCalTxIDC(prAdapter);

    halRFCalTxSet(prAdapter, 0);

    //FORCE RXHP high
    HAL_BBCR_WR(prAdapter, 97, 0x0008);
    HAL_BBCR_WR(prAdapter, 98, 0x0080);

    //Do TX Q-DC calibration
    halRFCalTxQDC(prAdapter);

    HAL_BBCR_WR(prAdapter, 80, 0x0);
    HAL_BBCR_WR(prAdapter, 81, 0x0);

    for (i=0; i<2; i++) {

        halRFCalTxSet(prAdapter, 0);

        HAL_BBCR_WR(prAdapter, 1, 0x8631);
        DBGLOG(PHY, TRACE,("0x204 is written as: 0x%04x\n", 0x8631));

        //Do Tx gain calibration
        halRFCalTxGain(prAdapter);

        halRFCalTxSet(prAdapter, 0);

        //Do Tx Phase calibration
        halRFCalTxPhase(prAdapter);

    }

    //Do not Swap RXIQ
    HAL_BBCR_RD(prAdapter, 1, &u4tmp);
    u4tmp &= ~BIT(15);
    HAL_BBCR_WR(prAdapter, 1, u4tmp);
    DBGLOG(PHY, TRACE,("BBCR_CR1 is written as: 0x%04lx\n", u4tmp));

    kalMdelay(6);
    halRFCalRxSet(prAdapter, 0);

    halRFCalRxGain(prAdapter);

    halRFCalRxSet(prAdapter, 0);

    halRFCalRxPhase(prAdapter);

    kalMdelay(6);

    //Restore
    halRFCrWR(prAdapter, 0x00, u4cw0tmp);
    DBGLOG(PHY, TRACE, ("The CW0 store as 0x%08lx\n", u4cw0tmp));
    halRFCrWR(prAdapter, 0x0c, u4cw12tmp);
    DBGLOG(PHY, TRACE, ("The CW12 store as 0x%08lx\n", u4cw12tmp));
    halRFCrWR(prAdapter, 0x0d, u4cw13tmp);
    DBGLOG(PHY, TRACE, ("The CW13 store as 0x%08lx\n", u4cw13tmp));
    halRFCrWR(prAdapter, 0x16, u4cw22tmp);
    DBGLOG(PHY, TRACE, ("The CW22 store as 0x%08lx\n", u4cw22tmp));
    halRFCrWR(prAdapter, 0x17, u4cw23tmp);
    DBGLOG(PHY, TRACE, ("The CW23 store as 0x%08lx\n", u4cw23tmp));

    HAL_BBCR_WR(prAdapter, 1, u4bbcr1);
    HAL_BBCR_WR(prAdapter, 97, u4bbcr97);
    HAL_BBCR_WR(prAdapter, 100, u4bbcr100);

    HAL_MCR_WR(prAdapter, MCR_RFICR, u4mcr98);
    DBGLOG(PHY, TRACE, ("The RFICR store as 0x%08lx\n", u4mcr98));

    HAL_MCR_WR(prAdapter, MCR_CCR, oldTxDacPwdMode);
    DBGLOG(PHY, TRACE, ("The CCR store as 0x%08lx\n", oldTxDacPwdMode));

    /* back to normal operation bit5~2 0x0111 */
    halRFCrRD(prAdapter, 0x0, &u4tmp);
    u4tmp |= BITS(2,4);
    u4tmp &= ~BIT(5);
    u4tmp &= (~BIT(14));
    halRFCrWR(prAdapter, 0x00, u4tmp);
    DBGLOG(PHY, TRACE, ("The CW0 store as 0x%08lx\n", u4tmp));

    HAL_BBCR_RD(prAdapter, 77, &u4tmp);
    u4tmp&= ~BITS(9,14);
    HAL_BBCR_WR(prAdapter, 77, u4tmp);


}   /* halRFCal60105_2412_2484 */


/*----------------------------------------------------------------------------*/
/*!
* \brief Calibrate the MT60105 2.4G Calibration
*
* \param prAdapter          a pointer to the adapter handler
*
*
* \return N/A
*/
/*----------------------------------------------------------------------------*/
VOID
halRFCal60105_Post (
    IN P_ADAPTER_T prAdapter
    )
{
    UINT_32 u4tmp;

    DEBUGFUNC("halRFCal60105_Post");

    DBGLOG(PHY, TRACE,("\n"));

    /* back to normal operation bit5~2 0x0111 */
    halRFCrRD(prAdapter, 0x0, &u4tmp);
    u4tmp |= BITS(2,4);
    u4tmp &= ~BIT(5);
    u4tmp &= (~BIT(14));
    halRFCrWR(prAdapter, 0x00, u4tmp);
    DBGLOG(PHY, TRACE, ("The CW0 store as 0x%08lx\n", u4tmp));

}   /* halRFCal60105_2412_2484 */


/*----------------------------------------------------------------------------*/
/*!
* \brief Program RF by platform, because RF does not know how to write RICR, so
*        we pass the configuration to HAL layer and let it set the RF.
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[in] pu4SynthProgWords the word needs to be set in RF
* \param[in] u4NumWords number of words to be set
*
* \return N/A
*
*/
/*----------------------------------------------------------------------------*/
VOID
halRFSetProg (
    IN P_ADAPTER_T prAdapter,
    IN PUINT_32    pu4SynthProgWords,
    IN UINT_32     u4NumWords
    )
{
    UINT_32 temp32_1, temp32_2, i;
    BOOLEAN fgStatus = FALSE;

    DEBUGFUNC("halRFSetProg");

    ASSERT(prAdapter);
    ASSERT(pu4SynthProgWords);
    
    /* Program the synthesizer. */
    for (i = 0; i < u4NumWords; i++) {
        DBGLOG(PHY, TRACE, ("Channel code: 0x%lx\n", pu4SynthProgWords[i]));

        /* read the CW */
        temp32_1 = pu4SynthProgWords[i];
        temp32_2 = pu4SynthProgWords[i];

        HAL_MCR_WR(prAdapter, MCR_RSDR, ((temp32_1 & (~BIT(18))) | 0x40000000));
        HAL_MCR_RD_AND_WAIT(prAdapter, MCR_RSDR, &temp32_1,
            (temp32_1 & RSDR_SYNT_PROG_START) == 0, 2, 5, fgStatus);
        ASSERT(fgStatus);

        /* Write the CW with specified code */
         switch (i) {
            case 0:
                temp32_1 = ((temp32_1 & BITS(0, 17)) & (~(BITS(4, 11) | BITS(0, 1)))) | pu4SynthProgWords[i];
                break;
            case 1:
                temp32_1 = pu4SynthProgWords[i];
                break;
            case 2:
                temp32_1 = ((temp32_1 & BITS(0, 17)) & (~(BIT(14) | BITS(0, 10)))) | pu4SynthProgWords[i];
                break;
        }


       HAL_MCR_WR_AND_WAIT(prAdapter, MCR_RSDR, temp32_1,
            RSDR_SYNT_PROG_START, 2, 5, fgStatus);

       ASSERT(fgStatus);
    }
}



/*----------------------------------------------------------------------------*/
/*!
* \brief Program RF by platform, get the channel table by input channel number and band.
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[in] ucChannelNum the channel number to query
* \param[in] eBand the band to query
*
* \return The Channel table entry
*
*/
/*----------------------------------------------------------------------------*/
P_RF_CHANNEL_PROG_ENTRY
halRFGetRFChnlProgEntry (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8      ucChannelNum,
    IN ENUM_BAND_T eBand
    )
{
    UINT_32 u4Idx = 0;
    BOOLEAN fgFound = FALSE;

    for(u4Idx = 0; u4Idx < sizeof(arRFChannelTableForA60105)/sizeof(RF_CHANNEL_PROG_ENTRY); u4Idx++) {
        if ( ucChannelNum == arRFChannelTableForA60105[u4Idx].ucChannelNum &&
            arRFChannelTableForA60105[u4Idx].eBand == eBand ){
            fgFound = TRUE;
            break;
        }
    }

    if (fgFound) {
        return (P_RF_CHANNEL_PROG_ENTRY)&arRFChannelTableForA60105[u4Idx];
    } 
    else {
        return NULL;
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Do RF switch channel, call this function while driver not yet enter low power
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[in] ucChannelNum The channel to switch
* \param[in] eBand The band to switch

* \return The channel and band can accept to switch or not
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
halRFSwitchChannel (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8      ucChannelNum,
    IN ENUM_BAND_T eBand
    )
{
    P_RF_CHANNEL_PROG_ENTRY prRfChnlProgEntry;

    DEBUGFUNC("halRFSwitchChannel");

    ASSERT(prAdapter);

    if ((prRfChnlProgEntry = halRFGetRFChnlProgEntry(prAdapter, ucChannelNum, eBand)) != NULL) {
        DBGLOG(HAL, TRACE, ("ch=%d (%lu) 0x%08lx 0x%08lx 0x%08lx\n",
            ucChannelNum,
            prRfChnlProgEntry->u4NumSynthProgWords,
            prRfChnlProgEntry->au4SynthProgWords[0],
            prRfChnlProgEntry->au4SynthProgWords[1],
            prRfChnlProgEntry->au4SynthProgWords[2]));
        halRFSetProg(prAdapter,
                     prRfChnlProgEntry->au4SynthProgWords,
                     prRfChnlProgEntry->u4NumSynthProgWords);

        return WLAN_STATUS_SUCCESS;
    } 
    else {
        return WLAN_STATUS_NOT_ACCEPTED;
    }

}


/*----------------------------------------------------------------------------*/
/*!
* \brief Do RF switch channel at low power instruction, call this function while driver
*          make scan at low power
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[in] ucChannelNum The channel to switch
* \param[in] eBand The band to switch

* \return The channel and band can accept to switch or not
*
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
halSetRFSwitchChnlInst (
    IN P_ADAPTER_T prAdapter,
    IN UINT_8      ucChannelNum,
    IN ENUM_BAND_T eBand
    )
{
    P_RF_CHANNEL_PROG_ENTRY prChProgEntry;
    UINT_32 i;

    DEBUGFUNC("halSetRFSwitchChnlInst");

    ASSERT(prAdapter);

    if ((prChProgEntry = halRFGetRFChnlProgEntry(prAdapter, ucChannelNum, eBand)) != NULL) {
        DBGLOG(HAL, TRACE, ("ch=%d 0x%08lx 0x%08lx 0x%08lx\n",
            ucChannelNum,
            prChProgEntry->au4SynthProgWords[0],
            prChProgEntry->au4SynthProgWords[1],
            prChProgEntry->au4SynthProgWords[2]));
        /* Program the synthesizer. */
        for (i = 0; i < prChProgEntry->u4NumSynthProgWords; i++) {
            HAL_HW_SCAN_SET_INST_RFCR_WR(prAdapter, prChProgEntry->au4SynthProgWords[i]);
        }
        return WLAN_STATUS_SUCCESS;
    } 
    else {
        return WLAN_STATUS_NOT_ACCEPTED;
    }

}


/*----------------------------------------------------------------------------*/
/*!
* \brief To identity the RF type.
*
* \param[in] prAdapter pointer to the Adapter handler
*
* \return The RF type
*
*/
/*----------------------------------------------------------------------------*/
ENUM_RF_TYPE_T
halGetRFType (
    IN P_ADAPTER_T prAdapter
    )
{
    return RF_TYPE_MTK60105;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Program RF by platform, get the channel table by input channel frequency.
*
* \param[in] prAdapter pointer to the Adapter handler
* \param[in] u4ChannelFreq the channel frequency to query
*
* \return The Channel table entry
*
*/
/*----------------------------------------------------------------------------*/
P_RF_CHANNEL_PROG_ENTRY
halRFGetRFChnlProgEntryFromChannelFreq (
    IN P_ADAPTER_T prAdapter,
    IN UINT_32     u4ChannelFreq
    )
{
    UINT_32 u4Idx = 0;
    BOOLEAN fgFound = FALSE;

    DEBUGFUNC("nicGetChannelBandFromFreq");

    ASSERT(prAdapter);

    for(u4Idx = 0; u4Idx < sizeof(arRFChannelTableForA60105)/sizeof(RF_CHANNEL_PROG_ENTRY); u4Idx++) {
        if ( u4ChannelFreq == arRFChannelTableForA60105[u4Idx].u4ChannelFreq  ){
            fgFound = TRUE;
            break;
        }

    }

    if (fgFound) {
        return (P_RF_CHANNEL_PROG_ENTRY)&arRFChannelTableForA60105[u4Idx];
    } 
    else {
        return NULL;
    }
}


/*----------------------------------------------------------------------------*/
/*!
* \brief Apply different temperature setting for A60105RF
*
* \param prAdapter          Pointer to the Adapter structure
* \param rState             Current Temperature state
*
* \return -
*/
/*----------------------------------------------------------------------------*/
VOID
halRFAdoptTempChange (
    IN P_ADAPTER_T          prAdapter,
    IN ENUM_THERMO_STATE_T  rState
    )
{
     DEBUGFUNC("halRFAdoptTempChange");
}

