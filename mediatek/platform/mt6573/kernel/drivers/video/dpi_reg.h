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

#ifndef __DPI_REG_H__
#define __DPI_REG_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    unsigned EN         : 1;
	unsigned rsv_1      : 31;
}DPI_REG_EN, *PDPI_REG_EN;

typedef struct
{
    unsigned DPI_OEN_OFF    : 1;
	unsigned rsv_1          : 1;
    unsigned DSI_MODE       : 1;
    unsigned INTF_68_EN     : 1;
    unsigned PXL_FMT        : 2;
    unsigned SRGB_ORDER     : 1;
    unsigned IRGB_ORDER     : 1;
    unsigned FB1_EN         : 1;
    unsigned FB2_EN         : 1;
    unsigned FB_CHK_EN      : 1;
    unsigned rsv_11         : 1;
    unsigned FS_PROT_EN     : 1;
    unsigned FS_RC_EN       : 1;
    unsigned ADP_EN         : 1;
    unsigned DPI_LMU_EN     : 1;
    unsigned rsv_16         : 16;
} DPI_REG_CNTL, *PDPI_REG_CNTL;


typedef struct
{
    unsigned FIFO_EMPTY     : 1;
    unsigned FIFO_FULL      : 1;
    unsigned R_FIFO_EMPTY   : 1;
    unsigned G_FIFO_EMPTY   : 1;
    unsigned B_FIFO_EMPTY   : 1;
    unsigned CNT_OVERFLOW   : 1;
    unsigned LINE_ERR       : 1;
    unsigned FRAME_ERR      : 1;
    unsigned VSYNC          : 1;
    unsigned rsv_9          : 23;
} DPI_REG_INTERRUPT, *PDPI_REG_INTERRUPT;


typedef struct
{
    UINT16 WIDTH;
    UINT16 HEIGHT;
} DPI_REG_SIZE, *PDPI_REG_SIZE;


typedef struct
{
    unsigned DIVISOR  : 5;
    unsigned rsv_5    : 3;
    unsigned DUTY     : 5;
    unsigned rsv_13   : 18;
    unsigned POLARITY : 1;
} DPI_REG_CLKCNTL, *PDPI_REG_CLKCNTL;


typedef struct
{
    unsigned DITHER_MODE : 2;
    unsigned rsv_2       : 2;
    unsigned IMPOSE_SEL  : 3;
    unsigned rsv_7       : 1;
    unsigned B_LBITS_SEL : 3;
    unsigned rsv_11      : 1;
    unsigned G_LBITS_SEL : 3;
    unsigned rsv_15      : 1;
    unsigned R_LBITS_SEL : 3;
    unsigned rsv_19      : 13;
} DPI_DITHER, *PDPI_DITHER;


typedef struct
{
    UINT32 ADDR;
    UINT16 STEP;
    UINT16 rsv_16;
} DPI_REG_FB, *PDPI_REG_FB;


typedef struct
{
    UINT16 WORD_TH;
    UINT16 LINE_TH;
} DPI_REG_OVL_CON, *PDPI_REG_OVL_CON;


typedef struct
{
    UINT16 LOW;
    UINT16 HIGH;
} DPI_REG_FIFO_TH, *PDPI_REG_FIFO_TH;

#define DPI_FIFO_TH_MAX     (496)


typedef struct
{
    UINT16 READ_PTR;
    UINT16 WRITE_PTR;
} DPI_REG_FIFO_PTR, *PDPI_REG_FIFO_PTR;


typedef struct
{
    unsigned HPW       : 8;
    unsigned HBP       : 8;
    unsigned HFP       : 8;
    unsigned HSYNC_POL : 1;
    unsigned DE_POL    : 1;
    unsigned rsv_26    : 6;
} DPI_REG_TGEN_HCNTL, *PDPI_REG_TGEN_HCNTL;


typedef struct
{
    unsigned VPW       : 8;
    unsigned VBP       : 8;
    unsigned VFP       : 8;
    unsigned VSYNC_POL : 1;
    unsigned rsv_25    : 7;
} DPI_REG_TGEN_VCNTL, *PDPI_REG_TGEN_VCNTL;


typedef struct
{
    unsigned CSR_EN   : 1;
    unsigned CSR_SIZE : 1;
    unsigned CSR_SET  : 2;
    unsigned rsv_4    : 27;
    unsigned CSR_LOAD : 1;
} DPI_REG_CUSR_CNTL, *PDPI_REG_CUSR_CNTL;


typedef struct
{
    UINT16 X;
    UINT16 Y;
} DPI_REG_COORD, *PDPI_REG_COORD;

typedef struct
{
    unsigned ULTRA_EN         : 1;
	unsigned THROTTLE_EN      : 1;
	unsigned rsv_2            : 2;
	unsigned THRESHOLD        : 3;
	unsigned rsv_7            : 9;
	unsigned THROTTLE_PERIOD  : 16;
}DPI_REG_GMC_CNTL, *PDPI_REG_GMC_CNTL;

