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

#ifdef MTK_DSPIRDBG
/*dsp logger*/
X_CON_SCE(CON_SCE_SS_FCORE_LOGGING, 0x10001C23, 0x0000D007, 0x0000D005, 0x00001009, 0x0000D01A, 0x0000D026, 0x00001008)
#endif
/* mobile TV */
X_CON_SCE(CON_SCE_MTV, 0x10001C23, 0x0000D00D, 0x0000D00E, 0x0000100B, 0x0000D009, 0x0000D025, 0x00001009)

/* video telephonly */
X_CON_SCE(CON_SCE_VT, 0x10001C23, 0x0000D006, 0x0000D018, 0x00001008, 0x0000D009, 0x0000D025, 0x00001009)

/* video record */
X_CON_SCE(CON_SCE_VIDEO_REC, 0x10001C2D, 0x0000D00D, 0x0000D008, 0x00001007, 0x0000D009, 0x0000D025, 0x00001009)

/* Camera capture + digital zoom in */
X_CON_SCE(CON_SCE_CAM_CAP, 0x10001C2C, 0x0000D000, 0x0000D016, 0x00001007, 0x0000D009, 0x0000D025, 0x00001009)

/* camera preview */
X_CON_SCE(CON_SCE_CAM_PREVIEW, 0x10001C2E, 0x0000D000, 0x0000D014, 0x00001007, 0x0000D009, 0x0000D025, 0x00001009)

/* TVOUT: H.264 async decode */
X_CON_SCE(CON_SCE_TVOUT_H264_DEC, 0x10001C23, 0x000D00D, 0x0000D012, 0x00001007, 0x0000D009, 0x0000D025, 0x00001009)

/* video playback */
X_CON_SCE(CON_SCE_VIDEO_PLAYBACK, 0x10001C2C, 0x000D00D, 0x0000D008, 0x00001008, 0x0000D009, 0x0000D025, 0x00001009)

/* normal */
X_CON_SCE(CON_SCE_NORMAL, 0x10001C31, 0x0000D007, 0x0000D006, 0x0000100A, 0x0000D009, 0x0000D026, 0x00001009)
