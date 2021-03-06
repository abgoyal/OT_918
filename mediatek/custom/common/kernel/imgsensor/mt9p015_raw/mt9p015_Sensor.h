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
 *   mt9p015_Sensor.h
 *
 * Project:
 * --------
 *   YUSU
 *
 * Description:
 * ------------
 *   Header file of Sensor driver
 *
 *
 * Author:
 * -------
 *   Guangye Yang (mtk70662)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by CC/CQ. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *
 *
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by CC/CQ. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef _MT9P015_SENSOR_H
#define _MT9P015_SENSOR_H

#define MT9P015_FACTORY_START_ADDR 0
#define MT9P015_ENGINEER_START_ADDR 39

typedef enum MT9P015_group_enum
{
  MT9P015_PRE_GAIN = 0,
  MT9P015_CMMCLK_CURRENT,
  MT9P015_FRAME_RATE_LIMITATION,
  MT9P015_REGISTER_EDITOR,
  MT9P015_GROUP_TOTAL_NUMS
} MT9P015_FACTORY_GROUP_ENUM;

typedef enum MT9P015_register_index
{
  MT9P015_SENSOR_BASEGAIN = MT9P015_FACTORY_START_ADDR,
  MT9P015_PRE_GAIN_R_INDEX,
  MT9P015_PRE_GAIN_Gr_INDEX,
  MT9P015_PRE_GAIN_Gb_INDEX,
  MT9P015_PRE_GAIN_B_INDEX,
  MT9P015_FACTORY_END_ADDR
} MT9P015_FACTORY_REGISTER_INDEX;

typedef enum MT9P015_engineer_index
{
  MT9P015_CMMCLK_CURRENT_INDEX = MT9P015_ENGINEER_START_ADDR,
  MT9P015_ENGINEER_END
} MT9P015_FACTORY_ENGINEER_INDEX;

typedef struct _sensor_data_struct
{
  SENSOR_REG_STRUCT reg[MT9P015_ENGINEER_END];
  SENSOR_REG_STRUCT cct[MT9P015_FACTORY_END_ADDR];
} sensor_data_struct;

/* IMPORT FUNCTION */
extern int iWriteReg(u16 a_u2Addr, u32 a_u4Data, u32 a_u4Bytes, u16 i2cId);
extern int iReadReg(u16 a_u2Addr, u8 *a_puBuff, u16 i2cId);

#define MT9P015_COLOR_FORMAT                    SENSOR_OUTPUT_FORMAT_RAW_B
#define MT9P015_ENG_INFO                        {128,CMOS_SENSOR,MT9P015_COLOR_FORMAT,}

/* SENSOR PREVIEW/CAPTURE VT CLOCK */
#define MT9P015_PREVIEW_CLK                     96000000
#define MT9P015_CAPTURE_CLK                     96000000

/* SENSOR FULL/PV SIZE */
#define MT9P015_IMAGE_SENSOR_FULL_WIDTH_DRV     2592
#define MT9P015_IMAGE_SENSOR_FULL_HEIGHT_DRV    1944
#define MT9P015_IMAGE_SENSOR_PV_WIDTH_DRV       (MT9P015_IMAGE_SENSOR_FULL_WIDTH_DRV / 2)
#define MT9P015_IMAGE_SENSOR_PV_HEIGHT_DRV      (MT9P015_IMAGE_SENSOR_FULL_HEIGHT_DRV / 2)

/* SENSOR HORIZONTAL/VERTICAL ACTIVE REGION */
#define MT9P015_IMAGE_SENSOR_FULL_HACTIVE       MT9P015_IMAGE_SENSOR_FULL_WIDTH_DRV /* 2592 */
#define MT9P015_IMAGE_SENSOR_FULL_VACTIVE       MT9P015_IMAGE_SENSOR_FULL_HEIGHT_DRV /* 1944 */
#define MT9P015_IMAGE_SENSOR_PV_HACTIVE         MT9P015_IMAGE_SENSOR_PV_WIDTH_DRV /* 1296 */
#define MT9P015_IMAGE_SENSOR_PV_VACTIVE         MT9P015_IMAGE_SENSOR_PV_HEIGHT_DRV /* 972 */

