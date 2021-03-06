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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/rx.c#2 $
*/

/*! \file   "rx.c"
    \brief  The functions related to the 802.11 rx protocol

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
** $Log: rx.c $
 *
 * 11 08 2010 enlai.chu
 * [ALPS00132010] [Regression][Bluetooth] Cannot turn BT on any more
 * GPIO1 need set to input mode for daisychain
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\58 2009-07-09 18:55:55 GMT mtk01088
**  move the rx wpi code to wpi.c
**  \main\maintrunk.MT5921\57 2009-07-08 14:54:22 GMT mtk01088
**  rename the wapi variable to mtk nameing style
**  \main\maintrunk.MT5921\56 2009-07-06 21:40:17 GMT mtk01088
**  fixed the compiling error at linux
**  \main\maintrunk.MT5921\55 2009-07-06 20:36:33 GMT mtk01088
**  adding the code for processing rx wpi pakcet, doing the sms4 decrypt and mic check
**  also fixed the rx header translation A3 issue
**  \main\maintrunk.MT5921\54 2009-06-11 11:26:42 GMT mtk01088
**  rename the compiling flag
**  \main\maintrunk.MT5921\53 2009-06-11 11:16:58 GMT mtk01088
**  Adding the woraround code to fixed the conexant WPS AP issue
**  \main\maintrunk.MT5921\52 2009-02-07 14:42:02 GMT mtk01088
**  mark non-used code for linux wps support
**  \main\maintrunk.MT5921\51 2009-01-05 10:08:03 GMT mtk01725
**  Change compiling flag.
**  \main\maintrunk.MT5921\50 2008-11-28 15:22:25 GMT mtk01088
**  fixed lint warning
**  \main\maintrunk.MT5921\49 2008-09-12 11:24:49 GMT mtk01461
**  Refine code - Add CFG_TX_FRAGMENT
**  \main\maintrunk.MT5921\48 2008-09-10 14:02:23 GMT mtk01088
**  Only break for data frame, not assert for data frame
**  \main\maintrunk.MT5921\47 2008-08-21 00:45:48 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\46 2008-08-12 09:57:44 GMT mtk01461
**  \main\maintrunk.MT5921\45 2008-05-30 20:28:44 GMT mtk01461
**  Rename KAL function
**  \main\maintrunk.MT5921\44 2008-05-28 14:40:55 GMT mtk01088
**  adjust the frame length for decrement the TKIP MIC filed
**  \main\maintrunk.MT5921\43 2008-05-20 13:21:04 GMT mtk01084
**  update RCPI variance check under SLT
**  \main\maintrunk.MT5921\42 2008-05-16 10:39:42 GMT mtk01461
**  Add rxUpdateRssi() for RSSI OID
**  \main\maintrunk.MT5921\41 2008-05-03 20:31:30 GMT mtk01461
**  Update RSSI during RX data frame for OID Query RSSI
**  \main\maintrunk.MT5921\40 2008-04-30 14:18:56 GMT mtk01088
**  not check the non-data frame for rsn
**  \main\maintrunk.MT5921\39 2008-04-23 14:14:29 GMT mtk01461
**  Select the lowest rate from desired rate set for error handling
**  \main\maintrunk.MT5921\38 2008-04-17 23:06:29 GMT mtk01461
**  Fix compile warnning
**  \main\maintrunk.MT5921\37 2008-04-07 22:17:57 GMT mtk01084
**  use RCPI_MEASURE index for printing debug message under RCPI_MEASURE
**  \main\maintrunk.MT5921\36 2008-04-02 20:44:07 GMT mtk01084
**  Support for RCPI variance histogram
**  \main\maintrunk.MT5921\35 2008-03-31 10:24:49 GMT mtk01461
**  Fix sync code problem
**  \main\maintrunk.MT5921\34 2008-03-31 10:05:37 GMT mtk01461
**  Add check class error and send disassoc/deauth frame
**  \main\maintrunk.MT5921\33 2008-03-26 09:16:23 GMT mtk01461
**  Fix Rx defragment problem(lost sync with correct version)
**  \main\maintrunk.MT5921\32 2008-03-23 20:37:20 GMT mtk01461
**  Fix - a STA_RECORD_T should be add only once while RX data from an unknown peer
**  \main\maintrunk.MT5921\31 2008-03-19 15:21:58 GMT mtk01461
**  Fix RX defragment for QoS and boundary case
**  \main\maintrunk.MT5921\30 2008-03-13 15:31:59 GMT mtk01461
**  Refine the relationship between SCAN result and STA record, lifetime, aging policy etc
**  \main\maintrunk.MT5921\29 2008-02-29 15:26:55 GMT mtk01088
**  add rsn port control check at rx path
**  \main\maintrunk.MT5921\28 2008-02-27 12:12:35 GMT mtk01461
**  Let MGMT frame can also pass the duplicate removal filter
**  \main\maintrunk.MT5921\27 2008-02-26 12:13:38 GMT mtk01084
**  fix RX duplicate filter handling issue
**  \main\maintrunk.MT5921\26 2008-02-21 15:01:42 GMT mtk01461
**  Add initial rate according rx signal quality support
**  \main\maintrunk.MT5921\25 2008-02-01 10:01:37 GMT mtk01385
**  1. Fix WinCE 4.2 compiling error.
**  \main\maintrunk.MT5921\24 2008-01-24 15:00:49 GMT mtk01461
**  Fix Duplicate Filter may drop incoming frame unexpectedly
**  \main\maintrunk.MT5921\23 2008-01-24 12:44:15 GMT mtk01088
**  do SW BSSID check for HW info the BSSID not matched case
**  \main\maintrunk.MT5921\22 2008-01-07 15:06:49 GMT mtk01461
**  Add PhyType & AdHocMode Selection Support
**  \main\maintrunk.MT5921\21 2007-12-11 00:10:17 GMT mtk01461
**  Update MGMT process function array
**  \main\maintrunk.MT5921\20 2007-11-30 16:46:27 GMT mtk01425
**  1. Refine Rx path
**  \main\maintrunk.MT5921\19 2007-11-29 02:05:58 GMT mtk01461
**  Fix Windows RX multiple packet retain problem
**  \main\maintrunk.MT5921\18 2007-11-15 16:23:22 GMT mtk01425
**  1. Fix software rx header translation when receiving QoS Fragment packets
**  \main\maintrunk.MT5921\17 2007-11-13 18:18:56 GMT mtk01084
**  modify function name to process beacon and probe response
**  \main\maintrunk.MT5921\16 2007-11-09 17:32:08 GMT mtk01425
**  1. Fix 802.3 packet validation
**  \main\maintrunk.MT5921\15 2007-11-07 18:36:50 GMT mtk01461
**  Update Macro Source
**
**  \main\maintrunk.MT5921\14 2007-11-06 20:24:16 GMT mtk01088
**  add the WPS code, indicate mgmt frame to upper layer
**  \main\maintrunk.MT5921\13 2007-11-02 00:57:17 GMT mtk01461
**  Unify TX Path for Normal and IBSS Power Save + IBSS neighbor learning
** Revision 1.3  2007/07/17 12:59:22  MTK01088
** add the rx sec check
**
** Revision 1.2  2007/06/27 02:14:00  MTK01461
** Update SCAN_FSM, Initial(Can Load Module), Proc(Can do Reg R/W), TX API
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

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/
static PROCESS_RX_MGT_FUNCTION apfnProcessRxMgtFrame[MAX_NUM_OF_FC_SUBTYPES] = {
    NULL,                           /* subtype 0000: Association request */
    arbFsmRunEventJoinRxAuthAssoc,  /* subtype 0001: Association response */
    NULL,                           /* subtype 0010: Reassociation request */
    arbFsmRunEventJoinRxAuthAssoc,  /* subtype 0011: Reassociation response */
    arbFsmRunEventProcessProbeReq,  /* subtype 0100: Probe request */
    scanProcessBeaconAndProbeResp,  /* subtype 0101: Probe response */
    NULL,                           /* subtype 0110: reserved */
    NULL,                           /* subtype 0111: reserved */
    scanProcessBeaconAndProbeResp,  /* subtype 1000: Beacon */
    NULL,                           /* subtype 1001: ATIM */
    arbFsmRunEventProcessDisassoc,  /* subtype 1010: Disassociation */
    arbFsmRunEventJoinRxAuthAssoc,  /* subtype 1011: Authentication */
    arbFsmRunEventProcessDeauth,    /* subtype 1100: Deauthentication */
    NULL,                           /* subtype 1101: Action */
    NULL,                           /* subtype 1110: reserved */
    NULL                            /* subtype 1111: reserved */
};

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

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
/*----------------------------------------------------------------------------*/
/*!
* \brief rxProcessMSDU() is used to process MSDU integrity as defined in the 802.11
*        spec: TKIP MIC, CCMP MIC, BIP.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prSWRfb        Pointer to the RFB which is being processed.
*
* \retval WLAN_STATUS_SUCCESS           Process Data MSDU ok, Not Data MSDU
* \retval WLAN_STATUS_FAILURE           Drop this MSDU
* \retval WLAN_STATUS_INVALID_LENGTH    Drop this MSDU
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rxProcessMSDU (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    )
{
    P_RX_CTRL_T prRxCtrl;
    P_RX_STATUS_T prRxStatus;
    UINT_16 u2ResultFrameBodyLen;
    WLAN_STATUS u4Status = WLAN_STATUS_SUCCESS;


    ASSERT(prAdapter);
    ASSERT(prSWRfb);

    prRxCtrl = &prAdapter->rRxCtrl;
    prRxStatus = prSWRfb->prRxStatus;

    if (prSWRfb->fgIsDataFrame == FALSE) {
        return WLAN_STATUS_SUCCESS;
    }

    //4 <1> Port Control Check
    if (rsnRxProcessMSDU(prAdapter, prSWRfb) == FALSE) {
        return WLAN_STATUS_FAILURE;
    }

    //4 <2> RSC check
    //4 <3> check TKIP MIC error and do countermeasure
    do {
        if (tkipMicDecapsulate(prAdapter,
                               prSWRfb,
                               &u2ResultFrameBodyLen) == FALSE) {
            prRxStatus->u2StatusFlag |= RX_STATUS_FLAG_TKIPMIC_ERROR;
        }
        else {
            prSWRfb->u2FrameLength = u2ResultFrameBodyLen;
        }

        if (RX_STATUS_IS_TKIP_MIC_ERROR(prRxStatus->u2StatusFlag)) {
            //4 do countermeasure
            rsnTkipHandleMICFailure(prAdapter,
                (prRxStatus->u2StatusFlag & RX_STATUS_FLAG_BMCAST) != 0 ? TRUE : FALSE);

            RX_INC_CNT(prRxCtrl, RX_TKIP_ERR_DROP_COUNT);

            u4Status = WLAN_STATUS_FAILURE;
            break;
        }

        /* NOTE: 802.11 NULL/QoS NULL can pass following check */
        if (!prSWRfb->fgIs8023 &&
            (prSWRfb->u2FrameLength < WLAN_MAC_HEADER_LEN)) {
            u4Status = WLAN_STATUS_INVALID_LENGTH;
            break;
        }
    } while (FALSE);

    return u4Status;

} /* end of rxProcessMSDU() */


