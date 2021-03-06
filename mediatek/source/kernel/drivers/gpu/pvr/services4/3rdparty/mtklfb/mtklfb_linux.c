/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
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

/**********************************************************************
 *
 * Copyright(c) 2008 Imagination Technologies Ltd. All rights reserved.
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope it will be useful but, except 
 * as otherwise stated in writing, without any warranty; without even the 
 * implied warranty of merchantability or fitness for a particular purpose. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 * Contact Information:
 * Imagination Technologies Ltd. <gpl-support@imgtec.com>
 * Home Park Estate, Kings Langley, Herts, WD4 8LZ, UK 
 *
 ******************************************************************************/

#ifndef AUTOCONF_INCLUDED
#include <linux/config.h>
#endif

#include <linux/version.h>

#include <asm/atomic.h>

#if defined(SUPPORT_DRI_DRM)
#include <drm/drmP.h>
#else
#include <linux/module.h>
#endif

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/hardirq.h>
#include <linux/mutex.h>
#include <linux/workqueue.h>
#include <linux/fb.h>
#include <linux/console.h>
#include <linux/mutex.h>

//#include <mach/vrfb.h>

#if defined(DEBUG)
#define	PVR_DEBUG DEBUG
#undef DEBUG
#endif
#if defined(DEBUG)
#undef DEBUG
#endif
#if defined(PVR_DEBUG)
#define	DEBUG PVR_DEBUG
#undef PVR_DEBUG
#endif

#include "img_defs.h"
#include "servicesext.h"
#include "kerneldisplay.h"
#include "mtklfb.h"
#include "pvrmodule.h"
#if defined(SUPPORT_DRI_DRM)
#include "pvr_drm.h"
#include "3rdparty_dc_drm_shared.h"
#endif

#if !defined(PVR_LINUX_USING_WORKQUEUES)
#error "PVR_LINUX_USING_WORKQUEUES must be defined"
#endif

MODULE_SUPPORTED_DEVICE(DEVNAME);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
//#define MTK_DSS_DRIVER(drv, dev) struct omap_dss_driver *drv = (dev) != NULL ? (dev)->driver : NULL
//#define MTK_DSS_MANAGER(man, dev) struct omap_overlay_manager *man = (dev) != NULL ? (dev)->manager : NULL
#define	WAIT_FOR_VSYNC(man)	((man)->wait_for_vsync)
#else
//#define MTK_DSS_DRIVER(drv, dev) struct omap_dss_device *drv = (dev)
//#define MTK_DSS_MANAGER(man, dev) struct omap_dss_device *man = (dev)
#define	WAIT_FOR_VSYNC(man)	((man)->wait_vsync)
#endif

void *MTKLFBAllocKernelMem(unsigned long ulSize)
{
	return kmalloc(ulSize, GFP_KERNEL);
}

void MTKLFBFreeKernelMem(void *pvMem)
{
	kfree(pvMem);
}

void MTKLFBCreateSwapChainLockInit(MTKLFB_DEVINFO *psDevInfo)
{
	mutex_init(&psDevInfo->sCreateSwapChainMutex);
}

void MTKLFBCreateSwapChainLockDeInit(MTKLFB_DEVINFO *psDevInfo)
{
	mutex_destroy(&psDevInfo->sCreateSwapChainMutex);
}

void MTKLFBCreateSwapChainLock(MTKLFB_DEVINFO *psDevInfo)
{
	mutex_lock(&psDevInfo->sCreateSwapChainMutex);
}

void MTKLFBCreateSwapChainUnLock(MTKLFB_DEVINFO *psDevInfo)
{
	mutex_unlock(&psDevInfo->sCreateSwapChainMutex);
}

void MTKLFBAtomicBoolInit(MTKLFB_ATOMIC_BOOL *psAtomic, MTKLFB_BOOL bVal)
{
	atomic_set(psAtomic, (int)bVal);
}

void MTKLFBAtomicBoolDeInit(MTKLFB_ATOMIC_BOOL *psAtomic)
{
}

void MTKLFBAtomicBoolSet(MTKLFB_ATOMIC_BOOL *psAtomic, MTKLFB_BOOL bVal)
{
	atomic_set(psAtomic, (int)bVal);
}

MTKLFB_BOOL MTKLFBAtomicBoolRead(MTKLFB_ATOMIC_BOOL *psAtomic)
{
	return (MTKLFB_BOOL)atomic_read(psAtomic);
}