/* SENSOR HORIZONTAL/VERTICAL BLANKING IN ONE PERIOD */
#define MT9P015_IMAGE_SENSOR_FULL_HBLANKING     3307
#define MT9P015_IMAGE_SENSOR_FULL_VBLANKING     90
#define MT9P015_IMAGE_SENSOR_PV_HBLANKING       1717
#define MT9P015_IMAGE_SENSOR_PV_VBLANKING       90

/* SENSOR PIXEL/LINE NUMBERS IN ONE PERIOD */
#define MT9P015_FULL_PERIOD_PIXEL_NUMS          (MT9P015_IMAGE_SENSOR_FULL_HACTIVE + MT9P015_IMAGE_SENSOR_FULL_HBLANKING) /* 5899 */
#define MT9P015_FULL_PERIOD_LINE_NUMS           (MT9P015_IMAGE_SENSOR_FULL_VACTIVE + MT9P015_IMAGE_SENSOR_FULL_VBLANKING) /* 2034 */
#define MT9P015_PV_PERIOD_PIXEL_NUMS            (MT9P015_IMAGE_SENSOR_PV_HACTIVE + MT9P015_IMAGE_SENSOR_PV_HBLANKING) /* 3013 */
#define MT9P015_PV_PERIOD_LINE_NUMS             (MT9P015_IMAGE_SENSOR_PV_VACTIVE + MT9P015_IMAGE_SENSOR_PV_VBLANKING) /* 1062 */

/* SENSOR START/END POSITION */
#define MT9P015_FULL_X_START                    4
#define MT9P015_FULL_Y_START                    4
#define MT9P015_IMAGE_SENSOR_FULL_WIDTH         (MT9P015_IMAGE_SENSOR_FULL_HACTIVE - 32) /* 2560 */
#define MT9P015_IMAGE_SENSOR_FULL_HEIGHT        (MT9P015_IMAGE_SENSOR_FULL_VACTIVE - 24) /* 1924 */
#define MT9P015_PV_X_START                      4
#define MT9P015_PV_Y_START                      4
#define MT9P015_IMAGE_SENSOR_PV_WIDTH           (MT9P015_IMAGE_SENSOR_PV_HACTIVE - 16) /* 1280 */
#define MT9P015_IMAGE_SENSOR_PV_HEIGHT          (MT9P015_IMAGE_SENSOR_PV_VACTIVE - 12) /* 960 */

/* SENSOR GAIN LIMITATION */
#define MT9P015_MIN_ANALOG_GAIN                 1 /* 1x analog gain */
#define MT9P015_MAX_ANALOG_GAIN                 12.7

/* SENSOR READ/WRITE ID */
#define MT9P015_SLV1_WRITE_ID                   0x20 /* SMIA */
#define MT9P015_SLV1_READ_ID                    0x21
#define MT9P015_SLV2_WRITE_ID                   0x30
#define MT9P015_SLV2_READ_ID                    0x31
#define MT9P015_SLV3_WRITE_ID                   0x6C /* MIPI */
#define MT9P015_SLV3_READ_ID                    0x6D
#define MT9P015_SLV4_WRITE_ID                   0x6E
#define MT9P015_SLV4_READ_ID                    0x6F

/* SENSOR PRIVATE STRUCT */
typedef struct MT9P015_sensor_STRUCT
{
  MSDK_SENSOR_CONFIG_STRUCT cfg_data;
  sensor_data_struct eng; /* engineer mode */
  MSDK_SENSOR_ENG_INFO_STRUCT eng_info;
  kal_uint8 mirror;
  kal_bool pv_size; /* false means full size */
  kal_bool video_mode;
  kal_uint16 normal_fps; /* video normal mode max fps */
  kal_uint16 night_fps; /* video night mode max fps */
  kal_uint8 write_id;
  kal_uint8 read_id;
  kal_uint32 vt_clk; /* internal use */
  kal_uint16 shutter;
  kal_uint16 gain;
  kal_uint16 frame_height;
  kal_uint16 line_length;
} MT9P015_sensor_struct;

/* FRAME RATE */
#define MT9P015_FPS(x)                          ((kal_uint32)(10 * (x)))

#endif /* _MT9P015_SENSOR_H */