/*----------------------------------------------------------------------------*/
/*!
* \brief rxProcessMPDU() is used to process MPDU as defined in the 802.11 spec:
*        duplicated frame checking, decryption and defragmentation.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in, out] pprSWRfb  Address of the Pointer to the RFB which is being processed.
*
* \retval WLAN_STATUS_INVALID_DATA  Duplicated, Class Error, Out of BSSID.
* \retval WLAN_STATUS_FAILURE       Null frame, MPDU Decryption Error, Defragmenting.
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rxProcessMPDU (
    IN P_ADAPTER_T prAdapter,
    IN OUT PP_SW_RFB_T pprSWRfb
    )
{
    P_SW_RFB_T prSWRfb;
    P_STA_RECORD_T prStaRec;
    WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("rxProcessMPDU");


    ASSERT(prAdapter);
    ASSERT(pprSWRfb);
    prSWRfb = *pprSWRfb;
    prStaRec = prSWRfb->prStaRec;

    do {
        //4 <1> Duplicate Removal
        if (rxIsDuplicateFrame(prAdapter, prSWRfb)) {
            DBGLOG(RX, TRACE, ("RX duplicate frame check failed\n"));
            rStatus = WLAN_STATUS_INVALID_DATA;
            break;
        }

        //4 <2> Class Error Removal
        if (rxFilterRecvPacket(prAdapter, prSWRfb) != WLAN_STATUS_SUCCESS) {
            DBGLOG(RX, TRACE, ("RX filter frame failed\n"));
            rStatus = WLAN_STATUS_INVALID_DATA;
            break;
        }

        //4 <3> Different BSSID Removal
        /* TODO(Kevin): We should recheck this part if support "BT over Wi-Fi".
         */
        if (prSWRfb->fgIsDataFrame &&
            !NIC_RFB_BSSID_MATCHED(prSWRfb)) {
            /* If the packet is following the association response,
               the HW BSSID is not update, thus the NIC_RFB_BSSID_MATCHED
               will set, for this case, do the TA address check,
               pass the check for BSSID */
            if ((prStaRec == NULL) ||
                (UNEQUAL_MAC_ADDR(prStaRec->aucMacAddr, prAdapter->rBssInfo.aucBSSID))) {
                /* NOTE: Here we only consider the Infrastructure Case.
                 * For IBSS, the prStaRec->aucMacAddr will always not equal to BSSID.
                 * But because we'll send beacon first before
                 */

                rStatus = WLAN_STATUS_INVALID_DATA;
                break;
            }
        }

        //4 <4> Null Frame Removal
        if (prSWRfb->fgIsNullData) {
            rStatus = WLAN_STATUS_FAILURE;
            break;
        }

        //4 <5> Security check
        if (rxProcessMPDUSecurity(prAdapter, prSWRfb)){
            rStatus= WLAN_STATUS_FAILURE;
            break;
        }

        //4 <6> Defragment
        if (prStaRec) {
            prSWRfb = rxDefragMPDU(prAdapter, prSWRfb);
            *pprSWRfb = prSWRfb;
        }
    } while (FALSE);

    if (!prSWRfb) {
        rStatus = WLAN_STATUS_FAILURE;
    }

    return rStatus;

} /* end of rxProcessMPDU() */


#if 0 //SUPPORT_WPS //Not used at linux supplicant v0.6.7
/*----------------------------------------------------------------------------*/
/*!
* \brief rxIndicateMgt() is used to dispatch the incoming management frame to the
*        appropriate application
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prSWRfb        Pointer to the RFB which is being processed.
* \param[in] ucFrameType    The frame type of management frame.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rxIndicateMgt (
    IN P_ADAPTER_T  prAdapter,
    IN P_SW_RFB_T   prSWRfb,
    IN UINT_8       ucFrameType,
    )
{
   UINT_8 ucFilterType = 0;


   ASSERT(prAdapter);
   ASSERT(prSWRfb);


   switch (ucFrameType) {
   case MAC_FRAME_BEACON:
       ucFilterType = IEEE80211_FILTER_TYPE_BEACON;
       break;

   case MAC_FRAME_PROBE_REQ:
       ucFilterType = IEEE80211_FILTER_TYPE_PROBE_REQ;
       break;

   case MAC_FRAME_PROBE_RSP:
       ucFilterType = IEEE80211_FILTER_TYPE_PROBE_RESP;
       break;

   case MAC_FRAME_ASSOC_REQ: /* Pass through */
   case MAC_FRAME_REASSOC_REQ:
       ucFilterType = IEEE80211_FILTER_TYPE_ASSOC_REQ;
       break;

   case MAC_FRAME_ASSOC_RSP: /* Pass through */
   case MAC_FRAME_REASSOC_RSP:
       ucFilterType = IEEE80211_FILTER_TYPE_ASSOC_RESP;
       break;

   case MAC_FRAME_AUTH:
       ucFilterType = IEEE80211_FILTER_TYPE_AUTH;
       break;

   case MAC_FRAME_DEAUTH:
       ucFilterType = IEEE80211_FILTER_TYPE_DEAUTH;
       break;

   case MAC_FRAME_DISASSOC:
       ucFilterType = IEEE80211_FILTER_TYPE_DISASSOC;
       break;

   default:
       break;
   }

   if (ucFilterType) {
       kalRxIndicateMgt(prAdapter->prGlueInfo, ucFilterType, prSWRfb->pvPacket);
    }

   return WLAN_STATUS_SUCCESS;

} /* end of rxIndicateMgt() */
#endif /* SUPPORT_WPS */