void MTKLFBAtomicIntInit(MTKLFB_ATOMIC_INT *psAtomic, int iVal)
{
	atomic_set(psAtomic, iVal);
}

void MTKLFBAtomicIntDeInit(MTKLFB_ATOMIC_INT *psAtomic)
{
}

void MTKLFBAtomicIntSet(MTKLFB_ATOMIC_INT *psAtomic, int iVal)
{
	atomic_set(psAtomic, iVal);
}

int MTKLFBAtomicIntRead(MTKLFB_ATOMIC_INT *psAtomic)
{
	return atomic_read(psAtomic);
}

void MTKLFBAtomicIntInc(MTKLFB_ATOMIC_INT *psAtomic)
{
	atomic_inc(psAtomic);
}

MTKLFB_ERROR MTKLFBGetLibFuncAddr (char *szFunctionName, PFN_DC_GET_PVRJTABLE *ppfnFuncTable)
{
	if(strcmp("PVRGetDisplayClassJTable", szFunctionName) != 0)
	{
		return (MTKLFB_ERROR_INVALID_PARAMS);
	}

	
	*ppfnFuncTable = PVRGetDisplayClassJTable;

	return (MTKLFB_OK);
}

void MTKLFBQueueBufferForSwap(MTKLFB_SWAPCHAIN *psSwapChain, MTKLFB_BUFFER *psBuffer)
{
	int res = queue_work(psSwapChain->psWorkQueue, &psBuffer->sWork);

	if (res == 0)
	{
		printk(KERN_WARNING DRIVER_PREFIX ": %s: Device %u: Buffer already on work queue\n", __FUNCTION__, psSwapChain->uiFBDevID);
	}
}

static void WorkQueueHandler(struct work_struct *psWork)
{
	MTKLFB_BUFFER *psBuffer = container_of(psWork, MTKLFB_BUFFER, sWork);

	MTKLFBSwapHandler(psBuffer);
}

MTKLFB_ERROR MTKLFBCreateSwapQueue(MTKLFB_SWAPCHAIN *psSwapChain)
{
	
	psSwapChain->psWorkQueue = __create_workqueue(DEVNAME, 1, 1, 1);
	if (psSwapChain->psWorkQueue == NULL)
	{
		printk(KERN_WARNING DRIVER_PREFIX ": %s: Device %u: create_singlethreaded_workqueue failed\n", __FUNCTION__, psSwapChain->uiFBDevID);

		return (MTKLFB_ERROR_INIT_FAILURE);
	}

	return (MTKLFB_OK);
}

void MTKLFBInitBufferForSwap(MTKLFB_BUFFER *psBuffer)
{
	INIT_WORK(&psBuffer->sWork, WorkQueueHandler);
}

void MTKLFBDestroySwapQueue(MTKLFB_SWAPCHAIN *psSwapChain)
{
	destroy_workqueue(psSwapChain->psWorkQueue);
}

void MTKLFBFlip(MTKLFB_DEVINFO *psDevInfo, MTKLFB_BUFFER *psBuffer)
{
	struct fb_var_screeninfo sFBVar;
	int res;
	unsigned long ulYResVirtual;

	acquire_console_sem();

	sFBVar = psDevInfo->psLINFBInfo->var;

	sFBVar.xoffset = 0;
	sFBVar.yoffset = psBuffer->ulYOffset;

	ulYResVirtual = psBuffer->ulYOffset + sFBVar.yres;

	
	if (sFBVar.xres_virtual != sFBVar.xres || sFBVar.yres_virtual < ulYResVirtual)
	{
		sFBVar.xres_virtual = sFBVar.xres;
		sFBVar.yres_virtual = ulYResVirtual;

		sFBVar.activate = FB_ACTIVATE_NOW | FB_ACTIVATE_FORCE;

		res = fb_set_var(psDevInfo->psLINFBInfo, &sFBVar);
		if (res != 0)
		{
			printk(KERN_INFO DRIVER_PREFIX ": %s: Device %u: fb_set_var failed (Y Offset: %lu, Error: %d)\n", __FUNCTION__, psDevInfo->uiFBDevID, psBuffer->ulYOffset, res);
		}
	}
	else
	{
		res = fb_pan_display(psDevInfo->psLINFBInfo, &sFBVar);
		if (res != 0)
		{
			printk(KERN_INFO DRIVER_PREFIX ": %s: Device %u: fb_pan_display failed (Y Offset: %lu, Error: %d)\n", __FUNCTION__, psDevInfo->uiFBDevID, psBuffer->ulYOffset, res);
		}
	}

	release_console_sem();
}

