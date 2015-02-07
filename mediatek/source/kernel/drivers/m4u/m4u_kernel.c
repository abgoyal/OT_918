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

#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/earlysuspend.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/dma-mapping.h>
#include <linux/slab.h>
#include <linux/aee.h>
#include <linux/timer.h>
#include <linux/cache.h>


// for error msg, high priority
#define MT6573M4U_MSG
#ifdef MT6573M4U_MSG
#define M4UMSG(string, args...) printk("[M4U_K][pid=%d]"string,current->tgid,##args)
#else
#define M4UMSG(string, args...)
#endif

// serious error, will cause red screen and save log in sdcard/aee_exp/db.xx
#define M4UERR(string, args...) do { \
	printk("[M4U_K] error_assert_fail "string,##args); \
  aee_kernel_exception("M4U", "[M4U_K] error:"string,##args); \
}while(0)


unsigned long m4u_virt_to_phys(void *v)
{
    return virt_to_phys(v);
}
EXPORT_SYMBOL(m4u_virt_to_phys);

struct page* m4u_pfn_to_page(unsigned int pfn)
{
    return pfn_to_page(pfn);
}
EXPORT_SYMBOL(m4u_pfn_to_page);

unsigned int m4u_page_to_phys(struct page* pPage)
{
    return page_to_phys(pPage);
}
EXPORT_SYMBOL(m4u_page_to_phys);

unsigned int m4u_user_v2p(unsigned int va)
{
    unsigned int pageOffset = (va & (PAGE_SIZE - 1));
    pgd_t *pgd;
    pmd_t *pmd;
    pte_t *pte;
    unsigned int pa;

    if( (!current)||(!(current->mm)))
    {
        M4UMSG("error in m4u_user_v2p: current=%d or current->mm is zero\n", current);
        return 0;
    }
    
    pgd = pgd_offset(current->mm, va); /* what is tsk->mm */
    if(pgd_none(*pgd)||pgd_bad(*pgd))
    {
        M4UMSG("warning: m4u_user_v2p(), va=0x%x, pgd invalid! \n", va);
        return 0;
    }
    
    pmd = pmd_offset(pgd, va);
    if(pmd_none(*pmd)||pmd_bad(*pmd))
    {
        M4UMSG("warning: m4u_user_v2p(), va=0x%x, pmd invalid! \n", va);
        return 0;
    }
        
    pte = pte_offset_map(pmd, va);
    if(pte_present(*pte)) 
    { 
        pa=(pte_val(*pte) & (PAGE_MASK)) | pageOffset; 
        return pa; 
    }     

    return 0;
}

EXPORT_SYMBOL(m4u_user_v2p);