/*----------------------------------------------------------------------------*/
/*!
* \brief rxProcessMgmtFrame() is used to check the format of the management frame,
*        and put them into the mapping management-processing functions.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prSWRfb        Pointer to the RFB which is being processed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA  Not management frame
* \retval WLAN_STATUS_NOT_SUPPORTED No corresponding management handler
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rxProcessMgmtFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    )
{
    P_WLAN_MAC_HEADER_T prWLANHdr;
    UINT_8 ucMgmtFrameSubType = 0;
    WLAN_STATUS u4Status = WLAN_STATUS_SUCCESS;

    DEBUGFUNC("rxProcessMgmtFrame");


    ASSERT(prAdapter);
    ASSERT(prSWRfb);
    prWLANHdr = (P_WLAN_MAC_HEADER_T)prSWRfb->pvHeader;

    //DBGLOG(RX, TRACE, ("rxProcessMgmtFrame(%#x)\n", prSWRfb));

    do {
        if (prSWRfb->fgIsDataFrame) {
            break;
        }

        //4 2007/06/22, mike, Check FromDS and ToDS bits, they should not be asserted
        if (prWLANHdr->u2FrameCtrl & MASK_TO_DS_FROM_DS) {
            u4Status = WLAN_STATUS_INVALID_DATA;
            DBGLOG(RX, TRACE, ("Invalide FromDS and ToDS are 1s\n"));
            break;
        }

        ucMgmtFrameSubType = (UINT_8)
            ((prWLANHdr->u2FrameCtrl & MASK_FC_SUBTYPE) >> OFFSET_OF_FC_SUBTYPE);

        if (apfnProcessRxMgtFrame[ucMgmtFrameSubType] == NULL) {
            DBGLOG(RX, TRACE, ("Unsupported management frame type: %#x\n", ucMgmtFrameSubType));
            u4Status = WLAN_STATUS_NOT_SUPPORTED;
            break;
        }
        apfnProcessRxMgtFrame[ucMgmtFrameSubType](prAdapter, prSWRfb);

#if 0 //SUPPORT_WPS //Not used at linux supplicant v0.6.7
        if (prAdapter->fgIndMgt) {
            BOOLEAN fgIsRetained = TRUE;

            if (kalProcessRxPacket(prAdapter->prGlueInfo,
                                   prSWRfb->pvPacket,
                                   (PUINT_8)prSWRfb->pvHeader,
                                   (UINT_32)prSWRfb->u2FrameLength,
                                   &fgIsRetained,
                                   CSUM_RES_NONE) != WLAN_STATUS_SUCCESS) {
                DBGLOG(NIC, ERROR, ("kalProcessRxPacket return value != WLAN_STATUS_SUCCESS\n"));
                ASSERT(0);
            }
            else {
                rxIndicateMgt(prAdapter,
                              prSWRfb,
                              (UINT_8)(prWLANHdr->u2FrameCtrl & MASK_FRAME_TYPE));
            }
        }
#endif /* SUPPORT_WPS */

    }
    while (FALSE);

    return u4Status;

} /* end of rxProcessMgmtFrame() */


#if SUPPORT_CR1809_WPS_AP_WORKAROUND
UINT_8      ucIdentifier;
#endif

/*----------------------------------------------------------------------------*/
/*!
* \brief rxProcessDataFrame() is used to process data frame do header translation
*        and checksum offload for defragmented MSDU.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prSWRfb        Pointer to the RFB which is being processed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE Header translation fail
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rxProcessDataFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    )
{
    P_STA_RECORD_T prStaRec;
    PUINT_8 pucSrcAddr;

    DEBUGFUNC("rxProcessDataFrame");


    ASSERT(prAdapter);
    ASSERT(prSWRfb);
    pucSrcAddr = NIC_RFB_GET_TA(prSWRfb);

    DBGLOG(RX, TRACE, ("rxProcessDataFrame(%#lx)\n", (UINT_32)prSWRfb));

    //4 <1> <todo>Update counters

    //4 <2> Indicate packet to upper layer
    /* TODO(Kevin): better to place it before duplicate filter & defragment */
    if ((prAdapter->eCurrentOPMode == OP_MODE_IBSS) &&
        (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED)) {
        P_BSS_INFO_T prBssInfo = &prAdapter->rBssInfo;
        P_CONNECTION_SETTINGS_T prConnSettings = &prAdapter->rConnSettings;
        UINT_16 u2DesiredRateSet;


        /* Get or Add a Station Record by TA for this IBSS PEER */
        prStaRec = staRecGetStaRecordByAddr(prAdapter, pucSrcAddr);

        /* Add a new entry */
        if (!prStaRec) {

            /* Get or Add a Station Record by TA for this IBSS PEER */
            prStaRec = staRecGetStaRecordByAddrOrAddIfNotExist(prAdapter, pucSrcAddr);

            /* **NOTE(Kevin): This is not the default entry(BSSID), we won't use STATE_3 to
             * let it can be cleaned up by aging func.
             */

            /* Update received RCPI */
            prStaRec->rRcpi = NIC_RFB_GET_RCPI(prSWRfb);

            /* Update the record activity time. */
            GET_CURRENT_SYSTIME(&prStaRec->rUpdateTime);


            //4 Desired Rate Set
            u2DesiredRateSet = (prConnSettings->u2DesiredRateSet &
                                    prBssInfo->u2OperationalRateSet);
            if (u2DesiredRateSet) {
                prStaRec->u2DesiredRateSet = u2DesiredRateSet;
            }
            else {
                /* For Error Handling - The Desired Rate Set is not covered in Operational Rate Set. */
                prStaRec->u2DesiredRateSet = prBssInfo->u2OperationalRateSet;
            }

            /* Try to set the best initial rate for this entry */
            if (!rateGetBestInitialRateIndex(prStaRec->u2DesiredRateSet,
                                             prStaRec->rRcpi,
                                             &prStaRec->ucCurrRate1Index)) {

                if (!rateGetLowestRateIndexFromRateSet(prStaRec->u2DesiredRateSet,
                                                       &prStaRec->ucCurrRate1Index)) {
                    ASSERT(0);
                }
            }

            DBGLOG(MGT, TRACE, ("Initial Rate Index for entry ["MACSTR"] = %d\n",
                MAC2STR(prStaRec->aucMacAddr), prStaRec->ucCurrRate1Index));

            //4 Preamble Mode
            prStaRec->fgIsShortPreambleOptionEnable =
                prBssInfo->fgUseShortPreamble;

            //4 QoS Flag
            prStaRec->fgIsQoS = prBssInfo->fgIsWmmAssoc;

            //4 Update WLAN Table.
            if (nicSetHwBySta(prAdapter, prStaRec) == FALSE) {
                ASSERT(FALSE);
            }

            //4 Update Desired Rate Set for BT.
#if CFG_TX_FRAGMENT
            if (prConnSettings->fgIsEnableTxAutoFragmentForBT) {
                txRateSetInitForBT(prAdapter, prStaRec);
            }
#endif /* CFG_TX_FRAGMENT */

        }
        else {

            /* Update the record activity time. */
            GET_CURRENT_SYSTIME(&prStaRec->rUpdateTime);

            /* TODO(Kevin): Should we update paramenters here ? */
        }
    }

    /* It is not a 802.3 frame, do software header translation */
    if (!prSWRfb->fgIs8023) {
        if (rxWlanHeaderTranslation(prAdapter, prSWRfb)) {
            return WLAN_STATUS_FAILURE;
        }
    }

