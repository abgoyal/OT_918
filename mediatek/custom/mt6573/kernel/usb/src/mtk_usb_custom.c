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

#include <mt6573_udc.h>
#include <mach/mt6573_pll.h>
#include <linux/jiffies.h>
#include <linux/delay.h>
#include <asm/io.h>

#define TIME_WINDOW   (0x400)
#define A             (3)
#define FRA           (66)

#define USBPHY_READ8(offset)          __raw_readb(USB_BASE+0x800+offset)
#define USBPHY_WRITE8(offset, value)  __raw_writeb(value, USB_BASE+0x800+offset)
#define USBPHY_SET8(offset, mask)     USBPHY_WRITE8(offset, USBPHY_READ8(offset) | mask)
#define USBPHY_CLR8(offset, mask)     USBPHY_WRITE8(offset, USBPHY_READ8(offset) & ~mask)

#define USBPHY_READ16(offset)          __raw_readw(USB_BASE+0x800+offset)
#define USBPHY_WRITE16(offset, value)  __raw_writew(value, USB_BASE+0x800+offset)
#define USBPHY_SET16(offset, mask)     USBPHY_WRITE16(offset, USBPHY_READ16(offset) | mask)
#define USBPHY_CLR16(offset, mask)     USBPHY_WRITE16(offset, USBPHY_READ16(offset) & ~mask)

#define USBPHY_READ32(offset)          __raw_readl(USB_BASE+0x800+offset)
#define USBPHY_WRITE32(offset, value)  __raw_writel(value, USB_BASE+0x800+offset)
#define USBPHY_SET32(offset, mask)     USBPHY_WRITE32(offset, USBPHY_READ32(offset) | mask)
#define USBPHY_CLR32(offset, mask)     USBPHY_WRITE32(offset, USBPHY_READ32(offset) & ~mask)

BOOL mt6573_usb_enable_clock(BOOL enable) 
{
    static int count = 0;
    BOOL res = TRUE;
    
    if (enable && !count) {
        res = hwEnableClock(MT65XX_PDN_PERI_USB, "PERI_USB");
        count++;        
    } else if (!enable) {
        res = hwDisableClock(MT65XX_PDN_PERI_USB, "PERI_USB");
        count=0;
    }
    printk("enable(%d), count(%d)\n", enable, count);
    return res;
}

void hs_slew_rate_cal(void){

    unsigned long start_time, timeout;
    unsigned long data = 0, cal;
    unsigned int timeout_flag = 0;

    USBPHY_SET8(0x1d, 0x40);
    USBPHY_SET8(0x66, 0x20);
    USBPHY_WRITE32(0x700, (1<<28) | (1<<24) | TIME_WINDOW);
    
    start_time = jiffies;
    timeout = jiffies + 3 * HZ;
    
    while(!(USBPHY_READ32(0x710)&0x1))
    {
        if(time_after(jiffies, timeout))
        {
            timeout_flag = 1;
            break;
        }
    }

    if(timeout_flag)
    {
        printk("[USB] Slew Rate Calibration: Timeout\n");
        cal = 0x4;
    }
    else
    {
        printk("[USB] Slew Rate Calibration: Complete\n");
        data = USBPHY_READ32(0x70c);
        cal = ((((2 * A * 48 * TIME_WINDOW) / FRA) / data) + 1) / 2;
    }

    printk("[USB] cal = %lu\n", cal);
    USBPHY_CLR8(0x15, 0x07);
    USBPHY_SET8(0x15, (cal & 0x7));
    USBPHY_CLR8(0x703, 0x01);
    USBPHY_CLR8(0x1d, 0x40);

    return;
}