MTKLFB_UPDATE_MODE MTKLFBGetUpdateMode(MTKLFB_DEVINFO *psDevInfo)
{
/*
	struct omap_dss_device *psDSSDev = fb2display(psDevInfo->psLINFBInfo);
	MTK_DSS_DRIVER(psDSSDrv, psDSSDev);

	enum omap_dss_update_mode eMode;

	if (psDSSDrv == NULL || psDSSDrv->get_update_mode == NULL)
	{
		DEBUG_PRINTK((KERN_INFO DRIVER_PREFIX ": %s: Device %u: Can't get update mode\n", __FUNCTION__, psDevInfo->uiFBDevID));
		return MTKLFB_UPDATE_MODE_UNDEFINED;
	}

	eMode = psDSSDrv->get_update_mode(psDSSDev);
	switch(eMode)
	{
		case MTK_DSS_UPDATE_AUTO:
			return MTKLFB_UPDATE_MODE_AUTO;
		case MTK_DSS_UPDATE_MANUAL:
			return MTKLFB_UPDATE_MODE_MANUAL;
		case MTK_DSS_UPDATE_DISABLED:
			return MTKLFB_UPDATE_MODE_DISABLED;
		default:
			DEBUG_PRINTK((KERN_INFO DRIVER_PREFIX ": %s: Device %u: Unknown update mode (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, eMode));
			break;
	}
*/
	return MTKLFB_UPDATE_MODE_UNDEFINED;
}

MTKLFB_BOOL MTKLFBSetUpdateMode(MTKLFB_DEVINFO *psDevInfo, MTKLFB_UPDATE_MODE eMode)
{
/*
	struct omap_dss_device *psDSSDev = fb2display(psDevInfo->psLINFBInfo);
	MTK_DSS_DRIVER(psDSSDrv, psDSSDev);
	enum omap_dss_update_mode eDSSMode;
	int res;

	if (psDSSDrv == NULL || psDSSDrv->set_update_mode == NULL)
	{
		DEBUG_PRINTK((KERN_INFO DRIVER_PREFIX ": %s: Device %u: Can't set update mode\n", __FUNCTION__, psDevInfo->uiFBDevID));
		return MTKLFB_FALSE;
	}

	switch(eMode)
	{
		case MTKLFB_UPDATE_MODE_AUTO:
			eDSSMode = MTK_DSS_UPDATE_AUTO;
			break;
		case MTKLFB_UPDATE_MODE_MANUAL:
			eDSSMode = MTK_DSS_UPDATE_MANUAL;
			break;
		case MTKLFB_UPDATE_MODE_DISABLED:
			eDSSMode = MTK_DSS_UPDATE_DISABLED;
			break;
		default:
			DEBUG_PRINTK((KERN_INFO DRIVER_PREFIX ": %s: Device %u: Unknown update mode (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, eMode));
			return MTKLFB_FALSE;
	}

	res = psDSSDrv->set_update_mode(psDSSDev, eDSSMode);
	if (res != 0)
	{
		DEBUG_PRINTK((KERN_INFO DRIVER_PREFIX ": %s: Device %u: set_update_mode failed (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, res));
	}

	return (res == 0);
*/
	return MTKLFB_TRUE;
}

MTKLFB_BOOL MTKLFBWaitForVSync(MTKLFB_DEVINFO *psDevInfo)
{
/*
	struct omap_dss_device *psDSSDev = fb2display(psDevInfo->psLINFBInfo);
	MTK_DSS_MANAGER(psDSSMan, psDSSDev);

	if (psDSSMan != NULL && WAIT_FOR_VSYNC(psDSSMan) != NULL)
	{
		int res = WAIT_FOR_VSYNC(psDSSMan)(psDSSMan);
		if (res != 0)
		{
			DEBUG_PRINTK((KERN_INFO DRIVER_PREFIX ": %s: Device %u: Wait for vsync failed (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, res));
			return MTKLFB_FALSE;
		}
	}
*/
	return MTKLFB_TRUE;
}

