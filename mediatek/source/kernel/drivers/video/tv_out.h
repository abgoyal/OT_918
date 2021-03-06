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


#ifndef _MTKTVOUT_H
#define _MTKTVOUT_H

#define MTK_TVOUT_MAJOR_NUMBER 187


// ---------------------------------------------------------------------------

#define TVOUT_CHECK_RET(expr)             \
    do {                                \
        TVOUT_STATUS ret = (expr);        \
        ASSERT(TVOUT_STATUS_OK == ret);   \
    } while (0)

// ---------------------------------------------------------------------------

typedef enum
{	
    TVOUT_STATUS_OK = 0,
    TVOUT_STATUS_ALREADY_SET,
    TVOUT_STATUS_ERROR,
} TVOUT_STATUS;


typedef enum {
   TVOUT_SYSTEM_NTSC = 0,
   TVOUT_SYSTEM_PAL  = 1,
} TVOUT_SYSTEM;


typedef enum {
   TVOUT_ROT_0   = 0,
   TVOUT_ROT_90  = 1,
   TVOUT_ROT_180 = 2,
   TVOUT_ROT_270 = 3,
} TVOUT_ROT;


typedef enum
{
    TVOUT_FMT_RGB565     = 0,
    TVOUT_FMT_YUV420_SEQ = 1,
    TVOUT_FMT_UYVY422 = 2,
    TVOUT_FMT_YUV420_BLK = 3,
} TVOUT_SRC_FORMAT;


typedef enum
{
    TVOUT_MODE_MIRROR = 0,
    TVOUT_MODE_VIDEO  = 1,
} TVOUT_MODE;


typedef struct {
    void*                phy_addr;
	void*				 vir_addr;
    TVOUT_SRC_FORMAT	 format;
    unsigned int         width, height;
} TVOUT_HQA_BUF ;


#define MTK_IOW(num, dtype)     _IOW('O', num, dtype)
#define MTK_IOR(num, dtype)     _IOR('O', num, dtype)
#define MTK_IOWR(num, dtype)    _IOWR('O', num, dtype)
#define MTK_IO(num)             _IO('O', num)

// --------------------------------------------------------------------------
// Begin of TVOut IOCTL code
#define TVOUT_TURN_ON       			MTK_IOW(60, unsigned long)
#define TVOUT_SET_TV_SYSTEM       		MTK_IOW(61, unsigned long)
#define TVOUT_SET_ORIENTATION     		MTK_IOW(62, unsigned long)
// Video Playback Mode
#define TVOUT_POST_VIDEO_BUFFER     	MTK_IOW(63, unsigned long)
#define TOVUT_LEAVE_VIDEO_PLAYBACK_MODE MTK_IOW(64, unsigned long)
// For Factory Mode
#define TVOUT_IS_TV_CABLE_PLUG_IN 		MTK_IOW(65, unsigned long)

// For different Setting menu
#define TVOUT_ISSHOW_TVOUTBUTTON    	MTK_IOW(66, unsigned long)

#define TVOUT_CTL_SWITCH_TO_HQA_MODE    MTK_IOW(67, unsigned long)
#define TVOUT_CTL_POST_HQA_BUFFER	    MTK_IOW(68, unsigned long)
#define TVOUT_CTL_LEAVE_HQA_MODE   		MTK_IOW(69, unsigned long)
#define TVOUT_DISABLE_VIDEO_MODE    	MTK_IOW(70, unsigned long)

#define TVOUT_FORCE_CLOSE    	        MTK_IOW(71, unsigned long)
#define TVOUT_RESTORE_OPEN    	        MTK_IOW(72, unsigned long)


// ---------------------------------------------------------------------------
// Public Functions
// ---------------------------------------------------------------------------
TVOUT_STATUS TVOUT_PowerEnable(bool);
TVOUT_STATUS TVOUT_TvCablePlugIn(void);
TVOUT_STATUS TVOUT_TvCablePlugOut(void);
TVOUT_STATUS TVOUT_On_LCD_Done(void);
TVOUT_STATUS TVOUT_ScreenUpdateLock(void);
TVOUT_STATUS TVOUT_SetTvSystem(TVOUT_SYSTEM tvSystem);
TVOUT_STATUS TVOUT_SetOrientation(TVOUT_ROT rot);
TVOUT_STATUS TVOUT_EnableColorBar(bool enable);
TVOUT_STATUS TVOUT_PostVideoBuffer(unsigned int VA, TVOUT_SRC_FORMAT format,
		unsigned int width, unsigned int height);
TVOUT_STATUS TVOUT_LeaveVideoBuffer(void);
bool TVOUT_IsCablePlugIn(void);
TVOUT_STATUS TVOUT_DisableVideoMode(bool disable);
void TVOUT_EnableLog(bool);
TVOUT_STATUS TVOUT_Capture_Tvrotbuffer(unsigned int pvbuf, unsigned int bpp);
bool TVOUT_IsTvoutEnabled(void);
void TVOUT_ForceClose(void);
void TVOUT_RestoreOpen(void);
void TVOUT_TurnOn(bool en);


#endif