void mt6573_usb_phy_poweron(struct mt_udc *udc){
    
    if(udc->power == USB_TRUE)
        return;

    mt6573_usb_enable_clock(TRUE);

    udelay(50);

    USBPHY_CLR8(0x6b, 0x04);  
    USBPHY_CLR8(0x66, 0x40); 
    USBPHY_SET8(0x66, 0x20); 
    USBPHY_CLR8(0x60, 0x40);  
    USBPHY_SET8(0x60, 0x80);  
    USBPHY_CLR8(0x1e, 0x04);  
    USBPHY_CLR8(0x15, 0x07);  
    USBPHY_SET8(0x15, 0x01);
    USBPHY_CLR8(0x10, 0x03);  
    USBPHY_SET8(0x10, 0x02);
    USBPHY_CLR8(0x10, 0x0c);  
    USBPHY_SET8(0x10, 0x08);
    USBPHY_CLR8(0x18, 0x07);  
    USBPHY_SET8(0x18, 0x04);
    USBPHY_SET8(0x18, 0x40);  
    USBPHY_SET8(0x18, 0x20);  
    USBPHY_CLR8(0x18, 0x10);  
    USBPHY_CLR8(0x16, 0x03); 
    USBPHY_SET8(0x16, 0x02);
    USBPHY_CLR8(0x02, 0x3f);  
    USBPHY_SET8(0x02, 0x0a);
    USBPHY_CLR8(0x1b, 0x01);  
    USBPHY_CLR8(0x1b, 0x02);  
    USBPHY_CLR8(0x6a, 0x04);  
    USBPHY_SET8(0x1b, 0x04); 

    udelay(100);

    udc->power = USB_TRUE;
    
    return;
}

void mt6573_usb_phy_savecurrent(struct mt_udc *udc){

    if(!udc || (udc->power == USB_FALSE))
        return;

    USBPHY_CLR8(0x6b, 0x04);  
    USBPHY_CLR8(0x66, 0x40);  
    USBPHY_SET8(0x66, 0x20);  
    USBPHY_CLR8(0x6a, 0x04);  
    USBPHY_SET8(0x68, 0x40);  
    USBPHY_SET8(0x68, 0x80); 
    USBPHY_CLR8(0x68, 0x30);  
    USBPHY_SET8(0x68, 0x10);
    USBPHY_SET8(0x68, 0x04); 
    USBPHY_CLR8(0x69, 0x3c); 
    USBPHY_SET8(0x6a, 0x10); 
    USBPHY_SET8(0x6a, 0x20); 
    USBPHY_SET8(0x6a, 0x08); 
    USBPHY_SET8(0x6a, 0x02); 
    USBPHY_SET8(0x6a, 0x80); 
    USBPHY_CLR8(0x1b, 0x04); 

    udelay(100);

    USBPHY_SET8(0x63, 0x02); 
    
    udelay(1);

    USBPHY_SET8(0x6a, 0x04); 

    udelay(1);

    mt6573_usb_enable_clock(FALSE);

    udc->power = USB_FALSE;
    
    return;
}

void mt6573_usb_phy_recover(struct mt_udc *udc){

    if(udc->power == USB_TRUE)
        return;

    mt6573_usb_enable_clock(TRUE);

    udelay(50);

    USBPHY_CLR8(0x1e, 0x04);
    USBPHY_CLR8(0x10, 0x10);  
    USBPHY_CLR8(0x6b, 0x04); 
    USBPHY_CLR8(0x66, 0x40);  
    USBPHY_SET8(0x66, 0x20);  
    USBPHY_CLR8(0x6a, 0x04); 
    USBPHY_CLR8(0x68, 0x40);  
    USBPHY_CLR8(0x68, 0x80);  
    USBPHY_CLR8(0x68, 0x30);  
    USBPHY_CLR8(0x68, 0x04);  
    USBPHY_CLR8(0x69, 0x3c);  
    USBPHY_CLR8(0x6a, 0x10);  
    USBPHY_CLR8(0x6a, 0x20);  
    USBPHY_CLR8(0x6a, 0x08);  
    USBPHY_CLR8(0x6a, 0x02); 
    USBPHY_CLR8(0x6a, 0x80); 
    USBPHY_SET8(0x1b, 0x04); 
		USBPHY_SET8(0x00, 0x80); 
    udelay(100);

    hs_slew_rate_cal();

    udc->power = USB_TRUE;

    return;
}


