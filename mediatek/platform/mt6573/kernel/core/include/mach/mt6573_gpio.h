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

/******************************************************************************
 * mt6516_gpio.h - The file is the gpio header file !
 * 
 * Copyright 2008-2009 MediaTek Co.,Ltd.
 * 
 * DESCRIPTION: - 
 *     This file expose an in-kernel gpio modules to other device drivers
 *
 * modification history
 * ----------------------------------------
 * 01a, 08 oct 2008, Koshi,Chiu written
 * ----------------------------------------
 ******************************************************************************/

#include <linux/fs.h>
#include <linux/ioctl.h>
#include <cust_gpio_usage.h>
/*----------------------------------------------------------------------------*/
//  Error Code No.
#define RSUCCESS        0
/*----------------------------------------------------------------------------*/
#define MAX_GPIO_PIN    203
/******************************************************************************
* Enumeration for GPIO pin
******************************************************************************/
typedef enum GPIO_PIN
{    
    GPIO_UNSUPPORTED = -1,    
        
    GPIO0  , GPIO1  , GPIO2  , GPIO3  , GPIO4  , GPIO5  , GPIO6  , GPIO7  ,
    GPIO8  , GPIO9  , GPIO10 , GPIO11 , GPIO12 , GPIO13 , GPIO14 , GPIO15 ,
    GPIO16 , GPIO17 , GPIO18 , GPIO19 , GPIO20 , GPIO21 , GPIO22 , GPIO23 ,
    GPIO24 , GPIO25 , GPIO26 , GPIO27 , GPIO28 , GPIO29 , GPIO30 , GPIO31 ,
    GPIO32 , GPIO33 , GPIO34 , GPIO35 , GPIO36 , GPIO37 , GPIO38 , GPIO39 ,
    GPIO40 , GPIO41 , GPIO42 , GPIO43 , GPIO44 , GPIO45 , GPIO46 , GPIO47 ,
    GPIO48 , GPIO49 , GPIO50 , GPIO51 , GPIO52 , GPIO53 , GPIO54 , GPIO55 ,
    GPIO56 , GPIO57 , GPIO58 , GPIO59 , GPIO60 , GPIO61 , GPIO62 , GPIO63 ,
    GPIO64 , GPIO65 , GPIO66 , GPIO67 , GPIO68 , GPIO69 , GPIO70 , GPIO71 ,
    GPIO72 , GPIO73 , GPIO74 , GPIO75 , GPIO76 , GPIO77 , GPIO78 , GPIO79 ,
    GPIO80 , GPIO81 , GPIO82 , GPIO83 , GPIO84 , GPIO85 , GPIO86 , GPIO87 ,
    GPIO88 , GPIO89 , GPIO90 , GPIO91 , GPIO92 , GPIO93 , GPIO94 , GPIO95 ,
    GPIO96 , GPIO97 , GPIO98 , GPIO99 , GPIO100, GPIO101, GPIO102, GPIO103,
    GPIO104, GPIO105, GPIO106, GPIO107, GPIO108, GPIO109, GPIO110, GPIO111,
    GPIO112, GPIO113, GPIO114, GPIO115, GPIO116, GPIO117, GPIO118, GPIO119,
    GPIO120, GPIO121, GPIO122, GPIO123, GPIO124, GPIO125, GPIO126, GPIO127,
    GPIO128, GPIO129, GPIO130, GPIO131, GPIO132, GPIO133, GPIO134, GPIO135,
    GPIO136, GPIO137, GPIO138, GPIO139, GPIO140, GPIO141, GPIO142, GPIO143,
    GPIO144, GPIO145, GPIO146, GPIO147, GPIO148, GPIO149, GPIO150, GPIO151,
    GPIO152, GPIO153, GPIO154, GPIO155, GPIO156, GPIO157, GPIO158, GPIO159,
    GPIO160, GPIO161, GPIO162, GPIO163, GPIO164, GPIO165, GPIO166, GPIO167,
    GPIO168, GPIO169, GPIO170, GPIO171, GPIO172, GPIO173, GPIO174, GPIO175,
    GPIO176, GPIO177, GPIO178, GPIO179, GPIO180, GPIO181, GPIO182, GPIO183,
    GPIO184, GPIO185, GPIO186, GPIO187, GPIO188, GPIO189, GPIO190, GPIO191,
    GPIO192, GPIO193, GPIO194, GPIO195, GPIO196, GPIO197, GPIO198, GPIO199,
    GPIO200, GPIO201, GPIO202,
    
    GPIO_MAX
}GPIO_PIN;         