#if CFG_TCP_IP_CHKSUM_OFFLOAD
    if (prAdapter->u4CSUMFlags && prSWRfb->fgFragmented) {
        utilRxComputeCSUM(prSWRfb->pvHeader, prSWRfb->u2FrameLength, prSWRfb->aeCSUM);
    }
    nicRxUpdateCSUMStatistics(prAdapter, prSWRfb->aeCSUM);
#endif

#if SUPPORT_CR1809_WPS_AP_WORKAROUND
    if (RX_STATUS_IS_1X(prSWRfb->prRxStatus->u2StatusFlag))  {

        PUINT_8 cp = (PUINT_8)prSWRfb->pvHeader;
        if (prSWRfb->u2FrameLength == 23 /* EAP-Request : Identity packet length */) { 
            ucIdentifier = cp[19];
        }
        else if (prSWRfb->u2FrameLength == 32 /* The EAP-Request WPS-Start */ &&
                 cp[22] == 0xfe /* EAP-WPS Type */ && 
                 cp[19] == ucIdentifier /* The same identifier */) {
            cp[19] = ucIdentifier + 1;
        }
    }
#endif
    DBGLOG_MEM8(RX, TRACE, (PUINT_32)prSWRfb->prRxStatus,
        DWORD_TO_BYTE((prSWRfb->prRxStatus->u2OverallBufferLengthDW & RX_STATUS_BUFFER_LENGTH_MASK) - 1));

    //dumpMemory32((PUINT_32)prSWRfb->prRxStatus, (prSWRfb->prRxStatus->u2OverallBufferLength &0x3ff)*4);

    return WLAN_STATUS_SUCCESS;

} /* end of rxProcessDataFrame() */


