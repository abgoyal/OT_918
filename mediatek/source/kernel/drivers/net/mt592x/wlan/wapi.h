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

/*******************************************************************************
* LEGAL DISCLAIMER

* Copyright (c) 2008 MediaTek Inc.  ALL RIGHTS RESERVED.

* BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES 
* AND AGREES THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS (��MEDIATEK 
* SOFTWARE��)RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE 
* PROVIDED TO BUYER ON AN ��AS IS�� BASIS ONLY.  MEDIATEK EXPRESSLY 
* DISCLAIMS ANY AND ALL WARRANTIES, WHETHER EXPRESS OR IMPLIED, INCLUDING 
* BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE, OR NON-INFRINGEMENT. NOR DOES MEDIATEK PROVIDE 
* ANY WARRANTY WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTIES 
* WHICH MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE.  
* BUYER AGREES TO LOOK ONLY TO SUCH THIRD PARTIES FOR ANY AND ALL 
* WARRANTY CLAIMS RELATING THERETO. MEDIATEK SHALL NOT BE RESPONSIBLE FOR 
* ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER��S SPECIFICATION OR CONFORMING 
* TO A PARTICULAR STANDARD OR OPEN FORUM.

* BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE 
* LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER SHALL BE, 
* AT MEDIATEK'S SOLE OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE
* OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGES PAID BY BUYER TO 
* MEDIATEK FOR SUCH MEDIATEK SOFTWARE. 

* THE MEDIATEK SOFTWARE IS PROVIDED FOR AND ONLY FOR USE WITH MEDIATEK CHIPS 
* OR PRODUCTS.  EXCEPT AS EXPRESSLY PROVIDED, NO LICENSE IS GRANTED BY 
* IMPLICATION OR OTHERWISE UNDER ANY INTELLECTUAL PROPERTY RIGHTS, INCLUDING 
* PATENT OR COPYRIGHTS, OF MEDIATEK.  UNAUTHORIZED USE, REPRODUCTION, OR 
* DISCLOSURE OF THE MEDIATEK SOFTWARE IN WHOLE OR IN PART IS STRICTLY PROHIBITED.

* THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH 
* THE LAWS OF THE REPUBLIC OF SINGAPORE, EXCLUDING ITS CONFLICT OF LAWS 
* PRINCIPLES. ANY DISPUTES, CONTROVERSIES OR CLAIMS RELATING HERETO OR ARISING 
* HEREFROM SHALL BE EXCLUSIVELY SETTLED VIA ARBITRATION IN SINGAPORE UNDER THE 
* THEN CURRENT ARBITRAL RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE.  
* THE LANGUAGE OF ARBITRATION SHALL BE ENGLISH. THE AWARDS OF THE ARBITRATION 
* SHALL BE FINAL AND BINDING UPON BOTH PARTIES AND SHALL BE ENTERED AND 
* ENFORCEABLE IN ANY COURT OF COMPETENT JURISDICTION.
********************************************************************************
*/
#ifndef _WAPI_H
#define _WAPI_H

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

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

#if SUPPORT_WAPI
/* Structure of WAPI Information */
typedef struct _WAPI_INFO_T {
    UINT_8          ucElemId;
    UCHAR           ucLength;
    UINT_16         u2Version;
    UINT_32         u4AuthKeyMgtSuiteCount;
    UINT_32         au4AuthKeyMgtSuite[MAX_NUM_SUPPORTED_AKM_SUITES];
    UINT_32         u4PairwiseKeyCipherSuiteCount;
    UINT_32         au4PairwiseKeyCipherSuite[MAX_NUM_SUPPORTED_CIPHER_SUITES];
    UINT_32         u4GroupKeyCipherSuite;
    UINT_16         u2WapiCap;
    UINT_16         u2Bkid;
    UINT_8          aucBkid[16][16];
} WAPI_INFO_T, *P_WAPI_INFO_T;

/* WAPI Information element format */
typedef struct _WAPI_INFO_ELEM_T {
    UCHAR       ucElemId;
    UCHAR       ucLength;
    UINT_16     u2Version;
    UINT_16     u2AuthKeyMgtSuiteCount;
    UCHAR       aucAuthKeyMgtSuite1[4];
} WAPI_INFO_ELEM_T, *P_WAPI_INFO_ELEM_T;

#endif

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
#define WAPI_CIPHER_SUITE_WPI           0x01721400 /* WPI_SMS4 */
#define WAPI_AKM_SUITE_802_1X           0x01721400 /* WAI */
#define WAPI_AKM_SUITE_PSK              0x02721400 /* WAI_PSK */
		
#define ELEM_ID_WAPI                    68 /* WAPI IE */
	
#define WAPI_IE(fp)                     ((P_WAPI_INFO_ELEM_T) fp)


/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
BOOLEAN
wapiPerformPolicySelection (
    IN  P_ADAPTER_T         prAdapter,
    IN  P_BSS_DESC_T        prBss
    );

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _RSN_H */

