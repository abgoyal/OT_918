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

#ifndef _MT_ISP_H
#define _MT_ISP_H

#include <linux/ioctl.h>

/*******************************************************************************
*
********************************************************************************/
#define ISP_DEV_MAJOR_NUMBER    251
#define ISP_MAGIC               'k'

/*******************************************************************************
*
********************************************************************************/
typedef struct mt_isp_reg_s {
    unsigned long addr;   // register's addr
    unsigned long val;    // register's value
} mt_isp_reg_t;

typedef struct mt_isp_reg_io_s {
    unsigned long data;   // pointer to mt_isp_reg_t
    unsigned long count;  // count
} mt_isp_reg_io_t;

/*******************************************************************************
*
********************************************************************************/
//IOCTRL(inode * ,file * ,cmd ,arg )
//S means "set through a ptr"
//T means "tell by a arg value"
//G means "get by a ptr"
//Q means "get by return a value"
//X means "switch G and S atomically"
//H means "switch T and Q atomically"
// ioctrl commands
// Reset
#define MT_ISP_IOC_T_RESET      _IO  (ISP_MAGIC, 1)
// Read register from driver
#define MT_ISP_IOC_G_READ_REG   _IOWR(ISP_MAGIC, 2, mt_isp_reg_io_t)
// Write register to driver
#define MT_ISP_IOC_S_WRITE_REG  _IOWR(ISP_MAGIC, 3, mt_isp_reg_io_t)
// Hold reg write to hw, on/off
#define MT_ISP_IOC_T_HOLD_REG   _IOW (ISP_MAGIC, 4, u32)
// MT_ISP_IOC_T_RUN : Tell ISP to run/stop
#define MT_ISP_IOC_T_RUN        _IOW (ISP_MAGIC, 5, u32)
// Wait IRQ
#define MT_ISP_IOC_T_WAIT_IRQ   _IOW (ISP_MAGIC, 6, u32)
// Dump ISP registers , for debug usage
#define MT_ISP_IOC_T_DUMP_REG   _IO  (ISP_MAGIC, 7)
// Dump message level
#define MT_ISP_IOC_T_DBG_FLAG   _IOW (ISP_MAGIC, 8, u32)
// Reset SW Buffer
#define MT_ISP_IOC_T_RESET_BUF  _IO  (ISP_MAGIC, 9)
/*******************************************************************************
*
********************************************************************************/
void mt_isp_mclk_ctrl(int en);
//
#endif