/*----------------------------------------------------------------------------*/
/*!
* \brief rxFilterRecvPacket() is used to filter the received packets such as class error.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prSWRfb        Pointer to the RFB which is being processed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE Class Error Frames.
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rxFilterRecvPacket (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    )
{
    P_BSS_INFO_T prBssInfo;
    P_STA_RECORD_T prStaRec;
    WLAN_STATUS u4Status = WLAN_STATUS_SUCCESS;


    ASSERT(prAdapter);
    ASSERT(prSWRfb);
    prBssInfo = &prAdapter->rBssInfo;
    prStaRec = prSWRfb->prStaRec;

    if (prAdapter->eCurrentOPMode == OP_MODE_INFRASTRUCTURE) {
        if (prSWRfb->fgIsDataFrame && prStaRec) {

            /* NOTE(Kevin 2008/03/30):
             * For the Beacon Timeout case:
             *        First we'll set the ucStaState to STA_STATE_1, and we'll try to
             *    search and connect to an AP asap. During this period if we still
             *    get data from previous AP(or in RX FIFO), we'll reply Deauth with
             *    Class Error Code.
             *        If we try to join the same AP, but send Deauth at the later
             *    time. This may lead to an ambiguous situation if we are in JOIN
             *    STATE.
             *        In JOIN STATE, we send MGMT frames in AC4. So if we send the
             *    Deauth in AC3, we may send Deauth frame after re-connect to AP.
             *    And cause unreasonable disconnection.
             *        If we send Deauth in AC4, then we need add additional parameter
             *    for arbFsmRunEventJoinRxClassError().
             *        Thus we'll check additionally if the STA's MAC Address is
             *    equal to current BSSID at the same time. If not match, then we'll
             *    send Deauth to it without harm to curren BSS. If match, then we won't
             *    send Deauth, because most of situation means we lost it accidentally,
             *    let JOIN FSM to handle.
             *        If the frame passed the Class Check, it will also be checked
             *    with the eConnectionStateIndicated flag later.
             */
            if ((prStaRec->ucStaState != STA_STATE_3) &&
                (UNEQUAL_MAC_ADDR(prStaRec->aucMacAddr, prBssInfo->aucBSSID))) {

                arbFsmRunEventJoinRxClassError(prAdapter, prStaRec);

                u4Status = WLAN_STATUS_FAILURE;
            }
        }
    }

    return u4Status;

} /* end of rxFilterRecvPacket() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function checks if the received packet is a duplicated one.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prSWRfb        The RFB which is being processed.
*
* \retval TRUE  the packet is duplicated
* \retval FALSE the packets is not duplicated
*/
/*----------------------------------------------------------------------------*/
BOOLEAN
rxIsDuplicateFrame (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    )
{
    P_RX_CTRL_T prRxCtrl;
    P_STA_RECORD_T prStaRec;
    BOOLEAN fgIsDuplicatedFrame = FALSE;

    DEBUGFUNC("rxIsDuplicateFrame");

    ASSERT(prAdapter);
    ASSERT(prSWRfb);
    prRxCtrl = &prAdapter->rRxCtrl;
    prStaRec = prSWRfb->prStaRec;

    if (prStaRec) {
        if (NIC_RFB_IS_QOS(prSWRfb)) {
            if (NIC_RFB_IS_RETRY(prSWRfb) &&
                (prStaRec->u2TIDLastRxSeqCtrl[prSWRfb->ucQosTID] ==
                 NIC_RFB_GET_SEQCTRL(prSWRfb))) {

                //4 20060821, mikewu, <todo>  Duplicated frame found, update MIB counter (what counter)
                //DBGLOG(MIKE, TRACE, ("MacAddr: "MACSTR", Seq = %d\n",
                    //MAC2STR(prStaRec->aucMacAddr), NIC_RFB_GET_SEQCTRL(prSWRfb) >> 4));
                fgIsDuplicatedFrame = TRUE;
            }
            else {
                // Update last received SeqCtrl of current TID
                prStaRec->u2TIDLastRxSeqCtrl[prSWRfb->ucQosTID] =
                    NIC_RFB_GET_SEQCTRL(prSWRfb);

                //DBGLOG(MIKE, TRACE, ("prStaRecord->u2TIDLastRxSeqCtrl[%d] = %d(%#x %#x)\n",
                    //prSWRfb->ucQosTID, prStaRec->u2TIDLastRxSeqCtrl[prSWRfb->ucQosTID], prStaRec->aucMacAddr[4], prStaRec->aucMacAddr[5]));
                fgIsDuplicatedFrame = FALSE;
            }
        }
        else {
            if (NIC_RFB_IS_RETRY(prSWRfb) &&
                (prStaRec->u2LastRxSeqCtrl == NIC_RFB_GET_SEQCTRL(prSWRfb))) {

                //4 20060821, mikewu, todo:  Duplicated frame found, update MIB counter (what counter)
                //DBGLOG(MIKE, TRACE, ("MacAddr: "MACSTR", Seq = %d\n",
                    //MAC2STR(prStaRec->aucMacAddr), NIC_RFB_GET_SEQCTRL(prSWRfb) >> 4));

                fgIsDuplicatedFrame = TRUE;
            }
            else {
                // Update last received SeqCtrl
                prStaRec->u2LastRxSeqCtrl = NIC_RFB_GET_SEQCTRL(prSWRfb);

                //DBGLOG(MIKE, TRACE, ("prStaRecord->u2LastRxSeqCtrl = %d\n",
                    //prStaRec->u2LastRxSeqCtrl));
                fgIsDuplicatedFrame = FALSE;
            }
        }
    }
#if DBG
    else {
        DBGLOG(RX, TRACE, ("No STA_RECORD_T for "MACSTR"\n",
            MAC2STR(prSWRfb->prRxStatus->aucTA)));
    }
#endif /* DBG */

    if (NIC_RFB_IS_RETRY(prSWRfb)) {
        RX_INC_CNT(prRxCtrl, RX_RETRY_FRAME_COUNT);
    }

    if (fgIsDuplicatedFrame) {
        RX_INC_CNT(prRxCtrl, RX_DUPLICATE_DROP_COUNT);
    }

    return fgIsDuplicatedFrame;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief rxProcessMPDUSecurity() is used to check security(software BIP, decryption,
*        MIC check) per MPDU.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prSWRfb        The RFB which is being processed.
*
* \retval WLAN_STATUS_SUCCESS
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rxProcessMPDUSecurity (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    )
{
    WLAN_STATUS u4Status = WLAN_STATUS_SUCCESS;

    ASSERT(prAdapter);
    ASSERT(prSWRfb);
    
#if SUPPORT_WAPI
    u4Status = rxProcessMPDUWpiSecurity(prAdapter, prSWRfb);
#endif

    return u4Status;
}


/*----------------------------------------------------------------------------*/
/*!
* \brief rxDefragMPDU() is used to defragment the incoming packets.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prSWRfb        The RFB which is being processed.
*
* \retval NOT NULL  Receive the last fragment data
* \retval NULL      Receive the fragment packet which is not the last
*/
/*----------------------------------------------------------------------------*/
P_SW_RFB_T rxDefragMPDU(
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSWRfb
    )
{
    P_RX_CTRL_T prRxCtrl;
    P_RX_STATUS_T prRxStatus;
    UINT_16 u2SeqCtrl;
    UINT_8 ucFragNum;
    BOOLEAN fgFirst = FALSE;
    BOOLEAN fgLast = FALSE;
    P_FRAG_INFO_T prFragInfo;
    P_SW_RFB_T prOutputSwRfb = (P_SW_RFB_T)NULL;
    UINT_32 i = 0;

    DEBUGFUNC("rxDefragMPDU");


    ASSERT(prAdapter);
    ASSERT(prSWRfb);
    prRxCtrl = &prAdapter->rRxCtrl;
    prRxStatus = prSWRfb->prRxStatus;

    u2SeqCtrl = RX_STATUS_GET_SEQ_CTRL(prRxStatus);
    ucFragNum = (UINT_8)(u2SeqCtrl & MASK_SC_FRAG_NUM);

    if (!RX_STATUS_IS_MORE_FRAG(prRxStatus)) {
        /* The last fragment frame */
        if (ucFragNum) {
            fgLast = TRUE;
        }
        /* Non-fragment frame */
        else {
            return prSWRfb;
        }
    }
    /* The fragment frame except the last one */
    else {
        if (ucFragNum == 0) {
            fgFirst = TRUE;
        }
    }

    for (i = 0; i < MAX_NUM_CONCURRENT_FRAGMENTED_MSDUS; i++) {

        prFragInfo = &prSWRfb->prStaRec->rFragInfo[i];

        if (fgFirst) {//looking for timed-out frag buffer

            if (prFragInfo->pr1stFrag == (P_SW_RFB_T)NULL) {//find a free frag buffer
                break;
            }
        }
        else {//looking for a buffer with desired next seqctrl

            if (prFragInfo->pr1stFrag == (P_SW_RFB_T)NULL) {
                continue;
            }

            if (NIC_RFB_IS_QOS(prSWRfb)) {
                if (NIC_RFB_IS_QOS(prFragInfo->pr1stFrag)) {
                    if (NIC_RFB_GET_SEQCTRL(prSWRfb) == prFragInfo->u2NextFragSeqCtrl) {
                        break;
                    }
                }
            }
            else {
                if (!NIC_RFB_IS_QOS(prFragInfo->pr1stFrag)) {
                    if (NIC_RFB_GET_SEQCTRL(prSWRfb) == prFragInfo->u2NextFragSeqCtrl) {
                        break;
                    }
                }
            }
        }
    }

    if (i >= MAX_NUM_CONCURRENT_FRAGMENTED_MSDUS) {

        /* Can't find a proper FRAG_INFO_T.
         * I. 1st Fragment MPDU, all of the FragInfo are exhausted
         * II. 2nd ~ (n-1)th Fragment MPDU, can't find the right FragInfo for defragment.
         * Because we won't process fragment frame outside this function, so
         * we should free it right away.
         */
        nicRxReturnRFB(prAdapter, prSWRfb);

        return (P_SW_RFB_T)NULL;
    }

    /* NOTE(Kevin): force to check defragment buffer in nicProcessRxInterrupt()
     */
    prRxCtrl->fgIsDefragQueNonEmpty = TRUE;

    //printk("rxDefragMPDU first 2\n");
    ASSERT(prFragInfo);

    if (fgFirst) {
        //printk("rxDefragMPDU first\n");
        SET_EXPIRATION_TIME(prFragInfo->rReceiveLifetimeLimit,
            TU_TO_SYSTIME(DOT11_RECEIVE_LIFETIME_TU_DEFAULT));

        prFragInfo->pr1stFrag = prSWRfb;

        prFragInfo->pucNextFragStart =
            (PUINT_8) prSWRfb->pvHeader + (prSWRfb->u2FrameLength);

        prFragInfo->u2NextFragSeqCtrl = u2SeqCtrl + 1;
        //printk("First: nextFragmentSeqCtrl = %d, u2SeqCtrl = %d\n",
        //    prFragInfo->nextFragmentSeqCtrl, prRxStatus->u2SeqCtrl);

        prSWRfb->fgFragmented = TRUE;
    }
    else {
        DBGLOG(RX, TRACE,
            ("Intermediate rx fragment: Seq_Ctrl=0x%04x, macHeaderLength = %d\n",
                prRxStatus->u2SeqCtrl, prSWRfb->u2MACHeaderLength));

        i = prSWRfb->u2FrameLength - prSWRfb->u2MACHeaderLength;
        prFragInfo->pr1stFrag->u2FrameLength += (UINT_16)i;

        if (prFragInfo->pr1stFrag->u2FrameLength > CFG_RX_MAX_PKT_SIZE) {
            nicRxReturnRFB(prAdapter, prFragInfo->pr1stFrag);

            prFragInfo->pr1stFrag = (P_SW_RFB_T)NULL;

            nicRxReturnRFB(prAdapter, prSWRfb);
        }
        else {
            kalMemCopy(prFragInfo->pucNextFragStart,
                prSWRfb->pvBody, i);

            nicRxReturnRFB(prAdapter, prSWRfb);

            if (fgLast) {//The last one, free the buffer
                //printk("Defrag: finished\n");
                //dumpMemory32((PUINT_32)prFragInfo->firstFragment_p->pvHeader, prFragInfo->firstFragment_p->frameLength);

                prOutputSwRfb = prFragInfo->pr1stFrag;

                prFragInfo->pr1stFrag = (P_SW_RFB_T)NULL;

                //printk("swRfb_p->frameLength = %d\n", swRfb_p->frameLength);
            }
            else {
                prFragInfo->pucNextFragStart += i;

                prFragInfo->u2NextFragSeqCtrl++;
            }
        }
    }

    DBGLOG_MEM8(RX, LOUD,
                prFragInfo->pr1stFrag->pvHeader,
                prFragInfo->pr1stFrag->u2FrameLength);

    return prOutputSwRfb;

} /* end of rxDefragMPDU() */


/*----------------------------------------------------------------------------*/
/*!
* \brief rxWlanHeaderTranslation() is used to do header translation.
*
* \param[in] prAdapter      Pointer to the Adapter structure.
* \param[in] prSWRfb        The RFB which is being processed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_FAILURE wrong frame type
*/
/*----------------------------------------------------------------------------*/
WLAN_STATUS
rxWlanHeaderTranslation (
    IN P_ADAPTER_T prAdapter,
    IN P_SW_RFB_T prSwRfb
    )
{
    BOOLEAN fgEthernetPresent;
    PUINT_8 pucBody;
    P_WLAN_MAC_HEADER_T prHeader;
    PUINT_8 pucEtherPktStart;
    UINT_16 u2EtherPktLen;

    DEBUGFUNC("rxWlanHeaderTranslation");

    DBGLOG(RX, INFO, ("\n"));

    ASSERT(prAdapter);
    ASSERT(prSwRfb);
    pucBody = (PUINT_8)prSwRfb->pvBody;
    prHeader = (P_WLAN_MAC_HEADER_T)prSwRfb->pvHeader;

    ASSERT(prHeader);

    /* Didn't support TO_DS frame and TO_DS_FROM_DS frame now */
    if (prHeader->u2FrameCtrl & MASK_FC_TO_DS) {
        ASSERT(0);
        return WLAN_STATUS_FAILURE;
    }

    /* Check the LLC of the received 802.11 packet. */
    /* We assume the default case here: the LLC is neither Bridge-Tunnel
       Encapsulation Protocol nor RFC1042 protocol -- the 802.11 MAC is
       replaced by the ISO/IEC 8802-3 MAC below the LLC. */
    fgEthernetPresent = FALSE;
    if (pucBody[0] == 0xAA &&
        pucBody[1] == 0xAA &&
        pucBody[2] == 0x03) {
        /* Check the SNAP OUI field in the LLC. */
        if (pucBody[3] == 0x00 &&
            pucBody[4] == 0x00 &&
            pucBody[5] == 0x00) {
            UINT_16 u2Type;

            /* If the LLC is RFC1042 protocol, we need to check the Type field
               in the LLC against the Selective Translation Table.
               Currently, there are two types in the Selective Translation
               Table according to the WiFi's requirements: AppleTalk ARP
               (0x80F3) and DIX II IPX (0x8137) */
            u2Type = *((PUINT_16) &pucBody[6]);

#if 0
            if (u2Type == 0x8E88) {
                DBGLOG(RSN, TRACE, ("Rx 802.1x\n"));
            }
#endif

            if (u2Type == CONST_HTONS(ETH_P_AARP) || u2Type == CONST_HTONS(ETH_P_IPX)) {
                /* If the type is included in the Selective Translation Table,
                   the 802.11 MAC is replaced by the ISO/IEC 8802-3 MAC below
                   the LLC. */
                DBGLOG(RX, INFO, ("RFC1042: in the Table\n"));

                fgEthernetPresent = FALSE;
            }
            else {
                /* If the type is not included in the Selective Translation
                   Table, the 802.11 MAC and RFC1042 LLC is replaced by its
                   Ethernet MAC representation. */
                DBGLOG(RX, INFO, ("RFC1042: not in the Table\n"));

                fgEthernetPresent = TRUE;
            }

        }
        else if (pucBody[3] == 0x00 &&
                 pucBody[4] == 0x00 &&
                 pucBody[5] == 0xF8) {
            /* If the LLC is Bridge-Tunnel Encapsulation Protocol, the 802.11
               MAC and Bridge-Tunnel LLC is replaced by its Ethernet MAC
               representation. */
            DBGLOG(RX, INFO, ("Bridge-Tunnel\n"));

            fgEthernetPresent = TRUE;
        }
#if DBG
        else {
            DBGLOG(RX, INFO, ("Other LLC\n"));
        }
#endif
    }
#if DBG
    else {
        DBGLOG(RX, INFO, ("Other LLC\n"));
    }
#endif


    /* Replace the 802.11 MAC and the LLC, if needed, by its Ethernet
       representation or the ISO/IEC 8802-3 MAC. */

    if (!fgEthernetPresent) {
        UINT_16 u2Offset;

        DBGLOG(RX, LOUD, ("Rx packet frame length: %d, MAC HeaderLength: %d",
            prSwRfb->u2FrameLength, prSwRfb->u2MACHeaderLength));

        ASSERT(prSwRfb->u2MACHeaderLength >= WLAN_MAC_HEADER_LEN);

        pucEtherPktStart = (PUINT_8)prSwRfb->pvBody - ETHER_HEADER_LEN;
        u2EtherPktLen = prSwRfb->u2FrameLength - prSwRfb->u2MACHeaderLength + ETHER_HEADER_LEN;
        /* Compute the length field in the ISO/IEC 8802-3 MAC. */
        u2Offset = prSwRfb->u2FrameLength - prSwRfb->u2MACHeaderLength; /* Only payload length */
        ((P_ETH_FRAME_T)pucEtherPktStart)->u2TypeLen = HTONS(u2Offset);
    }
    else {
        pucEtherPktStart = (PUINT_8)prSwRfb->pvBody + LLC_LEN - ETHER_HEADER_LEN;
        u2EtherPktLen = prSwRfb->u2FrameLength - prSwRfb->u2MACHeaderLength - LLC_LEN + ETHER_HEADER_LEN;
    }

    /* -------------------------------------------------
       Start to fill the header of 802.3/Ethernet packet
       ------------------------------------------------- */
    /* Copy Source/Destination address fields. */
    if (prHeader->u2FrameCtrl & MASK_FC_FROM_DS) {
         UINT_8 auca3[6], auca1[6];
         COPY_MAC_ADDR(auca1, prHeader->aucAddr1);
         COPY_MAC_ADDR(auca3, prHeader->aucAddr3);
        
         COPY_MAC_ADDR(((P_ETH_FRAME_T) (pucEtherPktStart))->aucDestAddr, auca1);
         COPY_MAC_ADDR(((P_ETH_FRAME_T) (pucEtherPktStart))->aucSrcAddr, auca3);
    }
    else {
         COPY_MAC_ADDR(((P_ETH_FRAME_T) (pucEtherPktStart))->aucDestAddr, prHeader->aucAddr1);
         COPY_MAC_ADDR(((P_ETH_FRAME_T) (pucEtherPktStart))->aucSrcAddr, prHeader->aucAddr2);
    }

    /* If the packet length is less than the minimum size of 802.3 and Ethernet
       frames, we add pad bytes. */
    if (u2EtherPktLen < ETHERNET_MIN_PKT_SZ) {
        u2EtherPktLen = ETHERNET_MAX_PKT_SZ;
    }

    prSwRfb->pvHeader = pucEtherPktStart;
    prSwRfb->u2FrameLength = u2EtherPktLen;
    prSwRfb->pvBody = (PVOID)((PUINT_8)prSwRfb->pvHeader+ ETHER_HEADER_LEN);
    prSwRfb->fgIs8023 = TRUE;

    DBGLOG(RX, LOUD, ("packet length = %d\n", u2EtherPktLen));
    DBGLOG_MEM8(RX, LOUD, pucEtherPktStart, u2EtherPktLen);

    return WLAN_STATUS_SUCCESS;

} /* end of rxWlanPacketHeaderTranslation() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will update the RSSI information to BSS_INFO_T according the
*        the averaged RCPI of received Beacon Frames.
*
* \param[in] prAdapter              Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
rxUpdateRssi (
    IN P_ADAPTER_T  prAdapter
    )
{
    P_BSS_INFO_T prBssInfo;
    RCPI rRcpi;


    ASSERT(prAdapter);
    prBssInfo = &prAdapter->rBssInfo;

    if (prAdapter->eConnectionState == MEDIA_STATE_CONNECTED) {
        OS_SYSTIME rCurrentTime;

        GET_CURRENT_SYSTIME(&rCurrentTime);
        if (CHECK_FOR_TIMEOUT(rCurrentTime,
                              prBssInfo->rRssiLastUpdateTime,
                              SEC_TO_SYSTIME(UPDATE_BSS_RSSI_INTERVAL_SEC))) {

            nicRRGetRCPI(prAdapter, &rRcpi);

            prBssInfo->rRcpi = rRcpi;
            prBssInfo->rRssi = RCPI_TO_dBm(rRcpi);
            prBssInfo->rRssiLastUpdateTime = rCurrentTime;
        }
    }

    return;
} /* end of rxUpdateRssi() */


#if (CFG_DBG_BEACON_RCPI_MEASUREMENT || CFG_LP_PATTERN_SEARCH_SLT)
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to clear the RSSI and link quality records.
*
* \param[in] prAdapter  Pointer to the Adapter structure.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
VOID
rxRssiClearRssiLinkQualityRecords (
    IN  P_ADAPTER_T prAdapter
    )
{
    P_BEACON_RCPI_RECORED_T prBcnRcpiInfo;
    UINT_32 i;


    ASSERT(prAdapter);

    prBcnRcpiInfo= &prAdapter->rBcnRCPIRecord;
    kalMemZero(prBcnRcpiInfo, sizeof(BEACON_RCPI_RECORED_T));
    /* Set the current RCPI value to the minimum RCPI value, -100 dBm. */
    prBcnRcpiInfo->cCurAveRcpi= NO_RCPI_RECORDS;
    prBcnRcpiInfo->cRcpiMin= MAX_RCPI_DBM;
    prBcnRcpiInfo->cRcpiMax= MIN_RCPI_DBM;


    /* Set the values of the RCPI records to the minimum RCPI value, -100
       dBm. */
    for (i= 0; i < MAX_NUM_RCPI_RECORDS; i++) {
        prBcnRcpiInfo->acRcpiArray[i] = MIN_RCPI_DBM;

    }

    return;
} /* end of rssiClearRssiLinkQualityRecords() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to save a new RSSI value to the
*        RSSI record array, and calculate an average RSSI value
*        from the RSSI records. If the value of the given new
*        RSSI is not greater -100, we will not save this value to
*        RSSI record array but calculate the average RSSI only.
*
* \param[in] prAdapter              Pointer to the Adapter structure.
* \param[in] i4NewRssi              New RSSI value.
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
INT_32
rxGetAverageRssi(
    IN  P_ADAPTER_T prAdapter,
    IN  INT_32      i4NewRssi
    )
{
    P_BEACON_RCPI_RECORED_T        prBcnRcpiInfo;

    INT_32 i;
    INT_8 cNewRcpi;
    INT_32 i4Summary;

    UINT_8 ucGapCnt = 0;
    INT_32  i4TmpIdx = 0;
    UINT_8 ucValidSamples = 0;
    INT_32 i4RetRcpi;
    INT_8  cMaxDiff;
    INT_8  cMaxRcpi;
    UINT_8 ucMode = 0;


    ASSERT(prAdapter);

    prBcnRcpiInfo= &prAdapter->rBcnRCPIRecord;

    cNewRcpi = (INT_8)i4NewRssi;

    /* Save the new RCPI value to the record array if it is greater than
       -100. */
    /* Save the new RSSI value to the record array if it's greater than -100. */
    if (cNewRcpi > MIN_RCPI_DBM) {
        prBcnRcpiInfo->acRcpiArray[prBcnRcpiInfo->u4RcpiIndex] = cNewRcpi;

        /* aging case for rssiMaxIndex*/
        if (((prBcnRcpiInfo->u4RcpiIndex == prBcnRcpiInfo->u4RcpiMaxIndex) ||
             (prBcnRcpiInfo->u4RcpiIndex == prBcnRcpiInfo->u4RcpiMinIndex)) &&
            (prBcnRcpiInfo->u4RcpiMaxIndex != prBcnRcpiInfo->u4RcpiMinIndex)) {
                prBcnRcpiInfo->u4RcpiMaxIndex = 0;
                prBcnRcpiInfo->u4RcpiMinIndex = 0;
                for (i = 1; i < MAX_NUM_RCPI_RECORDS; i++) {
                    if (prBcnRcpiInfo->acRcpiArray[i] <= MIN_RCPI_DBM) {
                        break;
                    }

                    if (prBcnRcpiInfo->acRcpiArray[prBcnRcpiInfo->u4RcpiMaxIndex] <
                        prBcnRcpiInfo->acRcpiArray[i]) {
                            prBcnRcpiInfo->u4RcpiMaxIndex = i;
                    }

                    if (prBcnRcpiInfo->acRcpiArray[prBcnRcpiInfo->u4RcpiMinIndex] >
                        prBcnRcpiInfo->acRcpiArray[i]) {
                            prBcnRcpiInfo->u4RcpiMinIndex = i;
                    }
                }
        }
        else {
            if (cNewRcpi >= prBcnRcpiInfo->acRcpiArray[prBcnRcpiInfo->u4RcpiMaxIndex]) {
                prBcnRcpiInfo->u4RcpiMaxIndex = prBcnRcpiInfo->u4RcpiIndex;
            }

            if (cNewRcpi <= prBcnRcpiInfo->acRcpiArray[prBcnRcpiInfo->u4RcpiMinIndex]) {
                prBcnRcpiInfo->u4RcpiMinIndex = prBcnRcpiInfo->u4RcpiIndex;
            }
        }

        prBcnRcpiInfo->u4RcpiIndex++;
        if (prBcnRcpiInfo->u4RcpiIndex >= MAX_NUM_RCPI_RECORDS) {
            prBcnRcpiInfo->u4RcpiIndex = 0;
        }
    }

    /* Calculate the average value from the RSSI records. */
    i4Summary = 0;
    for (i = 0; i < MAX_NUM_RCPI_RECORDS; i++) {
        if (prBcnRcpiInfo->acRcpiArray[i] <= MIN_RCPI_DBM) {
            break;
        }

        ucValidSamples++;
        i4Summary += prBcnRcpiInfo->acRcpiArray[i];
    }

    if (i != 0) {
        i4RetRcpi = ((i4Summary /i));
        //INITLOG(("summary =%d, i=%d, ave Rcpi=%d\n",
        //i4Summary, i, i4RetRcpi));


        /* get the Maximum RSSI differnce(MaxD) in array */
        cMaxDiff = prBcnRcpiInfo->acRcpiArray[prBcnRcpiInfo->u4RcpiMaxIndex] -
                       prBcnRcpiInfo->acRcpiArray[prBcnRcpiInfo->u4RcpiMinIndex];

        if (cMaxDiff < 20) {
            /* all samples are consistent, use orignal mean value */
            return i4RetRcpi;
        }
        else {
            /* Check if the abnormal point is real case or not */
            cMaxRcpi = prBcnRcpiInfo->acRcpiArray[prBcnRcpiInfo->u4RcpiMaxIndex];
            for (i = 1; i < 6; i++) {
                i4TmpIdx = prBcnRcpiInfo->u4RcpiIndex-i;
                if (i4TmpIdx < 0) {
                    i4TmpIdx += MAX_NUM_RCPI_RECORDS ;
                }

                if (cMaxRcpi - prBcnRcpiInfo->acRcpiArray[i4TmpIdx] >= MAX_NUM_RCPI_RECORDS) {
                    ucGapCnt++;
                }
                else {
                    break;
                }
            }
            if (ucGapCnt > 4) {
                /* consider as real case */
                return i4RetRcpi;
            }

            /* MaxD> 20 dB, find the mode  */
            i4Summary = 0;
            for (i = 0; i < MAX_NUM_RCPI_RECORDS; i++) {
                if (prBcnRcpiInfo->acRcpiArray[i] <= MIN_RCPI_DBM) {
                    break;
                }

                if (cMaxRcpi - prBcnRcpiInfo->acRcpiArray[i] < 20) {
                    i4Summary += prBcnRcpiInfo->acRcpiArray[i];
                    ucMode++;
                }
            }

            /* Get the RSSI mean from the mode group if
               mode samples > (1/2 valid samples) */
            if (ucMode >= (ucValidSamples >> 1)) {
                i4RetRcpi = (i4Summary / (ucMode) );
            }
        }
    }
    else {
        i4RetRcpi = NO_RCPI_RECORDS;
    }

    return i4RetRcpi;

} /* end of rxGetAverageRssi() */