MTKLFB_BOOL MTKLFBManualSync(MTKLFB_DEVINFO *psDevInfo)
{
/*
	struct omap_dss_device *psDSSDev = fb2display(psDevInfo->psLINFBInfo);
	MTK_DSS_DRIVER(psDSSDrv, psDSSDev);

	if (psDSSDrv != NULL && psDSSDrv->sync != NULL)
	{
		int res = psDSSDrv->sync(psDSSDev);
		if (res != 0)
		{
			printk(KERN_INFO DRIVER_PREFIX ": %s: Device %u: Sync failed (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, res);
			return MTKLFB_FALSE;
		}
	}
*/
	return MTKLFB_TRUE;
}

MTKLFB_BOOL MTKLFBCheckModeAndSync(MTKLFB_DEVINFO *psDevInfo)
{
	MTKLFB_UPDATE_MODE eMode = MTKLFBGetUpdateMode(psDevInfo);

	switch(eMode)
	{
		case MTKLFB_UPDATE_MODE_AUTO:
		case MTKLFB_UPDATE_MODE_MANUAL:
			return MTKLFBManualSync(psDevInfo);
		default:
			break;
	}

	return MTKLFB_TRUE;
}

static int MTKLFBFrameBufferEvents(struct notifier_block *psNotif,
                             unsigned long event, void *data)
{
	MTKLFB_DEVINFO *psDevInfo;
	struct fb_event *psFBEvent = (struct fb_event *)data;
	struct fb_info *psFBInfo = psFBEvent->info;
	MTKLFB_BOOL bBlanked;

	
	if (event != FB_EVENT_BLANK)
	{
		return 0;
	}

	bBlanked = (*(IMG_INT *)psFBEvent->data != 0) ? MTKLFB_TRUE: MTKLFB_FALSE;

	psDevInfo = MTKLFBGetDevInfoPtr(psFBInfo->node);

#if 0
	if (psDevInfo != NULL)
	{
		if (bBlanked)
		{
			DEBUG_PRINTK((KERN_INFO DRIVER_PREFIX ": %s: Device %u: Blank event received\n", __FUNCTION__, psDevInfo->uiFBDevID));
		}
		else
		{
			DEBUG_PRINTK((KERN_INFO DRIVER_PREFIX ": %s: Device %u: Unblank event received\n", __FUNCTION__, psDevInfo->uiFBDevID));
		}
	}
	else
	{
		DEBUG_PRINTK((KERN_INFO DRIVER_PREFIX ": %s: Device %u: Blank/Unblank event for unknown framebuffer\n", __FUNCTION__, psFBInfo->node));
	}
#endif

	if (psDevInfo != NULL)
	{
		MTKLFBAtomicBoolSet(&psDevInfo->sBlanked, bBlanked);
		MTKLFBAtomicIntInc(&psDevInfo->sBlankEvents);
	}

	return 0;
}

