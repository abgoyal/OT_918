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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/time.h>
#include "kd_flashlight.h"
#include <asm/io.h>
#include <asm/uaccess.h>
#include "kd_camera_hw.h"

//s_add new flashlight driver here
//export funtions
MUINT32 defaultFlashlightInit(PFLASHLIGHT_FUNCTION_STRUCT *pfFunc);
MUINT32 dummyFlashlightInit(PFLASHLIGHT_FUNCTION_STRUCT *pfFunc);
MUINT32 peakFlashlightInit(PFLASHLIGHT_FUNCTION_STRUCT *pfFunc);
MUINT32 torchFlashlightInit(PFLASHLIGHT_FUNCTION_STRUCT *pfFunc);
MUINT32 constantFlashlightInit(PFLASHLIGHT_FUNCTION_STRUCT *pfFunc);


KD_FLASHLIGHT_INIT_FUNCTION_STRUCT kdFlashlightList[] =
{
    {KD_DEFAULT_FLASHLIGHT_ID, defaultFlashlightInit},
#if defined(DUMMY_FLASHLIGHT)
	{KD_DUMMY_FLASHLIGHT_ID, dummyFlashlightInit},
#endif
#if defined(PEAK_FLASHLIGHT)
	{KD_PEAK_FLASHLIGHT_ID, peakFlashlightInit},
#endif
#if defined(TORCH_FLASHLIGHT)
	{KD_TORCH_FLASHLIGHT_ID, torchFlashlightInit},
#endif
#if defined(CONSTANT_FLASHLIGHT)
	{KD_CONSTANT_FLASHLIGHT_ID, constantFlashlightInit},
#endif


/*  ADD flashlight driver before this line */
    {0,NULL}, //end of list
};
//e_add new flashlight driver here
/******************************************************************************
 * Definition
******************************************************************************/
#ifndef TRUE
#define TRUE KAL_TRUE
#endif
#ifndef FALSE
#define FALSE KAL_FALSE
#endif

/* device name and major number */
#define FLASHLIGHT_DEVNAME            "kd_camera_flashlight"

#define DELAY_MS(ms) {mdelay(ms);}//unit: ms(10^-3)
#define DELAY_US(us) {mdelay(us);}//unit: us(10^-6)
#define DELAY_NS(ns) {mdelay(ns);}//unit: ns(10^-9)
/*
    non-busy dealy(/kernel/timer.c)(CANNOT be used in interrupt context):
        ssleep(sec)
        msleep(msec)
        msleep_interruptible(msec)

    kernel timer


*/
/******************************************************************************
 * Debug configuration
******************************************************************************/
#define PFX "[KD_CAMERA_FLASHLIGHT]"
#define PK_DBG_NONE(fmt, arg...)    do {} while (0)
#define PK_DBG_FUNC(fmt, arg...)    printk(KERN_INFO PFX "%s: " fmt, __FUNCTION__ ,##arg)

#define PK_WARN(fmt, arg...)        printk(KERN_WARNING PFX "%s: " fmt, __FUNCTION__ ,##arg)
#define PK_NOTICE(fmt, arg...)      printk(KERN_NOTICE PFX "%s: " fmt, __FUNCTION__ ,##arg)
#define PK_INFO(fmt, arg...)        printk(KERN_INFO PFX "%s: " fmt, __FUNCTION__ ,##arg)
#define PK_TRC_FUNC(f)              printk(PFX "<%s>\n", __FUNCTION__);
#define PK_TRC_VERBOSE(fmt, arg...) printk(PFX fmt, ##arg)

#define DEBUG_KD_CAMERA_FLASHLIGHT
#ifdef DEBUG_KD_CAMERA_FLASHLIGHT
#define PK_DBG PK_DBG_FUNC
#define PK_TRC PK_DBG_NONE //PK_TRC_FUNC
#define PK_VER PK_DBG_NONE //PK_TRC_VERBOSE
#define PK_ERR(fmt, arg...)         printk(KERN_ERR PFX "%s: " fmt, __FUNCTION__ ,##arg)
#else
#define PK_DBG(a,...)
#define PK_TRC(a,...)
#define PK_VER(a,...)
#define PK_ERR(a,...)
#endif
/*****************************************************************************

*****************************************************************************/
static FLASHLIGHT_FUNCTION_STRUCT *g_pFlashlightFunc = NULL;
/*****************************************************************************

*****************************************************************************/
MINT32 default_flashlight_open(void *pArg) {
    PK_DBG("[default_flashlight_open] E\n");
    return 0;
}
MINT32 default_flashlight_release(void *pArg) {
    PK_DBG("[default_flashlight_release] E\n");
    return 0;
}
MINT32 default_flashlight_ioctl(MUINT32 cmd, MUINT32 arg) {
    int i4RetValue = 0;
    int iFlashType = (int)FLASHLIGHT_NONE;

    switch(cmd)
    {
        case FLASHLIGHTIOC_G_FLASHTYPE:
            iFlashType = FLASHLIGHT_NONE;
            if(copy_to_user((void __user *) arg , (void*)&iFlashType , _IOC_SIZE(cmd)))
            {
                PK_DBG("[default_flashlight_ioctl] ioctl copy to user failed\n");
                return -EFAULT;
            }
            break;
    	default :
    		PK_DBG("[default_flashlight_ioctl]\n");
    		break;
    }
    return i4RetValue;
}

