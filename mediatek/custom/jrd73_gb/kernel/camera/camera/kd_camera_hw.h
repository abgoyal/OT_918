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

#ifndef _KD_CAMERA_HW_H_
#define _KD_CAMERA_HW_H_
 
#include <mach/mt6573_pll.h>
#include <mach/mt6573_gpio.h>
#include <mach/mt6573_gpt.h>

//Power 
#define CAMERA_POWER_VCAM_A MT65XX_POWER_LDO_VCAMA
#define CAMERA_POWER_VCAM_D MT65XX_POWER_LDO_VCAMD
#define CAMERA_POWER_VCAM_A2 MT65XX_POWER_LDO_VCAMA2
#define CAMERA_POWER_VCAM_D2 MT65XX_POWER_LDO_VCAMD2

#if 0 
//FIXME, should remove when DCT done 
//
#ifndef GPIO_CAMERA_LDO_EN_PIN 
#define GPIO_CAMERA_LDO_EN_PIN GPIO94
#endif 

//
#ifndef GPIO_CAMERA_CMRST_PIN 
#define GPIO_CAMERA_CMRST_PIN GPIO78
#endif 

//
#ifndef GPIO_CAMERA_CMRST_PIN_M_GPIO
#define GPIO_CAMERA_CMRST_PIN_M_GPIO GPIO_MODE_00
#endif 

//
#ifndef GPIO_CAMERA_CMPDN_PIN 
#define GPIO_CAMERA_CMPDN_PIN GPIO79
#endif 

//
#ifndef GPIO_CAMERA_LDO_EN_PIN_M_GPIO
#define GPIO_CAMERA_LDO_EN_PIN_M_GPIO GPIO_MODE_00
#endif 

//
#ifndef GPIO_CAMERA_CMPDN_PIN_M_GPIO
#define GPIO_CAMERA_CMPDN_PIN_M_GPIO  GPIO_MODE_00 
#endif 

//
#ifndef GPIO_CAMERA_CMRST1_PIN
#define GPIO_CAMERA_CMRST1_PIN GPIO97
#endif

//
#ifndef GPIO_CAMERA_CMRST1_PIN_M_GPIO
#define GPIO_CAMERA_CMRST1_PIN_M_GPIO GPIO_MODE_00
#endif

//
#ifndef GPIO_CAMERA_CMPDN1_PIN
#define GPIO_CAMERA_CMPDN1_PIN GPIO96
#endif
//

#ifndef GPIO_CAMERA_CMPDN1_PIN_M_GPIO
#define GPIO_CAMERA_CMPDN1_PIN_M_GPIO GPIO_MODE_00
#endif
#endif 

//i2c id for sensor device, MT6573, the I2C is attached on 1
#define IMG_SENSOR_I2C_GROUP_ID 1

#endif 
