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
*  permission of MediaTek Inc. (C) 2009
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


/*******************************************************************************
 *
 * Filename:
 * ---------
 *  auddrv_ioctl_msg.h
 *
 * Project:
 * --------
 *   Android Audio Driver
 *
 * Description:
 * ------------
 *   ioctl control message
 *
 * Author:
 * -------
 *   Chipeng    (mtk02308)
 *   Stan Huang (mtk01728)
 *
 *
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime:$
 * $Log:$
 *
 *
 *
 *******************************************************************************/
#ifndef _AUDDRV_IOCTL_MSG_H
#define _AUDDRV_IOCTL_MSG_H


/*****************************************************************************
*                     C O M P I L E R   F L A G S
******************************************************************************
*/


/*****************************************************************************
*                          C O N S T A N T S
******************************************************************************
*/

//below is control message
#define AUD_DRV_IOC_MAGIC 'C'

#define SET_AUDSYS_REG         _IOWR(AUD_DRV_IOC_MAGIC, 0x00, Register_Control*)
#define GET_AUDSYS_REG         _IOWR(AUD_DRV_IOC_MAGIC, 0x01, Register_Control*)
#define SET_ANAAFE_REG         _IOWR(AUD_DRV_IOC_MAGIC, 0x02, Register_Control*)
#define GET_ANAAFE_REG         _IOWR(AUD_DRV_IOC_MAGIC, 0x03, Register_Control*)

#define GET_AFE_BUFFER_SIZE    _IOWR(AUD_DRV_IOC_MAGIC, 0x11, unsigned int)
#define SET_SPEAKER_VOL        _IOW(AUD_DRV_IOC_MAGIC, 0x12, int)
#define SET_SPEAKER_ON         _IOW(AUD_DRV_IOC_MAGIC, 0x13, int)
#define SET_SPEAKER_OFF        _IOW(AUD_DRV_IOC_MAGIC, 0x14, int)
#define SET_HEADSET_           _IOW(AUD_DRV_IOC_MAGIC, 0x15, int)

#define OPEN_DL1_STREAM        _IOWR(AUD_DRV_IOC_MAGIC, 0x20, int)
#define CLOSE_DL1_STREAM       _IOWR(AUD_DRV_IOC_MAGIC, 0x21, int)
#define INIT_DL1_STREAM        _IOWR(AUD_DRV_IOC_MAGIC, 0x22, int)
#define START_DL1_STREAM       _IOWR(AUD_DRV_IOC_MAGIC, 0x23, int)
#define STANDBY_DL1_STREAM     _IOWR(AUD_DRV_IOC_MAGIC, 0x24, int)
#define SET_DL1_AFE_BUFFER     _IOWR(AUD_DRV_IOC_MAGIC, 0x25, int)
#define SET_DL1_SLAVE_MODE     _IOWR(AUD_DRV_IOC_MAGIC, 0x26, int)
#define GET_DL1_SLAVE_MODE     _IOWR(AUD_DRV_IOC_MAGIC, 0x27, int)

#define OPEN_I2S_INPUT_STREAM       _IOWR(AUD_DRV_IOC_MAGIC, 0x30, int)
#define CLOSE_I2S_INPUT_STREAM      _IOWR(AUD_DRV_IOC_MAGIC, 0x31, int)
#define START_I2S_INPUT_STREAM      _IOWR(AUD_DRV_IOC_MAGIC, 0x33, int)
#define STANDBY_I2S_INPUT_STREAM    _IOWR(AUD_DRV_IOC_MAGIC, 0x34, int)
#define SET_I2S_Input_BUFFER        _IOWR(AUD_DRV_IOC_MAGIC, 0x35, int)
#define SET_I2S_Output_BUFFER       _IOWR(AUD_DRV_IOC_MAGIC, 0x36, int)
#define SET_AWB_INPUT_STREAM_STATE  _IOWR(AUD_DRV_IOC_MAGIC, 0x37, int)

#define SET_2IN1_SPEAKER          _IOW(AUD_DRV_IOC_MAGIC, 0x41, int)
#define SET_AUDIO_STATE           _IOWR(AUD_DRV_IOC_MAGIC, 0x42 ,SPH_Control*)
#define GET_AUDIO_STATE           _IOWR(AUD_DRV_IOC_MAGIC, 0x43, SPH_Control*)

#define AUD_SET_LINE_IN_CLOCK     _IOWR(AUD_DRV_IOC_MAGIC, 0x50, int)
#define AUD_SET_CLOCK             _IOWR(AUD_DRV_IOC_MAGIC, 0x51, int)
#define AUD_SET_26MCLOCK          _IOWR(AUD_DRV_IOC_MAGIC, 0x52, int)
#define AUD_SET_ADC_CLOCK         _IOWR(AUD_DRV_IOC_MAGIC, 0x53, int)
#define AUD_SET_I2S_CLOCK         _IOWR(AUD_DRV_IOC_MAGIC, 0x54, int)

#define AUDDRV_RESET_BT_FM_GPIO   _IOWR(AUD_DRV_IOC_MAGIC, 0x60, int)
#define AUDDRV_SET_BT_PCM_GPIO    _IOWR(AUD_DRV_IOC_MAGIC, 0x61, int)
#define AUDDRV_SET_FM_I2S_GPIO    _IOWR(AUD_DRV_IOC_MAGIC, 0x62, int)
#define AUDDRV_MT6573_CHIP_VER    _IOWR(AUD_DRV_IOC_MAGIC, 0x63, int)

#define AUDDRV_ENABLE_ATV_I2S_GPIO   _IOWR(AUD_DRV_IOC_MAGIC, 0x65, int)
#define AUDDRV_DISABLE_ATV_I2S_GPIO  _IOWR(AUD_DRV_IOC_MAGIC, 0x66, int)

#define AUDDRV_FM_ANALOG_PATH        _IOWR(AUD_DRV_IOC_MAGIC, 0x67, int)

#define YUSU_INFO_FROM_USER        _IOWR(AUD_DRV_IOC_MAGIC, 0x71, struct _Info_Data*)      //by HP

#define AUDDRV_START_DAI_OUTPUT    _IOWR(AUD_DRV_IOC_MAGIC, 0x81, int)
#define AUDDRV_STOP_DAI_OUTPUT     _IOWR(AUD_DRV_IOC_MAGIC, 0x82, int)

// used for debug
#define AUDDRV_LOG_PRINT          _IOWR(AUD_DRV_IOC_MAGIC, 0xFD, int)
#define AUDDRV_ASSERT_IOCTL       _IOW(AUD_DRV_IOC_MAGIC, 0xFE, int)
#define AUDDRV_BEE_IOCTL          _IOW(AUD_DRV_IOC_MAGIC, 0xFF, int)

// below defines the YUSU_INFO_FROM_USER message
#define INFO_U2K_MATV_AUDIO_START   0x1001
#define INFO_U2K_MATV_AUDIO_STOP    0x1002


/*****************************************************************************
*                         D A T A   T Y P E S
******************************************************************************
*/
typedef struct
{
    UINT32 offset;
    UINT32 value;
    UINT32 mask;
}Register_Control;

typedef struct
{
   int bSpeechFlag;
   int bBgsFlag;
   int bRecordFlag;
   int bTtyFlag;
   int bVT;
   int bAudioPlay;   
}SPH_Control;

typedef struct       //HP
{
    UINT32 info;
    UINT32 param1;
    UINT32 param2;
}_Info_Data;

/*****************************************************************************
*                        F U N C T I O N   D E F I N I T I O N
******************************************************************************
*/


#endif