FLASHLIGHT_FUNCTION_STRUCT	defaultFlashlightFunc=
{
	default_flashlight_open,
	default_flashlight_release,
	default_flashlight_ioctl,
};

UINT32 defaultFlashlightInit(PFLASHLIGHT_FUNCTION_STRUCT *pfFunc) { 
    if (pfFunc!=NULL) {
        *pfFunc=&defaultFlashlightFunc;
    }
    return 0;
}
/*******************************************************************************
* kdSetDriver
********************************************************************************/
int kdSetFlashlightDrv(unsigned int *pFlashlightIdx)
{
unsigned int flashlightIdx = *pFlashlightIdx;
    PK_DBG("[kdSetFlashlightDrv] flashlightIdx: %d \n",flashlightIdx);
    
    if (NULL != kdFlashlightList[flashlightIdx].flashlightInit) {
        kdFlashlightList[flashlightIdx].flashlightInit(&g_pFlashlightFunc);
        if (NULL == g_pFlashlightFunc) {
            PK_DBG("[kdSetFlashlightDrv] flashlightIdx init fail\n");
            if (NULL != kdFlashlightList[KD_DEFAULT_FLASHLIGHT_INDEX].flashlightInit) {
                kdFlashlightList[KD_DEFAULT_FLASHLIGHT_INDEX].flashlightInit(&g_pFlashlightFunc);
                if (NULL == g_pFlashlightFunc) {
                    PK_DBG("[kdSetFlashlightDrv] KD_DEFAULT_FLASHLIGHT_INDEX init fail\n");
                    return -EIO;
                }
            }
        }
    }

    //open flashlight driver
    if (g_pFlashlightFunc) {
       g_pFlashlightFunc->flashlight_open(0);
    }

	return 0;
}
/*****************************************************************************

*****************************************************************************/
static int flashlight_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
    int i4RetValue = 0;

    //PK_DBG("%x, %x \n",cmd,arg);

    switch(cmd)
    {
        case FLASHLIGHTIOC_X_SET_DRIVER:
            i4RetValue = kdSetFlashlightDrv((unsigned int*)&arg);
            break;
    	default :
    	    if (g_pFlashlightFunc) {
    	        i4RetValue = g_pFlashlightFunc->flashlight_ioctl(cmd,arg);
    	    }
    		break;
    }

    return i4RetValue;
}

static int flashlight_open(struct inode *inode, struct file *file)
{
    int i4RetValue = 0;
    PK_DBG("[flashlight_open] E\n");
    return i4RetValue;
}

static int flashlight_release(struct inode *inode, struct file *file)
{
    PK_DBG("[flashlight_release] E\n");

    if (g_pFlashlightFunc) {
        g_pFlashlightFunc->flashlight_release(0);
        g_pFlashlightFunc = NULL;
    }

    return 0;
}

/*****************************************************************************/
/* Kernel interface */
static struct file_operations flashlight_fops = {
    .owner      = THIS_MODULE,
    .ioctl      = flashlight_ioctl,
    .open       = flashlight_open,
    .release    = flashlight_release,
};