/******************************************************************************
* Enumeration for Clock output
******************************************************************************/
/* GPIO MODE CONTROL VALUE*/
typedef enum {
    GPIO_MODE_GPIO  = 0,
    GPIO_MODE_00    = 0,
    GPIO_MODE_01    = 1,
    GPIO_MODE_02    = 2,
    GPIO_MODE_03    = 3,
    GPIO_MODE_04    = 4,
    GPIO_MODE_05    = 5,
    GPIO_MODE_06    = 6,
    GPIO_MODE_07    = 7,

    GPIO_MODE_MAX,
    GPIO_MODE_DEFAULT = GPIO_MODE_01,
} GPIO_MODE;
/*----------------------------------------------------------------------------*/
/* GPIO DIRECTION */
typedef enum {
    GPIO_DIR_IN     = 0,
    GPIO_DIR_OUT    = 1,

    GPIO_DIR_MAX,
    GPIO_DIR_DEFAULT = GPIO_DIR_IN,
} GPIO_DIR;
/*----------------------------------------------------------------------------*/
/* GPIO PULL ENABLE*/
typedef enum {
    GPIO_PULL_DISABLE = 0,
    GPIO_PULL_ENABLE  = 1,

    GPIO_PULL_EN_MAX,
    GPIO_PULL_EN_DEFAULT = GPIO_PULL_ENABLE,
} GPIO_PULL_EN;
/*----------------------------------------------------------------------------*/
/* GPIO PULL-UP/PULL-DOWN*/
typedef enum {
    GPIO_PULL_DOWN  = 0,
    GPIO_PULL_UP    = 1,

    GPIO_PULL_MAX,
    GPIO_PULL_DEFAULT = GPIO_PULL_DOWN
} GPIO_PULL;
/*----------------------------------------------------------------------------*/
/* GPIO INVERSION */
typedef enum {
    GPIO_DATA_UNINV = 0,
    GPIO_DATA_INV   = 1,

    GPIO_DATA_INV_MAX,
    GPIO_DATA_INV_DEFAULT = GPIO_DATA_UNINV
} GPIO_INVERSION;
/*----------------------------------------------------------------------------*/
/* GPIO OUTPUT */
typedef enum {
    GPIO_OUT_ZERO = 0,
    GPIO_OUT_ONE  = 1,

    GPIO_OUT_MAX,
    GPIO_OUT_DEFAULT = GPIO_OUT_ZERO,
    GPIO_DATA_OUT_DEFAULT = GPIO_OUT_ZERO,  /*compatible with DCT*/
} GPIO_OUT;

/*CLOCK OUT*/
typedef enum {
    CLK_OUT_UNSUPPORTED = -1,
    CLK_OUT0,
    CLK_OUT1,
    CLK_OUT2,
    CLK_OUT3,
    CLK_OUT4,
    CLK_OUT5,
    CLK_MAX	
}GPIO_CLKOUT;

typedef enum CLK_SRC
{
    CLK_SRC_UNSUPPORTED = -1,
    CLK_SRC_F32K = 0x2,
    CLK_SRC_FWCDMA = 0x4,
    CLK_SRC_FGSM = 0x6,
    CLK_SRC_GDSP = 0x8,
    CLK_SRC_SYSCLK,
    CLK_SRC_GEMIX2,
    CLK_SRC_GAPMCU,
    CLK_SRC_GX32W,
    CLK_SRC_X16W_MCLK,
    CLK_SRC_GMDMCU,

    CLK_SRC_MAX
}GPIO_CLKSRC;
    
