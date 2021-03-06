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

#include <mach/mt6573_reg_base.h>
//Register address define
#define MIC_BIAS_REG 0xF702F630
#define VMIC_CON1 0xF702F634
#define PMIC_RESERVE_CON2 0xF702FE88

#define ACCDET_RSTB ACCDET_BASE
#define ACCDET_CTRL ACCDET_BASE + 0x0004
#define ACCDET_STATE_SWCTRL ACCDET_BASE + 0x0008
#define ACCDET_PWM_WIDTH ACCDET_BASE + 0x000c

#define ACCDET_PWM_THRESH ACCDET_BASE + 0x0010
#define ACCDET_EN_DELAY_NUM ACCDET_BASE + 0x0024
#define ACCDET_PWM_IDLE_VALUE ACCDET_BASE + 0x0028
#define ACCDET_DEBOUNCE0 ACCDET_BASE + 0x002c
#define ACCDET_DEBOUNCE1 ACCDET_BASE + 0x0030
#define ACCDET_DEBOUNCE2 ACCDET_BASE + 0x0034
#define ACCDET_DEBOUNCE3 ACCDET_BASE + 0x0038


#define ACCDET_IRQ_STS ACCDET_BASE + 0x003c
#define ACCDET_CURR_IN ACCDET_BASE + 0x0040
#define ACCDET_SAMPLE_IN ACCDET_BASE + 0x0044
#define ACCDET_MEMORIZED_IN ACCDET_BASE + 0x0048


#define ACCDET_TV_START_LINE0 ACCDET_BASE + 0x0058
#define ACCDET_TV_END_LINE0 ACCDET_BASE + 0x005C
#define ACCDET_TV_START_LINE1 ACCDET_BASE + 0x0060
#define ACCDET_TV_END_LINE1 ACCDET_BASE + 0x0064
#define ACCDET_TV_PRE_LINE ACCDET_BASE + 0x0068
#define ACCDET_TV_START_PXL ACCDET_BASE + 0x006c
#define ACCDET_TV_END_PXL ACCDET_BASE + 0x0070
#define ACCDET_TV_EN_DELAY_NUM ACCDET_BASE + 0x0074
#define ACCDET_TV_DIV_RATE ACCDET_BASE + 0x0078

//Register value define
#define RSTB_BIT        (0<<0)
#define RSTB_FINISH_BIT (1<<0)
#define MIC_INIT_BIT (1<<1)
#define TV_INIT_BIT (1<<2)

#define IRQ_STATUS_BIT  (1<<0)
#define IRQ_CLR_BIT     (1<<8)
#define IRQ_CLR_FINISH  (0<<8)

#define ACCDET_ENABLE   (1<<0)
#define ACCDET_DISABLE  (0<<0)
#define ANASW_BIT (1<<0)
#define TV_DET_BIT (1<<1)
#define CMP_PWM_EN_BIT (1<<2)
#define VTH_PWM_EN_BIT (1<<3)
#define MBIAS_PWM_EN_BIT (1<<4)
#define ACCDET_SWCTRL_EN (MBIAS_PWM_EN_BIT | VTH_PWM_EN_BIT | CMP_PWM_EN_BIT | ANASW_BIT)

//PMIC reserve CON2 value define
#define MIC_FORCE_LOW   (1<<3)

#define VMIC_EN_BIT (1<<0)
#define VMIC_LOW_POWER_BIT (1<<2)