/*****************************************************************************
Driver interface
*****************************************************************************/
struct flashlight_data{
    spinlock_t lock;
    wait_queue_head_t read_wait;
    struct semaphore sem;
};
static struct class *flashlight_class = NULL;
static struct device *flashlight_device = NULL;
static struct flashlight_data flashlight_private;
static dev_t flashlight_devno;
static struct cdev flashlight_cdev;
/****************************************************************************/
#define ALLOC_DEVNO
static int flashlight_probe(struct platform_device *dev)
{
    int ret = 0, err = 0;

	PK_DBG("[flashlight_probe] start\n");

#ifdef ALLOC_DEVNO
    ret = alloc_chrdev_region(&flashlight_devno, 0, 1, FLASHLIGHT_DEVNAME);
    if (ret) {
        PK_ERR("[flashlight_probe] alloc_chrdev_region fail: %d\n", ret);
        goto flashlight_probe_error;
    } else {
        PK_DBG("[flashlight_probe] major: %d, minor: %d\n", MAJOR(flashlight_devno), MINOR(flashlight_devno));
    }
    cdev_init(&flashlight_cdev, &flashlight_fops);
    flashlight_cdev.owner = THIS_MODULE;
    err = cdev_add(&flashlight_cdev, flashlight_devno, 1);
    if (err) {
        PK_ERR("[flashlight_probe] cdev_add fail: %d\n", err);
        goto flashlight_probe_error;
    }
#else
    #define FLASHLIGHT_MAJOR 242
    ret = register_chrdev(FLASHLIGHT_MAJOR, FLASHLIGHT_DEVNAME, &flashlight_fops);
    if (ret != 0) {
        PK_ERR("[flashlight_probe] Unable to register chardev on major=%d (%d)\n", FLASHLIGHT_MAJOR, ret);
        return ret;
    }
    flashlight_devno = MKDEV(FLASHLIGHT_MAJOR, 0);
#endif


    flashlight_class = class_create(THIS_MODULE, "flashlightdrv");
    if (IS_ERR(flashlight_class)) {
        PK_ERR("[flashlight_probe] Unable to create class, err = %d\n", (int)PTR_ERR(flashlight_class));
        goto flashlight_probe_error;
    }

    flashlight_device = device_create(flashlight_class, NULL, flashlight_devno, NULL, FLASHLIGHT_DEVNAME);
    if(NULL == flashlight_device){
        PK_ERR("[flashlight_probe] device_create fail\n");
        goto flashlight_probe_error;
    }

    /*initialize members*/
    spin_lock_init(&flashlight_private.lock);
    init_waitqueue_head(&flashlight_private.read_wait);
    init_MUTEX(&flashlight_private.sem);

    PK_DBG("[flashlight_probe] Done\n");
    return 0;

flashlight_probe_error:
#ifdef ALLOC_DEVNO
    if (err == 0)
        cdev_del(&flashlight_cdev);
    if (ret == 0)
        unregister_chrdev_region(flashlight_devno, 1);
#else
    if (ret == 0)
        unregister_chrdev(MAJOR(flashlight_devno), FLASHLIGHT_DEVNAME);
#endif
    return -1;
}

static int flashlight_remove(struct platform_device *dev)
{

    PK_DBG("[flashlight_probe] start\n");

#ifdef ALLOC_DEVNO
    cdev_del(&flashlight_cdev);
    unregister_chrdev_region(flashlight_devno, 1);
#else
    unregister_chrdev(MAJOR(flashlight_devno), FLASHLIGHT_DEVNAME);
#endif
    device_destroy(flashlight_class, flashlight_devno);
    class_destroy(flashlight_class);

    PK_DBG("[flashlight_probe] Done\n");
    return 0;
}


static struct platform_driver flashlight_platform_driver =
{
    .probe      = flashlight_probe,
    .remove     = flashlight_remove,
    .driver     = {
        .name = FLASHLIGHT_DEVNAME,
		.owner	= THIS_MODULE,
    },
};

static struct platform_device flashlight_platform_device = {
    .name = FLASHLIGHT_DEVNAME,
    .id = 0,
    .dev = {
    }
};

static int __init flashlight_init(void)
{
    int ret = 0;
    PK_DBG("[flashlight_probe] start\n");

	ret = platform_device_register (&flashlight_platform_device);
	if (ret) {
        PK_ERR("[flashlight_probe] platform_device_register fail\n");
        return ret;
	}

    ret = platform_driver_register(&flashlight_platform_driver);
	if(ret){
		PK_ERR("[flashlight_probe] platform_driver_register fail\n");
		return ret;
	}

	PK_DBG("[flashlight_probe] done!\n");
    return ret;
}

static void __exit flashlight_exit(void)
{
    PK_DBG("[flashlight_probe] start\n");
    platform_driver_unregister(&flashlight_platform_driver);
    //to flush work queue
    //flush_scheduled_work();
    PK_DBG("[flashlight_probe] done!\n");
}

/*****************************************************************************/
module_init(flashlight_init);
module_exit(flashlight_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jackie Su <jackie.su@mediatek.com>");
MODULE_DESCRIPTION("Flashlight control Driver");