MTKLFB_ERROR MTKLFBUnblankDisplay(MTKLFB_DEVINFO *psDevInfo)
{
	int res;

	acquire_console_sem();
	res = fb_blank(psDevInfo->psLINFBInfo, 0);
	release_console_sem();
	if (res != 0 && res != -EINVAL)
	{
		printk(KERN_WARNING DRIVER_PREFIX
			": %s: Device %u: fb_blank failed (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, res);
		return (MTKLFB_ERROR_GENERIC);
	}

	return (MTKLFB_OK);
}

#ifdef CONFIG_HAS_EARLYSUSPEND

static void MTKLFBBlankDisplay(MTKLFB_DEVINFO *psDevInfo)
{
	acquire_console_sem();
	fb_blank(psDevInfo->psLINFBInfo, 1);
	release_console_sem();
}

static void MTKLFBEarlySuspendHandler(struct early_suspend *h)
{
	unsigned uiMaxFBDevIDPlusOne = MTKLFBMaxFBDevIDPlusOne();
	unsigned i;

	for (i=0; i < uiMaxFBDevIDPlusOne; i++)
	{
		MTKLFB_DEVINFO *psDevInfo = MTKLFBGetDevInfoPtr(i);

		if (psDevInfo != NULL)
		{
			MTKLFBAtomicBoolSet(&psDevInfo->sEarlySuspendFlag, MTKLFB_TRUE);
			MTKLFBBlankDisplay(psDevInfo);
		}
	}
}

static void MTKLFBEarlyResumeHandler(struct early_suspend *h)
{
	unsigned uiMaxFBDevIDPlusOne = MTKLFBMaxFBDevIDPlusOne();
	unsigned i;

	for (i=0; i < uiMaxFBDevIDPlusOne; i++)
	{
		MTKLFB_DEVINFO *psDevInfo = MTKLFBGetDevInfoPtr(i);

		if (psDevInfo != NULL)
		{
			MTKLFBUnblankDisplay(psDevInfo);
			MTKLFBAtomicBoolSet(&psDevInfo->sEarlySuspendFlag, MTKLFB_FALSE);
		}
	}
}

#endif 

MTKLFB_ERROR MTKLFBEnableLFBEventNotification(MTKLFB_DEVINFO *psDevInfo)
{
	int                res;
	MTKLFB_ERROR         eError;

	
	memset(&psDevInfo->sLINNotifBlock, 0, sizeof(psDevInfo->sLINNotifBlock));

	psDevInfo->sLINNotifBlock.notifier_call = MTKLFBFrameBufferEvents;

	MTKLFBAtomicBoolSet(&psDevInfo->sBlanked, MTKLFB_FALSE);
	MTKLFBAtomicIntSet(&psDevInfo->sBlankEvents, 0);

	res = fb_register_client(&psDevInfo->sLINNotifBlock);
	if (res != 0)
	{
		printk(KERN_WARNING DRIVER_PREFIX
			": %s: Device %u: fb_register_client failed (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, res);

		return (MTKLFB_ERROR_GENERIC);
	}

	eError = MTKLFBUnblankDisplay(psDevInfo);
	if (eError != MTKLFB_OK)
	{
		printk(KERN_WARNING DRIVER_PREFIX
			": %s: Device %u: UnblankDisplay failed (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, eError);
		return eError;
	}

#ifdef CONFIG_HAS_EARLYSUSPEND
	psDevInfo->sEarlySuspend.suspend = MTKLFBEarlySuspendHandler;
	psDevInfo->sEarlySuspend.resume = MTKLFBEarlyResumeHandler;
	psDevInfo->sEarlySuspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN;
	register_early_suspend(&psDevInfo->sEarlySuspend);
#endif

	return (MTKLFB_OK);
}

MTKLFB_ERROR MTKLFBDisableLFBEventNotification(MTKLFB_DEVINFO *psDevInfo)
{
	int res;

#ifdef CONFIG_HAS_EARLYSUSPEND
	unregister_early_suspend(&psDevInfo->sEarlySuspend);
#endif

	
	res = fb_unregister_client(&psDevInfo->sLINNotifBlock);
	if (res != 0)
	{
		printk(KERN_WARNING DRIVER_PREFIX
			": %s: Device %u: fb_unregister_client failed (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, res);
		return (MTKLFB_ERROR_GENERIC);
	}

	MTKLFBAtomicBoolSet(&psDevInfo->sBlanked, MTKLFB_FALSE);

	return (MTKLFB_OK);
}

#if defined(SUPPORT_DRI_DRM) && defined(PVR_DISPLAY_CONTROLLER_DRM_IOCTL)
static MTKLFB_DEVINFO *MTKLFBPVRDevIDToDevInfo(unsigned uiPVRDevID)
{
	unsigned uiMaxFBDevIDPlusOne = MTKLFBMaxFBDevIDPlusOne();
	unsigned i;

	for (i=0; i < uiMaxFBDevIDPlusOne; i++)
	{
		MTKLFB_DEVINFO *psDevInfo = MTKLFBGetDevInfoPtr(i);

		if (psDevInfo->uiPVRDevID == uiPVRDevID)
		{
			return psDevInfo;
		}
	}

	printk(KERN_WARNING DRIVER_PREFIX
		": %s: PVR Device %u: Couldn't find device\n", __FUNCTION__, uiPVRDevID);

	return NULL;
}

int PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _Ioctl)(struct drm_device unref__ *dev, void *arg, struct drm_file unref__ *pFile)
{
	uint32_t *puiArgs;
	uint32_t uiCmd;
	unsigned uiPVRDevID;
	int ret = 0;
	MTKLFB_DEVINFO *psDevInfo;

	if (arg == NULL)
	{
		return -EFAULT;
	}

	puiArgs = (uint32_t *)arg;
	uiCmd = puiArgs[PVR_DRM_DISP_ARG_CMD];
	uiPVRDevID = puiArgs[PVR_DRM_DISP_ARG_DEV];

	psDevInfo = MTKLFBPVRDevIDToDevInfo(uiPVRDevID);
	if (psDevInfo == NULL)
	{
		return -EINVAL;
	}


	switch (uiCmd)
	{
		case PVR_DRM_DISP_CMD_LEAVE_VT:
		case PVR_DRM_DISP_CMD_ENTER_VT:
		{
			MTKLFB_BOOL bLeaveVT = (uiCmd == PVR_DRM_DISP_CMD_LEAVE_VT);
			DEBUG_PRINTK((KERN_WARNING DRIVER_PREFIX ": %s: PVR Device %u: %s\n",
				__FUNCTION__, uiPVRDevID,
				bLeaveVT ? "Leave VT" : "Enter VT"));

			MTKLFBCreateSwapChainLock(psDevInfo);
			
			MTKLFBAtomicBoolSet(&psDevInfo->sLeaveVT, bLeaveVT);
			if (psDevInfo->psSwapChain != NULL)
			{
				flush_workqueue(psDevInfo->psSwapChain->psWorkQueue);

				if (bLeaveVT)
				{
					MTKLFBFlip(psDevInfo, &psDevInfo->sSystemBuffer);
					(void) MTKLFBCheckModeAndSync(psDevInfo);
				}
			}

			MTKLFBCreateSwapChainUnLock(psDevInfo);
			(void) MTKLFBUnblankDisplay(psDevInfo);
			break;
		}
		case PVR_DRM_DISP_CMD_ON:
		case PVR_DRM_DISP_CMD_STANDBY:
		case PVR_DRM_DISP_CMD_SUSPEND:
		case PVR_DRM_DISP_CMD_OFF:
		{
			int iFBMode;
#if defined(DEBUG)
			{
				const char *pszMode;
				switch(uiCmd)
				{
					case PVR_DRM_DISP_CMD_ON:
						pszMode = "On";
						break;
					case PVR_DRM_DISP_CMD_STANDBY:
						pszMode = "Standby";
						break;
					case PVR_DRM_DISP_CMD_SUSPEND:
						pszMode = "Suspend";
						break;
					case PVR_DRM_DISP_CMD_OFF:
						pszMode = "Off";
						break;
					default:
						pszMode = "(Unknown Mode)";
						break;
				}
				printk (KERN_WARNING DRIVER_PREFIX ": %s: PVR Device %u: Display %s\n",
				__FUNCTION__, uiPVRDevID, pszMode);
			}
#endif
			switch(uiCmd)
			{
				case PVR_DRM_DISP_CMD_ON:
					iFBMode = FB_BLANK_UNBLANK;
					break;
				case PVR_DRM_DISP_CMD_STANDBY:
					iFBMode = FB_BLANK_HSYNC_SUSPEND;
					break;
				case PVR_DRM_DISP_CMD_SUSPEND:
					iFBMode = FB_BLANK_VSYNC_SUSPEND;
					break;
				case PVR_DRM_DISP_CMD_OFF:
					iFBMode = FB_BLANK_POWERDOWN;
					break;
				default:
					return -EINVAL;
			}

			MTKLFBCreateSwapChainLock(psDevInfo);

			if (psDevInfo->psSwapChain != NULL)
			{
				flush_workqueue(psDevInfo->psSwapChain->psWorkQueue);
			}

			acquire_console_sem();
			ret = fb_blank(psDevInfo->psLINFBInfo, iFBMode);
			release_console_sem();

			MTKLFBCreateSwapChainUnLock(psDevInfo);

			break;
		}
		default:
		{
			ret = -EINVAL;
			break;
		}
	}

	return ret;
}
#endif

#if defined(SUPPORT_DRI_DRM)
int PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _Init)(struct drm_device unref__ *dev)
#else
static int __init MTKLFB_Init(void)
#endif
{

	if(MTKLFBInit() != MTKLFB_OK)
	{
		printk(KERN_WARNING DRIVER_PREFIX ": %s: MTKLFBInit failed\n", __FUNCTION__);
		return -ENODEV;
	}

	return 0;

}

#if defined(SUPPORT_DRI_DRM)
void PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _Cleanup)(struct drm_device unref__ *dev)
#else
static void __exit MTKLFB_Cleanup(void)
#endif
{    
	if(MTKLFBDeInit() != MTKLFB_OK)
	{
		printk(KERN_WARNING DRIVER_PREFIX ": %s: MTKLFBDeInit failed\n", __FUNCTION__);
	}
}

#if !defined(SUPPORT_DRI_DRM)
late_initcall(MTKLFB_Init);
module_exit(MTKLFB_Cleanup);
#endif