typedef struct
{
    unsigned BUSY          : 1;
    unsigned DP_BUSY       : 1;
    unsigned TGEN_BUSY     : 1;
    unsigned HWC_BUSY      : 1;
    unsigned OUT_EN        : 1;
	unsigned DPI_GMC_BUSY  : 1;
    unsigned rsv_6         : 10;
    unsigned FB_INUSE      : 2;
    unsigned rsv_18        : 14;
} DPI_REG_STATUS, *PDPI_REG_STATUS;


typedef struct
{
    unsigned FIXED_OUTPUT_EN : 1;
    unsigned FIXED_INPUT_EN  : 1;
    unsigned FIXED_DATA_EN   : 1;
	unsigned FIFO_TEST_EN    : 1;
	unsigned FIFO_TEST_OEN   : 1;
	unsigned rsv_5           : 7;
    unsigned PAL_RSEL        : 4;
    unsigned rsv_16          : 15;
	unsigned DPI_ON          : 1;
} DPI_REG_TMODE, *PDPI_REG_TMODE;


typedef struct
{
    unsigned PAL_RDATA : 24;
    unsigned rsv_24    : 3;
    unsigned BPUSH_ERR : 1;
    unsigned GPUSH_ERR : 1;
    unsigned RPUSH_ERR : 1;
    unsigned GMC_EMPTY : 1;
    unsigned GMC_FULL  : 1;
} DPI_REG_MONITOR0, *PDPI_REG_MONITOR0;

typedef struct
{
    unsigned CKSUM     : 24;
    unsigned BPOP_ERR  : 1;
    unsigned GPOP_ERR  : 1;
    unsigned RPOP_ERR  : 1;
	unsigned rsv_27    : 5;
} DPI_REG_MONITOR1, *PDPI_REG_MONITOR1;

typedef struct
{
    unsigned PRE_FIFO_SIZE  : 10;
	unsigned rsv_10         : 6;
	unsigned FIFO_AE_TH     : 5;
	unsigned rsv_21         : 11;
}DPI_REG_OBS, *PDPI_REG_OBS;

typedef struct
{
    DPI_REG_EN        DPI_EN;           // 0000
    DPI_REG_CNTL      CNTL;             // 0004
    DPI_REG_INTERRUPT INT_ENABLE;       // 0008
    DPI_REG_INTERRUPT INT_STATUS;       // 000C
    
    DPI_REG_SIZE      SIZE;             // 0010
    DPI_REG_CLKCNTL   CLK_CNTL;         // 0014
    DPI_DITHER        DITHER;           // 0018
    UINT32            rsv_001C;         // 001C
    
    UINT32            SWAP_FB_STATUS;   // 0020  
    UINT32            rsv_0024[3];         // 0024..002C
    
    DPI_REG_FB        FB[3];            // 0030..0044
	UINT32			  rsv_0048[2]; 		// 0048..004C

    DPI_REG_OVL_CON   OVL_CON;          // 0050
	UINT32            rsv_0054[3];         // 0054..005C
    
    DPI_REG_FIFO_TH   FIFO_TH;          // 0060
    UINT32            FIFO_INC;         // 0064
    UINT32            rsv_0068;         // 0068
    UINT32            FIFO_MAX;      // 006C

    DPI_REG_TGEN_HCNTL TGEN_HCNTL;      // 0070
    DPI_REG_TGEN_VCNTL TGEN_VCNTL;      // 0074
    UINT32             rsv_0078[2];     // 0078..007C

    DPI_REG_CUSR_CNTL CUSR_CNTL;        // 0080
    DPI_REG_COORD     CUSR_COORD;       // 0084
    UINT32            CUSR_ADDR;        // 0088
    UINT32            rsv_008C;         // 008C

    DPI_REG_GMC_CNTL  GMC_CNTL;         // 0090
	DPI_REG_TMODE	  TMODE;			// 0094
	UINT32			  rsv_0098[2];		// 0098..009C

    DPI_REG_STATUS    STATUS;           // 00A0
    UINT32            ERR_CNT;          // 00A4
    DPI_REG_MONITOR0  MONITOR0;         // 00A8
    DPI_REG_MONITOR1  MONITOR1;         // 00AC   

	DPI_REG_FIFO_PTR  FIFO_PTR;         // 00B0
	UINT32            FIFO_SIZE;        // 00B4
	DPI_REG_OBS       OBS;              // 00B8
} volatile DPI_REGS, *PDPI_REGS;


STATIC_ASSERT(0x0060 == offsetof(DPI_REGS, FIFO_TH));
STATIC_ASSERT(0x0080 == offsetof(DPI_REGS, CUSR_CNTL));
STATIC_ASSERT(0x00BC == sizeof(DPI_REGS));

extern PDPI_REGS const DPI_REG;

#ifdef __cplusplus
}
#endif

#endif // __DPI_REG_H__

