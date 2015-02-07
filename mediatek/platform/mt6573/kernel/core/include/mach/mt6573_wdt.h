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

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

/*****************************************************************************
 *
 * Filename:
 * ---------
 *    wdt_hw.h
 *
 * Project:
 * --------
 *   MT6573 
 *
 * Description:
 * ------------
 *   This file is intends for MT6573 WDT driver.
 *
 * Author:
 * -------
 *  Lvqiang Huang (MTK80152)
 *
 ****************************************************************************/
#ifndef _WDT_HW_H
#define _WDT_HW_H

#include <mach/mt6573_reg_base.h>
#define		MT6573_WDT_BASE				       AP_RGU_BASE                           

#define 	MT6573_WDT_MODE   	        (MT6573_WDT_BASE+0x0000)
#define 	MT6573_WDT_LENGTH 	        (MT6573_WDT_BASE+0x0004)
#define 	MT6573_WDT_RESTART 	        (MT6573_WDT_BASE+0x0008)
#define 	MT6573_WDT_STATUS  	        (MT6573_WDT_BASE+0x000C)
#define 	MT6573_SW_PERIPH_RSTN       (MT6573_WDT_BASE+0x0010)
#define 	MT6573_SW_DSP_RSTN    	    (MT6573_WDT_BASE+0x0014)
#define		MT6573_WDT_INTERNAL	  			(MT6573_WDT_BASE+0x0018)
#define		MT6573_WDT_SWRST		        (MT6573_WDT_BASE+0x001C)
#define   MT6573_WDT_DSP_MODE         (MT6573_WDT_BASE+0x0020)
#define   MT6573_WDT_DSP_LENGTH       (MT6573_WDT_BASE+0x0024)
#define   MT6573_WDT_DSP_RESTART      (MT6573_WDT_BASE+0x0028)
#define   MT6573_WDT_DSP_STA          (MT6573_WDT_BASE+0x002C)
#define   MT6573_WDT_MD_MODE          (MT6573_WDT_BASE+0x0030)
#define   MT6573_WDT_MD_LENGTH        (MT6573_WDT_BASE+0x0034)
#define   MT6573_WDT_MD_RESTART       (MT6573_WDT_BASE+0x0038)
#define   MT6573_WDT_MD_STA           (MT6573_WDT_BASE+0x003C)
#define		MT6573_MD_INTERNAL	  			(MT6573_WDT_BASE+0x0040)
#define		MT6573_MD_SWRST		          (MT6573_WDT_BASE+0x0044)


/*WDT_MODE*/
#define 	MT6573_WDT_MODE_KEYMASK	    0xff00
#define 	MT6573_WDT_MODE_KEY		      0x2200

//#define 	MT6573_WDT_PWR_KEY_DIS      0x0004
#define 	MT6573_WDT_MODE_AUTORST     0x0010
#define 	MT6573_WDT_RESET_IRQ        0x0008
#define   MT6573_WDT_MODE_EXTEN       0x0004
#define   MT6573_WDT_MODE_DEBUG       0x0002
#define 	MT6573_WDT_MODE_ENABLE		  0x0001


/*WDT_LENGTH*/
#define 	MT6573_WDT_LENGTH_TOUT		0xffe0
#define 	MT6573_WDT_LENGTH_KEYMASK	0x001f
#define 	MT6573_WDT_LENGTH_KEY		  0x0008

/*WDT_RESTART*/
#define 	MT6573_WDT_RESTART_KEY		0x1971

/*WDT_STATUS*/
#define 	MT6573_WDT_STATUS_HWWDT	    0x8000
#define 	MT6573_WDT_STATUS_SWWDT  	  0x4000

/*MT6573_SW_PERIPH_RSTN*/
#define   MT6573_SW_PERIPH_RSTN_KEY    0x37
#define   MT6573_SW_PERIPH_RSTN_MDRST  0x0800
#define   MT6573_SW_PERIPH_RSTN_DMARST 0x4000

/*MT6573_SW_DSP_RSTN*/
#define   MT6573_SW_DSP_RSTN_KEY    0x48
#define   MT6573_SW_DSP_RSTN_RST    0x8000

/*WDT_SWRST*/
#define     MT6573_WDT_SWRST_KEY        0x1209

/*WDT_DSP_MODE*/
#define MT6573_WDT_DSP_MODE_ENABLE      0x1
#define MT6573_WDT_DSP_MODE_IRQ         0x8
#define MT6573_WDT_DSP_MODE_KEY         0x2200

/*WDT_DSP_LENGTH*/
#define MT6573_WDT_DSP_LENGTH_KEY         0x8

/*WDT_DSP_RESTART*/
#define MT6573_WDT_DSP_RESTART_KEY        0x1971

/*WDT_DSP_STA*/
#define MT6573_WDT_DSP_STA_DSPWDT     0x8000

/*WDT_MD_MODE*/
#define MT6573_WDT_MD_MODE_EN       0x1
#define MT6573_WDT_MD_MODE_RSTEN    0x2
#define MT6573_WDT_MD_MODE_IRQ      0x8
#define MT6573_WDT_MD_MODE_KEY      0x2200

/*WDT_MD_LENGTH*/
#define MT6573_WDT_MD_LENGTH_KEY    0x8

/*WDT_MD_RESTART*/
#define MT6573_WDT_MD_RESTART_KEY   0x1971

/*WDT_MD_STA*/
#define MT6573_WDT_MD_STA_HW    0x8000
#define MT6573_WDT_MD_STA_SW    0x4000

/*WDT_MD_SWRST*/
#define WDT_MD_SWRST_KEY  0x1209

extern void WDT_arch_reset(char mode);

#endif   /*_WDT_HW_H*/