BOOL
rxBcnRcpiMeasure (
    IN  P_ADAPTER_T prAdapter,
    IN  P_SW_RFB_T  prSwRfb
    )
{
    P_BEACON_RCPI_RECORED_T        prBcnRcpiInfo;
    P_WLAN_BEACON_FRAME_T           prBcnFrame;
    UINT_16 u2Tmp;
    UINT_32 u4Tmp;
    INT_32  i4Tmp;
    INT_8   cNewRcpi;
    INT_8   cOldAveRcpi;
    INT_8   cRcpiDiff;
    ULARGE_INTEGER   rTbttBcnCnt;
    ULARGE_INTEGER   rBcnTime;
    UINT_16 u2NoiseFloor;

    DEBUGFUNC("rxBcnRcpiMeasure");

    ASSERT(prAdapter);
    ASSERT(prSwRfb);

    if (prAdapter->rArbInfo.eCurrentState != ARB_STATE_NORMAL_TR)
        return TRUE;


    prBcnRcpiInfo = &prAdapter->rBcnRCPIRecord;

    prBcnFrame = (P_WLAN_BEACON_FRAME_T)prSwRfb->pvHeader;
    /*Check dedicate Bcn*/

    u2Tmp = prBcnFrame->u2FrameCtrl;
    u2Tmp &= MASK_FRAME_TYPE;
    if(u2Tmp != MAC_FRAME_BEACON ) {
        return TRUE;
    }
    /*
    //make sure TA of Beacon
    u4Tmp = *(pu4RDSBuf+5);
    u4Tmp &= 0xFFFFFFFF;
    if(u4Tmp != 0x9cE41900  ) {
        return TRUE;
    }
    u4Tmp = *(pu4RDSBuf+6);
    u4Tmp &= 0x0000FFFF;
    if(u4Tmp != 0x0000136D  ) {
        return TRUE;
    }
    */
    prBcnRcpiInfo->u4BcnRecvCnt++;

    /*Get RCPI*/
    cNewRcpi = RCPI_TO_DBM(prSwRfb->prRxStatus->ucRCPI);
    /*Get NF*/

    u2NoiseFloor = ((prSwRfb->prG2->u2NFRate & BITS(6,15))>>6);
    /*Get old Ave RCPI*/
    cOldAveRcpi = prBcnRcpiInfo->cCurAveRcpi;

    /*Calculate AP's TBTT*/

    WLAN_GET_FIELD_64( &prBcnFrame->au4Timestamp, &rBcnTime);
    //for build error of division
#if 0
    rTbttBcnCnt.QuadPart = rBcnTime.QuadPart / TU_TO_USEC(prBcnFrame->u2BeaconInterval);
#else
{
   UINT_64 tmp = rBcnTime.QuadPart;
   do_div(rBcnTime.QuadPart,TU_TO_USEC(prBcnFrame->u2BeaconInterval));	
   rTbttBcnCnt.QuadPart = rBcnTime.QuadPart;
   rBcnTime.QuadPart = tmp;
}
#endif

    /*Store Max and Min RCPI*/
    if(cNewRcpi < prBcnRcpiInfo->cRcpiMin)
        prBcnRcpiInfo->cRcpiMin = cNewRcpi;
    if(cNewRcpi > prBcnRcpiInfo->cRcpiMax)
        prBcnRcpiInfo->cRcpiMax = cNewRcpi;
    //prBcnRcpiInfo->cCurAveRcpi = cNewAveRcpi;
    /*Check diff value*/
    if(cOldAveRcpi == NO_RCPI_RECORDS){
        cRcpiDiff = 0;
    }
    else{
        cRcpiDiff = cNewRcpi- cOldAveRcpi;
    }
    if (ABS(cRcpiDiff) > 2) {
        HAL_CLICK_GPIO0(prAdapter);
        prBcnRcpiInfo->u4RcpiFalseAlarmCnt++;
        DBGLOG(RCPI_MEASURE, INFO, ("(Error)Diff: %3ddB, RSSI:%2d,Avg:%2d, L:0x%02x, V:0x%2x, Fail:%7d/%7d, NF:0x%02x,\n\t\tSeq:%4d, TSF:0x%08x_0x%08x,\n",
                cRcpiDiff, cNewRcpi, cOldAveRcpi,
                ((prSwRfb->prG1->u4CRC ) >> 29) & BITS(0, 1),
                ((prSwRfb->prG1->u4CRC ) >> 24) & BITS(0, 4),
                prBcnRcpiInfo->u4RcpiFalseAlarmCnt, prBcnRcpiInfo->u4BcnRecvCnt,
                u2NoiseFloor,
                ((prBcnFrame->u2SeqCtrl & BITS(4,15)) >> 4),
                rBcnTime.u.HighPart, rBcnTime.u.LowPart
                ));
        if (ABS(cRcpiDiff)>8) {
            /* >8 dB */
            prBcnRcpiInfo->u4Range2++;

        }
        else if (ABS(cRcpiDiff)>4) {
             /* >4, <=8 dB */
            prBcnRcpiInfo->u4Range1++;
        }
        else {
             /* >2, <=4 dB */
            prBcnRcpiInfo->u4Range0++;
        }
    }
    else {

        DBGLOG(RCPI_MEASURE, INFO, ("       Diff: %3ddB, RSSI:%2d,Avg:%2d, L:0x%02x, V:0x%2x, Fail:%7d/%7d, NF:0x%02x,\n\t\tSeq:%4d, TSF:0x%08x_0x%08x,\n",
            cRcpiDiff, cNewRcpi, cOldAveRcpi,
            ((prSwRfb->prG1->u4CRC ) >> 29) & BITS(0, 1),
            ((prSwRfb->prG1->u4CRC ) >> 24) & BITS(0, 4),
            prBcnRcpiInfo->u4RcpiFalseAlarmCnt, prBcnRcpiInfo->u4BcnRecvCnt,
            u2NoiseFloor,
            ((prBcnFrame->u2SeqCtrl & BITS(4,15)) >> 4),
            rBcnTime.u.HighPart, rBcnTime.u.LowPart
            ));

        prBcnRcpiInfo->i4AccuRCPI += cNewRcpi;
        prBcnRcpiInfo->u4AccuNF += u2NoiseFloor;
    }

    /*Get Ave RCPI and save it*/
    u4Tmp= (INT_32) cNewRcpi;
    prBcnRcpiInfo->cCurAveRcpi = (INT_8)rxGetAverageRssi(prAdapter,u4Tmp);
    if (prBcnRcpiInfo->cCurAveRcpi <= -100) {
        ERRORLOG(("rssiGetAverageRssi return Error, AveRcpi = %d\n",\
        prBcnRcpiInfo->cCurAveRcpi));
    }

    /*Check bcn lost*/
    if(!prBcnRcpiInfo->rLastTbttCnt.QuadPart) {
        prBcnRcpiInfo->rLastTbttCnt.QuadPart =
            rTbttBcnCnt.QuadPart;
    }
#if 1 // buggy in this part, which may cause CPU busy loop. removed it temporarily
    if((rTbttBcnCnt.QuadPart - prBcnRcpiInfo->rLastTbttCnt.QuadPart)>1){
#if 0  // For CR ALPS00132010, GPIO1 need set to input mode for daisychain
        HAL_CLICK_GPIO1(prAdapter);
#endif
        for (u4Tmp =1; u4Tmp<(rTbttBcnCnt.QuadPart - prBcnRcpiInfo->rLastTbttCnt.QuadPart);u4Tmp++)
        {
            DBGLOG(RCPI_MEASURE, INFO, ("Lose Beacon   ,  %d\n\n",u4Tmp));
            prBcnRcpiInfo->u4BcnLostCnt++;

            if (u4Tmp > 10) {
                DBGLOG(RCPI_MEASURE, INFO, ("\n\n",u4Tmp));
                break;
            }
        }
#if 0
        NKDbgPrintfW(_T("Lose Beacon   ,  %d times, this tbtt=%I64X, old tbtt=%I64X\n"),\
        (rTbttBcnCnt.QuadPart - prBcnRcpiInfo->rLastTbttCnt.QuadPart),\
        rTbttBcnCnt.QuadPart,\
        prBcnRcpiInfo->rLastTbttCnt.QuadPart);
#endif

    }
#endif
    /*Save last TBTT Cnt*/

    prBcnRcpiInfo->rLastTbttCnt.QuadPart =
        rTbttBcnCnt.QuadPart;
    /*Print Average Data*/
    if( (rTbttBcnCnt.QuadPart % 512) == 0) {
    //if( (rTbttBcnCnt.QuadPart % 64) == 0) {
        i4Tmp= prBcnRcpiInfo->u4BcnRecvCnt - prBcnRcpiInfo->u4RcpiFalseAlarmCnt;
        DBGLOG(RCPI_MEASURE, INFO, ("RSSI_Avg:%2d, BCNLostCnt:%7d, TotalPktCnt=%7d, RSSI_Min:%2d, RSSI_Max:%2d, NF_AVG: 0x%02x,\n\t\trange0(>2, <=4):%7d, range1(>4, <=8):%7d, range2(>8):%7d, \n",
                             prBcnRcpiInfo->i4AccuRCPI/i4Tmp,
                             prBcnRcpiInfo->u4BcnLostCnt,
                             prBcnRcpiInfo->u4BcnRecvCnt,
                             prBcnRcpiInfo->cRcpiMin,
                             prBcnRcpiInfo->cRcpiMax,
                             prBcnRcpiInfo->u4AccuNF/i4Tmp,
                             prBcnRcpiInfo->u4Range0,
                             prBcnRcpiInfo->u4Range1,
                             prBcnRcpiInfo->u4Range2
                             ));

    }


    return TRUE;
} /* rxRDSMeasureRecord */
#endif