/*----------------------------------------------------------------------------*/
typedef struct {    
    u16 val;        
    u16 _align1;
    u16 set;
    u16 _align2;
    u16 rst;
    u16 _align3[3];
} VAL_REGS;
/*----------------------------------------------------------------------------*/
typedef struct {
    VAL_REGS    dir[13];            /*0x0000 ~ 0x00CF: 208 bytes*/
    u8          rsv00[304];         /*0x00D0 ~ 0x01FF: 304 bytes*/
    VAL_REGS    pullen[13];         /*0x0200 ~ 0x02CF: 208 bytes*/
    u8          rsv01[304];         /*0x02D0 ~ 0x03FF: 304 bytes*/
    VAL_REGS    pullsel[13];        /*0x0400 ~ 0x04CF: 208 bytes*/
    u8          rsv02[304];         /*0x04D0 ~ 0x05FF: 304 bytes*/    
    VAL_REGS    dinv[13];           /*0x0600 ~ 0x06CF: 208 bytes*/    
    u8          rsv03[304];         /*0x06D0 ~ 0x07FF: 304 bytes*/    
    VAL_REGS    dout[13];           /*0x0800 ~ 0x08CF: 208 bytes*/
    u8          rsv04[304];         /*0x08D0 ~ 0x09FF: 304 bytes*/
    VAL_REGS    din[13];            /*0x0A00 ~ 0x0ACF: 208 bytes*/
    u8          rsv05[304];         /*0x0AD0 ~ 0x0BFF: 304 bytes*/
    VAL_REGS    mode[41];           /*0x0C00 ~ 0x0E90: 656 bytes*/  
} GPIO_REGS;
/*----------------------------------------------------------------------------*/
typedef struct {
    unsigned int no     : 16;
    unsigned int mode   : 3;    
    unsigned int pullsel: 1;
    unsigned int din    : 1;
    unsigned int dout   : 1;
    unsigned int pullen : 1;
    unsigned int dir    : 1;
    unsigned int dinv   : 1;
    unsigned int _align : 7; 
} GPIO_CFG; 
/******************************************************************************
* GPIO Driver interface 
******************************************************************************/
/*direction*/
s32 mt_set_gpio_dir(u32 pin, u32 dir);
s32 mt_get_gpio_dir(u32 pin);

/*pull enable*/
s32 mt_set_gpio_pull_enable(u32 pin, u32 enable);
s32 mt_get_gpio_pull_enable(u32 pin);
/*pull select*/
s32 mt_set_gpio_pull_select(u32 pin, u32 select);    
s32 mt_get_gpio_pull_select(u32 pin);

/*data inversion*/
s32 mt_set_gpio_inversion(u32 pin, u32 enable);
s32 mt_get_gpio_inversion(u32 pin);

/*input/output*/
s32 mt_set_gpio_out(u32 pin, u32 output);
s32 mt_get_gpio_out(u32 pin);
s32 mt_get_gpio_in(u32 pin);

/*mode control*/
s32 mt_set_gpio_mode(u32 pin, u32 mode);
s32 mt_get_gpio_mode(u32 pin);

/*clock output setting*/
s32 mt_set_clock_output(u32 u4ClkOut, u32 u4Src);
s32 mt_get_clock_output(u32 u4ClkOut);

/*misc functions for protect GPIO*/
void mt_gpio_set_default(void);
void mt_gpio_dump(GPIO_REGS *regs);
void mt_gpio_load(GPIO_REGS *regs);
void mt_gpio_checkpoint_save(void);
void mt_gpio_checkpoint_compare(void);
void gpio_dump_regs(void);
