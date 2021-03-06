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

#include <linux/io.h>
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <asm/mach/irq.h>

#include "mach/mt6573_reg_base.h"
#include "mach/irqs.h"
#include "mach/sync_write.h"

static const unsigned int IRQ_MASK_HEADER = 0xF1F1F1F1, IRQ_MASK_FOOTER = 0xF2F2F2F2;

/*
 * mt6573_irq_mask: mask one IRQ
 * @irq_line: IRQ line of the IRQ to mask
 */
void mt6573_irq_mask(unsigned int irq_line)
{
    mt65xx_reg_sync_writel(1 << (irq_line & 0x0000001F), IRQ_MASK_SET0 + (irq_line >> 5) * 4);
}
EXPORT_SYMBOL(mt6573_irq_mask);

/*
 * mt6573_irq_unmask: unmask one IRQ
 * @irq_line: IRQ line of the IRQ to unmask
 */
void mt6573_irq_unmask(unsigned int irq_line)
{
    mt65xx_reg_sync_writel(1 << (irq_line & 0x0000001F), IRQ_MASK_CLR0 + (irq_line >> 5) * 4);
}
EXPORT_SYMBOL(mt6573_irq_unmask);

/*
 * mt6573_irq_ack: acknowledge the IRQ
 * @irq_line: IRQ line of the IRQ to acknowledge
 */
void mt6573_irq_ack(unsigned int irq_line)
{
    mt65xx_reg_sync_writel(irq_line, IRQ_EOI2);
}
EXPORT_SYMBOL(mt6573_irq_ack);

/*
 * mt6573_irq_set_sens: set the sensitivity value for the given IRQ line
 * @irq_line: IRQ line of the IRQ to set sensitivity
 */
void mt6573_irq_set_sens(unsigned int irq_line, unsigned int sens)
{
    if (sens == MT65xx_EDGE_SENSITIVE) {
        mt65xx_reg_sync_writel(1 << (irq_line & 0x0000001F), IRQ_SENS_CLR0 + (irq_line >> 5) * 4);
    } else {
        mt65xx_reg_sync_writel(1 << (irq_line & 0x0000001F), IRQ_SENS_SET0 + (irq_line >> 5) * 4);
    }
}
EXPORT_SYMBOL(mt6573_irq_set_sens);

/*
 * mt6573_irq_set_type: set IRQ type
 * @irq: IRQ number
 * @flow_type: IRQ type
 * Always return 0.
 */
static int mt6573_irq_set_type(unsigned int irq, unsigned int flow_type)
{
    if (flow_type & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING)) {
        mt6573_irq_set_sens(irq, MT65xx_EDGE_SENSITIVE);
        irq_desc[irq].handle_irq = handle_edge_irq;
    } else if (flow_type & (IRQF_TRIGGER_HIGH | IRQF_TRIGGER_LOW)) {
        mt6573_irq_set_sens(irq, MT65xx_LEVEL_SENSITIVE);
        irq_desc[irq].handle_irq = handle_level_irq;
    }

    return 0;
}

/*
 * mt6573_irq_mask_all: mask all IRQ lines. (This is ONLY used for the idle current measurement by the factory mode.)
 * @mask: pointer to struct mtk_irq_mask for storing the original mask value.
 * Return 0 for success; return negative values for failure.
 */
int mt6573_irq_mask_all(struct mtk_irq_mask *mask)
{
    spinlock_t lock;
    unsigned long flags;

    if (mask) {
        spin_lock_irqsave(&lock, flags);

        mask->mask0 = readl(IRQ_MASK0);
        mask->mask1 = readl(IRQ_MASK1);
        mask->mask2 = readl(IRQ_MASK2);
        mask->mask3 = readl(IRQ_MASK3);
        mask->mask4 = readl(IRQ_MASK4);

        writel(0xFFFFFFFF, IRQ_MASK_SET0);
        writel(0xFFFFFFFF, IRQ_MASK_SET1);
        writel(0xFFFFFFFF, IRQ_MASK_SET2);
        writel(0xFFFFFFFF, IRQ_MASK_SET3);
        mt65xx_reg_sync_writel(0xFFFFFFFF, IRQ_MASK_SET4);

        spin_unlock_irqrestore(&lock, flags);

        mask->header = IRQ_MASK_HEADER;
        mask->footer = IRQ_MASK_FOOTER;

        return 0;
    } else {
        return -1;
    }
}

/*
 * mt6573_irq_mask_restore: restore all IRQ lines' masks. (This is ONLY used for the idle current measurement by the factory mode.)
 * @mask: pointer to struct mtk_irq_mask for storing the original mask value.
 * Return 0 for success; return negative values for failure.
 */
int mt6573_irq_mask_restore(struct mtk_irq_mask *mask)
{
    spinlock_t lock;
    unsigned long flags;

    if (!mask) {
        return -1;
    }
    if (mask->header != IRQ_MASK_HEADER) {
        return -1;
    }
    if (mask->footer != IRQ_MASK_FOOTER) {
        return -1;
    }

    spin_lock_irqsave(&lock, flags);

    writel(~(mask->mask0), IRQ_MASK_CLR0);
    writel(~(mask->mask1), IRQ_MASK_CLR1);
    writel(~(mask->mask2), IRQ_MASK_CLR2);
    writel(~(mask->mask3), IRQ_MASK_CLR3);
    mt65xx_reg_sync_writel(~(mask->mask4), IRQ_MASK_CLR4);

    spin_unlock_irqrestore(&lock, flags);

    return 0;
}

static struct irq_chip mt6573_irq_chip = {
    .disable = mt6573_irq_mask,
    .enable = mt6573_irq_unmask,
    .ack = mt6573_irq_ack,
    .mask = mt6573_irq_mask,
    .unmask = mt6573_irq_unmask,
    .set_type = mt6573_irq_set_type,
};

void __init mt6573_init_irq(void)
{
    unsigned int irq;

    for (irq = 0; irq < NR_MT6573_IRQ_LINE; irq++) {
        set_irq_chip(irq, &mt6573_irq_chip);
        set_irq_handler(irq, handle_level_irq);
        set_irq_flags(irq, IRQF_VALID | IRQF_PROBE);
    }
}

