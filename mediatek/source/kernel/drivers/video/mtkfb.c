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

#include <linux/autoconf.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/fb.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/earlysuspend.h>
#include <linux/kthread.h>
#include <linux/rtpm_prio.h>
#include <linux/vmalloc.h>
#include <linux/disp_assert_layer.h>

#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/mach-types.h>
#include <asm/cacheflush.h>
#include <asm/io.h>

#include <mach/dma.h>
#include <mach/irqs.h>

#if defined(CONFIG_ARCH_MT6516)
    #include <mach/mt6516_typedefs.h>
    #include <mach/mt6516_boot.h>
    #include <mach/mt6516_gpt_sw.h>
#elif defined(CONFIG_ARCH_MT6573)
    #include <mach/mt6573_typedefs.h>
    #include <mach/mt6573_gpt.h>
	#include <mach/mt6573_m4u.h>
#else
    #error "unknown arch"
#endif

#include "debug.h"
#include "disp_drv.h"
#include "dpi_drv.h"
#include "lcd_drv.h"
#if defined (MTK_TVOUT_SUPPORT)
#include "tv_out.h"
#endif

#include "mtkfb.h"
#include "mtkfb_console.h"

#define INIT_FB_AS_COLOR_BAR    (0)

static u32 MTK_FB_XRES  = 0;
static u32 MTK_FB_YRES  = 0;
static u32 MTK_FB_BPP   = 0;
static u32 MTK_FB_PAGES = 0;

#define MTK_FB_XRESV (MTK_FB_XRES)
#define MTK_FB_YRESV (MTK_FB_YRES * MTK_FB_PAGES) /* For page flipping */
#define MTK_FB_BYPP  ((MTK_FB_BPP + 7) >> 3)
#define MTK_FB_LINE  (MTK_FB_XRES * MTK_FB_BYPP)
#define MTK_FB_SIZE  (MTK_FB_LINE * MTK_FB_YRES)

#define MTK_FB_SIZEV (MTK_FB_LINE * MTK_FB_YRESV)

#define CHECK_RET(expr)    \
    do {                   \
        int ret = (expr);  \
        ASSERT(0 == ret);  \
    } while (0)

static size_t mtkfb_log_on = false;
#define MTKFB_LOG(...) \
    do { \
        if (mtkfb_log_on) printk("[mtkfb log]"__VA_ARGS__); \
    }while (0)

#define MTKFB_FUNC()	\
	do { \
		if(mtkfb_log_on) printk("[mtkfb func] %s\n", __func__); \
	}while (0)

void mtkfb_log_enable(bool enable)
{
	printk("mtkfb log %s\n", enable?"enabled":"disabled");
	mtkfb_log_on = enable;
}

// ---------------------------------------------------------------------------
//  local variables
// ---------------------------------------------------------------------------

static XGPT_CONFIG xgpt_cfg =
{
    .num        = XGPT6,
    .mode       = XGPT_ONE_SHOT,
    .clkDiv     = XGPT_CLK_DIV_1,   // 32K Hz
    .bIrqEnable = TRUE,
    .u4Compare  = 0
};
#if defined(MTK_M4U_SUPPORT)
//#undef MTK_M4U_SUPPORT
#endif

#if defined(MTK_M4U_SUPPORT)
static BOOL mtkfb_enable_m4u = FALSE;
static unsigned int fb_va_m4u = 0;
static unsigned int fb_size_m4u = 0;
static unsigned int fb_mva_m4u = 0;

struct fb_overlay_buffer_list{
	struct fb_overlay_buffer_info buffer;
	unsigned int src_mva;
	pid_t pid;
	void* file_addr;
	struct fb_overlay_buffer_list *next;
};

static struct fb_overlay_buffer_list *overlay_buffer_head = NULL;
#endif
//#endif

static const struct timeval FRAME_INTERVAL = {0, 30000};  // 33ms

atomic_t has_pending_update = ATOMIC_INIT(0);
struct fb_overlay_layer video_layerInfo;
/* This mutex is used to prevent tearing due to page flipping when adbd is 
   reading the front buffer
*/
DECLARE_MUTEX(sem_flipping);

DECLARE_MUTEX(sem_early_suspend);
static BOOL is_early_suspended = FALSE;
// ---------------------------------------------------------------------------
//  local function declarations
// ---------------------------------------------------------------------------

static int init_framebuffer(struct fb_info *info);
static int mtkfb_set_overlay_layer(struct fb_info *info,
                                   struct fb_overlay_layer* layerInfo);
static void mtkfb_update_screen_impl(void);
extern int is_pmem_range(unsigned long* base, unsigned long size);

// ---------------------------------------------------------------------------
//  Timer Routines
// ---------------------------------------------------------------------------

static struct task_struct *screen_update_task = NULL;
wait_queue_head_t screen_update_wq;

static int screen_update_kthread(void *data)
{
	struct sched_param param = { .sched_priority = RTPM_PRIO_SCRN_UPDATE };
	sched_setscheduler(current, SCHED_RR, &param);
    
    for( ;; ) {
        wait_event_interruptible(screen_update_wq, atomic_read(&has_pending_update));
		MTKFB_LOG("wq wakeup\n");
        mtkfb_update_screen_impl();

		atomic_set(&has_pending_update,0);
        if (kthread_should_stop())
            break;
    }

    return 0;
}

static void XGPT_ISR(unsigned short input)
{
	MTKFB_LOG("xgpt timer isr\n");
    wake_up_interruptible(&screen_update_wq);
}

// return out = a - b
void timeval_sub(struct timeval *out,
                 const struct timeval *a,
                 const struct timeval *b)
{
    out->tv_sec  = a->tv_sec - b->tv_sec;
    out->tv_usec = a->tv_usec - b->tv_usec;

    if (out->tv_usec < 0) {
        -- out->tv_sec;
        out->tv_usec += 1000000;
    }
}

// return if a > b
static __inline BOOL timeval_larger(const struct timeval *a, 
                                    const struct timeval *b)
{
    if (a->tv_sec > b->tv_sec) return TRUE;
    return (a->tv_usec > b->tv_usec) ? TRUE : FALSE;
}

// convert to 32KHz unit
static __inline time_t convert_to_32K_ticks(const struct timeval *x)
{
    return (x->tv_sec * 32768+ x->tv_usec * 32768/ 1000000);
}


/*
 * ---------------------------------------------------------------------------
 *  mtkfb_set_lcm_inited() will be called in mt6516_board_init()
 * ---------------------------------------------------------------------------
 */
static BOOL is_lcm_inited = FALSE;

void mtkfb_set_lcm_inited(BOOL inited)
{
    is_lcm_inited = inited;
}


/*
 * ---------------------------------------------------------------------------
 * called by M4U driver to init LCD port
 * ---------------------------------------------------------------------------
 */
unsigned int _m4u_lcd_init(void)
{
#if defined(MTK_M4U_SUPPORT)
    printk("[FB driver] call _m4u_lcd_init()\n");
	DISP_AllocUILayerMva(fb_va_m4u, &fb_mva_m4u, fb_size_m4u);
	DISP_SetFrameBufferAddr(fb_mva_m4u);
	DISP_ConfigAssertLayerMva();
	DISP_InitM4U();
	mtkfb_enable_m4u = TRUE;
	printk("[m4u_lcd_init] VA = 0x%x, MVA = 0x%x\n",fb_va_m4u, fb_mva_m4u);
#else
    printk("[FB driver] call _m4u_lcd_init() but this function not implement for MTKFB not use M4U\n");
#endif
	return 0;
}
EXPORT_SYMBOL(_m4u_lcd_init);


/*
 * ---------------------------------------------------------------------------
 * fbdev framework callbacks and the ioctl interface
 * ---------------------------------------------------------------------------
 */
/* Called each time the mtkfb device is opened */
static int mtkfb_open(struct file *file, struct fb_info *info, int user)
{
    NOT_REFERENCED(info);
    NOT_REFERENCED(user);
    
    MSG_FUNC_ENTER();
    MSG_FUNC_LEAVE();
    return 0;
}

#if defined (MTK_M4U_SUPPORT)
static int mtkfb_search_overlayList_ex(struct fb_overlay_buffer_list* head, void* file_addr)
{
    int ret = 0;
	struct fb_overlay_buffer_list *c, *n;
	c = head->next;
	n = head;
//	if(!c) return 0;
	while(c != NULL){
		if(c->file_addr == file_addr){
      
			LCD_WaitForNotBusy();
        	DISP_DeallocMva(c->buffer.src_vir_addr, c->src_mva, c->buffer.size);
			{
				struct fb_overlay_buffer_list *a;
				a = overlay_buffer_head;
				printk("[mtkfb_release] before delete a node,list node Addr:\n");
				
				while(a)
				{
					printk("0x%x,  ", (unsigned int)a);
					a = a->next;
				}
			}
			n->next = c->next;
			vfree(c);
			{
				struct fb_overlay_buffer_list *b;
				b = overlay_buffer_head;
				printk("\n[mtkfb_release] after delete a node,list node Addr:\n");
				while(b)
				{
					printk("0x%x,  ", (unsigned int)b);
					b = b->next;
					printk("\n");
				}
			}
			c = n->next;
			ret = 1;
		}
		else{
			n = c;
			c = c->next;
		}
	}
	return ret;
}
#endif

/* Called when the mtkfb device is closed. We make sure that any pending
 * gfx DMA operations are ended, before we return. */
static int mtkfb_release(struct file *file, struct fb_info *info, int user)
{
	struct mtkfb_device *fbdev = (struct mtkfb_device *)info->par;
    NOT_REFERENCED(info);
    NOT_REFERENCED(user);

#if defined (MTK_M4U_SUPPORT)
	{
		int i;
		if(mtkfb_search_overlayList_ex(overlay_buffer_head, (void*)file)){
			printk("disable all video layer\n");
			for(i = 0;i < VIDEO_LAYER_COUNT+1;i++)
				LCD_LayerEnable(i,0);
		}
		fbdev->layer_enable = 0x10;
	}
#endif

        
	MSG_FUNC_ENTER();
    MSG_FUNC_LEAVE();
    return 0;
}

/* Store a single color palette entry into a pseudo palette or the hardware
 * palette if one is available. For now we support only 16bpp and thus store
 * the entry only to the pseudo palette.
 */
static int mtkfb_setcolreg(u_int regno, u_int red, u_int green,
                           u_int blue, u_int transp,
                           struct fb_info *info)
{
    int r = 0;
    unsigned bpp, m;

    NOT_REFERENCED(transp);

    MSG_FUNC_ENTER();

    bpp = info->var.bits_per_pixel;
    m = 1 << bpp;
    if (regno >= m)
    {
        r = -EINVAL;
        goto exit;
    }

    switch (bpp)
    {
    case 16:
        /* RGB 565 */
        ((u32 *)(info->pseudo_palette))[regno] = 
            ((red & 0xF800) |
            ((green & 0xFC00) >> 5) |
            ((blue & 0xF800) >> 11));
        break;
    case 32:
        /* ARGB8888 */
        ((u32 *)(info->pseudo_palette))[regno] = 
             (0xff000000)           |
            ((red   & 0xFF00) << 8) |
            ((green & 0xFF00)     ) |
            ((blue  & 0xFF00) >> 8);
        break;

    // TODO: RGB888, BGR888, ABGR8888
    
    default:
        ASSERT(0);
    }

exit:
    MSG_FUNC_LEAVE();
    return r;
}


static void mtkfb_update_screen_impl(void)
{
	MTKFB_FUNC();
    DISP_CHECK_RET(DISP_UpdateScreen(0, 0, MTK_FB_XRES, MTK_FB_YRES));
}


static int mtkfb_update_screen(struct fb_info *info)
{
	MTKFB_FUNC();
    if (down_interruptible(&sem_early_suspend)) {
        printk("[FB Driver] can't get semaphore in mtkfb_update_screen()\n");
        return -ERESTARTSYS;
    }

    if (is_early_suspended) goto End;

	if(DISP_IsInOverlayMode())
	{
		if(DISP_IsLCDBusy())
		{
			atomic_set(&has_pending_update,1);
			goto End;
		}
		else
		{
			mtkfb_update_screen_impl();
		}
	}
	else
	{
		mtkfb_update_screen_impl();
	}

End:
    up(&sem_early_suspend);
    return 0;
}

int mtkfb_set_backlight_level(unsigned int level)
{
	MTKFB_FUNC();
	if (down_interruptible(&sem_flipping)) {
        printk("[FB Driver] can't get semaphore in mtkfb_set_backlight_level()\n");
        return -ERESTARTSYS;
    }
	if (down_interruptible(&sem_early_suspend)) {
        printk("[FB Driver] can't get semaphore in mtkfb_set_backlight_level()\n");
        return -ERESTARTSYS;
    }

    if (is_early_suspended) goto End;
	DISP_SetBacklight(level);
End:
    up(&sem_early_suspend);
	up(&sem_flipping);
    return 0;
}
EXPORT_SYMBOL(mtkfb_set_backlight_level);

int mtkfb_set_backlight_pwm(int div)
{
	MTKFB_FUNC();
	if (down_interruptible(&sem_flipping)) {
        printk("[FB Driver] can't get semaphore in mtkfb_set_backlight_pwm()\n");
        return -ERESTARTSYS;
    }
	if (down_interruptible(&sem_early_suspend)) {
        printk("[FB Driver] can't get semaphore in mtkfb_set_backlight_pwm()\n");
        return -ERESTARTSYS;
    }

    if (is_early_suspended) goto End;
	DISP_SetPWM(div);
End:
    up(&sem_early_suspend);
	up(&sem_flipping);
    return 0;
}
EXPORT_SYMBOL(mtkfb_set_backlight_pwm);

int mtkfb_get_backlight_pwm(int div, unsigned int *freq)
{
	DISP_GetPWM(div, freq);
    return 0;
}
EXPORT_SYMBOL(mtkfb_get_backlight_pwm);

static int mtkfb_pan_display_impl(struct fb_var_screeninfo *var, struct fb_info *info)
{
    UINT32 offset;
    UINT32 paStart;
    char *vaStart, *vaEnd;
    int ret = 0;

	MTKFB_FUNC();

    MSG_FUNC_ENTER();

    MSG(ARGU, "xoffset=%u, yoffset=%u, xres=%u, yres=%u, xresv=%u, yresv=%u\n",
        var->xoffset, var->yoffset, 
        info->var.xres, info->var.yres,
        info->var.xres_virtual,
        info->var.yres_virtual);

    if (down_interruptible(&sem_flipping)) {
        printk("[FB Driver] can't get semaphore in mtkfb_pan_display_impl()\n");
        return -ERESTARTSYS;
    }

    info->var.yoffset = var->yoffset;

    offset = var->yoffset * info->fix.line_length;
	paStart = info->fix.smem_start + offset;
#if defined(MTK_M4U_SUPPORT)
    if(mtkfb_enable_m4u){
		paStart = fb_mva_m4u + offset;
	}
#endif
    vaStart = info->screen_base + offset;
    vaEnd   = vaStart + info->var.yres * info->fix.line_length;
//    LCD_WaitForNotBusy();

    DISP_CHECK_RET(DISP_SetFrameBufferAddr(paStart));
/*#if defined(MTK_M4U_SUPPORT)
    if(mtkfb_enable_m4u){
    	ret = mtkfb_update_screen(info);
	}
#else
    ret = mtkfb_update_screen(info);
#endif*/
	ret = mtkfb_update_screen(info);
    up(&sem_flipping);

    return ret;
}


static int mtkfb_pan_display_proxy(struct fb_var_screeninfo *var, struct fb_info *info)
{
    return mtkfb_pan_display_impl(var, info);
}


/* Set fb_info.fix fields and also updates fbdev.
 * When calling this fb_info.var must be set up already.
 */
static void set_fb_fix(struct mtkfb_device *fbdev)
{
    struct fb_info           *fbi   = fbdev->fb_info;
    struct fb_fix_screeninfo *fix   = &fbi->fix;
    struct fb_var_screeninfo *var   = &fbi->var;
    struct fb_ops            *fbops = fbi->fbops;

    strncpy(fix->id, MTKFB_DRIVER, sizeof(fix->id));
    fix->type = FB_TYPE_PACKED_PIXELS;

    switch (var->bits_per_pixel)
    {
    case 16:
    case 24:
    case 32:
        fix->visual = FB_VISUAL_TRUECOLOR;
        break;
    case 1:
    case 2:
    case 4:
    case 8:
        fix->visual = FB_VISUAL_PSEUDOCOLOR;
        break;
    default:
        ASSERT(0);
    }
    
    fix->accel       = FB_ACCEL_NONE;
    fix->line_length = var->xres_virtual * var->bits_per_pixel / 8;
    fix->smem_len    = fbdev->fb_size_in_byte;
    fix->smem_start  = fbdev->fb_pa_base;

    fix->xpanstep = 0;
    fix->ypanstep = 1;

    fbops->fb_fillrect  = cfb_fillrect;
    fbops->fb_copyarea  = cfb_copyarea;
    fbops->fb_imageblit = cfb_imageblit;
}


/* Check values in var, try to adjust them in case of out of bound values if
 * possible, or return error.
 */
static int mtkfb_check_var(struct fb_var_screeninfo *var, struct fb_info *fbi)
{
    unsigned int bpp;
    unsigned long max_frame_size;
    unsigned long line_size;

    struct mtkfb_device *fbdev = (struct mtkfb_device *)fbi->par;

    MSG_FUNC_ENTER();

    MSG(ARGU, "xres=%u, yres=%u, xres_virtual=%u, yres_virtual=%u, "
              "xoffset=%u, yoffset=%u, bits_per_pixel=%u)\n",
        var->xres, var->yres, var->xres_virtual, var->yres_virtual,
        var->xoffset, var->yoffset, var->bits_per_pixel);

    bpp = var->bits_per_pixel;

    if (bpp != 16 && bpp != 24 && bpp != 32) {
        printk("[%s]unsupported bpp: %d", __func__, bpp);
        return -1;
    }

    switch (var->rotate) {
    case 0:
    case 180:
        var->xres = MTK_FB_XRES;
        var->yres = MTK_FB_YRES;
        break;
    case 90:
    case 270:
        var->xres = MTK_FB_YRES;
        var->yres = MTK_FB_XRES;
        break;
    default:
        return -1;
    }

    if (var->xres_virtual < var->xres)
        var->xres_virtual = var->xres;
    if (var->yres_virtual < var->yres)
        var->yres_virtual = var->yres;
    
    max_frame_size = fbdev->fb_size_in_byte;
    line_size = var->xres_virtual * bpp / 8;

    if (line_size * var->yres_virtual > max_frame_size) {
        /* Try to keep yres_virtual first */
        line_size = max_frame_size / var->yres_virtual;
        var->xres_virtual = line_size * 8 / bpp;
        if (var->xres_virtual < var->xres) {
            /* Still doesn't fit. Shrink yres_virtual too */
            var->xres_virtual = var->xres;
            line_size = var->xres * bpp / 8;
            var->yres_virtual = max_frame_size / line_size;
        }
    }
    if (var->xres + var->xoffset > var->xres_virtual)
        var->xoffset = var->xres_virtual - var->xres;
    if (var->yres + var->yoffset > var->yres_virtual)
        var->yoffset = var->yres_virtual - var->yres;

    if (16 == bpp) {
        var->red.offset    = 11;  var->red.length    = 5;
        var->green.offset  =  5;  var->green.length  = 6;
        var->blue.offset   =  0;  var->blue.length   = 5;
        var->transp.offset =  0;  var->transp.length = 0;
    }
    else if (24 == bpp)
    {
        var->red.length = var->green.length = var->blue.length = 8;
        var->transp.length = 0;

        // Check if format is RGB565 or BGR565
        
        ASSERT(8 == var->green.offset);
        ASSERT(16 == var->red.offset + var->blue.offset);
        ASSERT(16 == var->red.offset || 0 == var->red.offset);
    }
    else if (32 == bpp)
    {
        var->red.length = var->green.length = 
        var->blue.length = var->transp.length = 8;

        // Check if format is ARGB565 or ABGR565
        
        ASSERT(8 == var->green.offset && 24 == var->transp.offset);
        ASSERT(16 == var->red.offset + var->blue.offset);
        ASSERT(16 == var->red.offset || 0 == var->red.offset);
    }

    var->red.msb_right = var->green.msb_right = 
    var->blue.msb_right = var->transp.msb_right = 0;

    var->activate = FB_ACTIVATE_NOW;

    var->height    = UINT_MAX;
    var->width     = UINT_MAX;
    var->grayscale = 0;
    var->nonstd    = 0;

    var->pixclock     = UINT_MAX;
    var->left_margin  = UINT_MAX;
    var->right_margin = UINT_MAX;
    var->upper_margin = UINT_MAX;
    var->lower_margin = UINT_MAX;
    var->hsync_len    = UINT_MAX;
    var->vsync_len    = UINT_MAX;

    var->vmode = FB_VMODE_NONINTERLACED;
    var->sync  = 0;

    MSG_FUNC_LEAVE();
    return 0;
}


/* Switch to a new mode. The parameters for it has been check already by
 * mtkfb_check_var.
 */
static int mtkfb_set_par(struct fb_info *fbi)
{
    struct fb_var_screeninfo *var = &fbi->var;
    struct mtkfb_device *fbdev = (struct mtkfb_device *)fbi->par;
    struct fb_overlay_layer fb_layer;
    u32 bpp = var->bits_per_pixel;

    MSG_FUNC_ENTER();

    switch(bpp)
    {
    case 16 :
        fb_layer.src_fmt = MTK_FB_FORMAT_RGB565;
        fb_layer.src_use_color_key = 1;
        break;

    case 24 :
        fb_layer.src_use_color_key = 1;
        fb_layer.src_fmt = (0 == var->blue.offset) ? 
                           MTK_FB_FORMAT_RGB888 :
                           MTK_FB_FORMAT_BGR888;
        break;
        
    case 32 :
        fb_layer.src_use_color_key = 0;
        fb_layer.src_fmt = (0 == var->blue.offset) ? 
                           MTK_FB_FORMAT_ARGB8888 :
                           MTK_FB_FORMAT_ABGR8888;
        break;

    default :
        fb_layer.src_fmt = MTK_FB_FORMAT_UNKNOWN;
        printk("[%s]unsupported bpp: %d", __func__, bpp);
        return -1;
    }

    // If the framebuffer format is NOT changed, nothing to do
    //
    if (fb_layer.src_fmt == fbdev->layer_format[FB_LAYER]) {
        goto Done;
    }

    // else, begin change display mode
    //    
    set_fb_fix(fbdev);

    fb_layer.layer_id = FB_LAYER;
    fb_layer.layer_enable = 1;
    fb_layer.src_base_addr = fbdev->fb_va_base;
    fb_layer.src_phy_addr = (void *)fbdev->fb_pa_base;
    fb_layer.src_direct_link = 0;
    fb_layer.src_offset_x = fb_layer.src_offset_y = 0;
    fb_layer.src_width = fb_layer.tgt_width = fb_layer.src_pitch = var->xres;
    fb_layer.src_height = fb_layer.tgt_height = var->yres;
    fb_layer.tgt_offset_x = fb_layer.tgt_offset_y = 0;

    fb_layer.src_color_key = 0;
    fb_layer.layer_rotation = MTK_FB_ORIENTATION_0;
    
// xuecheng.zhang
// for landsacpe mode, we need to rotate the framebuffer layer
// because there is not any middleware could be used for the UI rotation.
#ifdef MTK_QVGA_LANDSCAPE_SUPPORT 
	if((MTK_LCM_PHYSICAL_ROTATION == 90 || MTK_LCM_PHYSICAL_ROTATION == 270) && 
			(get_boot_mode() == FACTORY_BOOT || get_boot_mode() == RECOVERY_BOOT))
	{
		if(MTK_LCM_PHYSICAL_ROTATION == 90) 
		{
			fb_layer.layer_rotation = MTK_FB_ORIENTATION_270;
		}
		else if(MTK_LCM_PHYSICAL_ROTATION == 270)
		{
			fb_layer.layer_rotation = MTK_FB_ORIENTATION_90;
		}
		else
		{
			printk("ERROR, this should never happen, MTK_LCM_PHYSICAL_ROTATION=%d\n", MTK_LCM_PHYSICAL_ROTATION);
		}
	}
#endif

    mtkfb_set_overlay_layer(fbi, &fb_layer);
    memset(fbi->screen_base, 0, fbi->screen_size);  // clear the whole VRAM as zero

Done:    
    MSG_FUNC_LEAVE();
    return 0;
}


static int mtkfb_soft_cursor(struct fb_info *info, struct fb_cursor *cursor)
{
    NOT_REFERENCED(info);
    NOT_REFERENCED(cursor);
    
    return 0;
}

#if defined (MTK_M4U_SUPPORT)
static struct fb_overlay_buffer_list* mtkfb_search_overlayList(struct fb_overlay_buffer_list* head, unsigned int va)
{
	struct fb_overlay_buffer_list *c;
	c = head->next;
	ASSERT(c);
	while(va != c->buffer.src_vir_addr || c->pid != current->tgid){
		c = c->next;
		if(!c){
			struct fb_overlay_buffer_list *p;
			p = head->next;
			ASSERT(p);
			printk("[FB driver] current va = 0x%x, buffer_list va:\n",va);
			while(p){
				printk("0x%x\n", p->buffer.src_vir_addr);
				p = p->next;
			}
			printk("[FB driver] ERROR: Can't find matched VA in buffer list\n");
		}
		ASSERT(c);
	}
    return c;
}
#else
static unsigned int mtkfb_user_v2p(unsigned int va)
{
    unsigned int pageOffset = (va & (PAGE_SIZE - 1));
    pgd_t *pgd;
    pmd_t *pmd;
    pte_t *pte;
    unsigned int pa;

    pgd = pgd_offset(current->mm, va); /* what is tsk->mm */
    pmd = pmd_offset(pgd, va);
    pte = pte_offset_map(pmd, va);
    
    pa = (pte_val(*pte) & (PAGE_MASK)) | pageOffset;


    return pa;
}
#endif

static int mtkfb_set_overlay_layer(struct fb_info *info, struct fb_overlay_layer* layerInfo)
{
    struct mtkfb_device *fbdev = (struct mtkfb_device *)info->par;

    unsigned int layerpitch;
	unsigned int layerbpp;
    unsigned int u4OvlPhyAddr;
	LCD_LAYER_FORMAT eFormat;
    unsigned int id = layerInfo->layer_id;
    int enable = layerInfo->layer_enable ? 1 : 0;
    int ret = 0;
    
	MTKFB_FUNC();

    if (down_interruptible(&sem_early_suspend)) {
        printk("[FB Driver] can't get semaphore in mtkfb_set_overlay_layer()\n");
        return -ERESTARTSYS;
    }

    /** LCD registers can't be R/W when its clock is gated in early suspend
        mode; power on/off LCD to modify register values before/after func.
    */
    if (is_early_suspended) {
        LCD_CHECK_RET(LCD_PowerOn());
    }

    MTKFB_LOG("[FB Driver] mtkfb_set_overlay_layer():layer id = %u, layer en = %u, src format = %u, direct link: %u, src vir addr = %u, src phy addr = %u, src pitch=%u, src xoff=%u, src yoff=%u, src w=%u, src h=%u\n",
        layerInfo->layer_id,
        layerInfo->layer_enable, 
        layerInfo->src_fmt,
        (unsigned int)(layerInfo->src_direct_link),
        (unsigned int)(layerInfo->src_base_addr),
        (unsigned int)(layerInfo->src_phy_addr),
        layerInfo->src_pitch,
        layerInfo->src_offset_x,
        layerInfo->src_offset_y,
        layerInfo->src_width,
        layerInfo->src_height);
    MTKFB_LOG("[FB Driver] mtkfb_set_overlay_layer():target xoff=%u, target yoff=%u, target w=%u, target h=%u\n",
        layerInfo->tgt_offset_x,
        layerInfo->tgt_offset_y, 
        layerInfo->tgt_width,
        layerInfo->tgt_height);

//    LCD_WaitForNotBusy();

    // Update Layer Enable Bits and Layer Config Dirty Bits

    if ((((fbdev->layer_enable >> id) & 1) ^ enable)) {
        fbdev->layer_enable ^= (1 << id);
        fbdev->layer_config_dirty |= MTKFB_LAYER_ENABLE_DIRTY;
    }

    // Update Layer Format and Layer Config Dirty Bits

    if (fbdev->layer_format[id] != layerInfo->src_fmt) {
        fbdev->layer_format[id] = layerInfo->src_fmt;
        fbdev->layer_config_dirty |= MTKFB_LAYER_FORMAT_DIRTY;
    }

    // Enter Overlay Mode if any layer is enabled except the FB layer

    if (fbdev->layer_enable & ~(1 << FB_LAYER)) {
        if (DISP_STATUS_OK == DISP_EnterOverlayMode()) {
            printk("mtkfb_ioctl(MTKFB_ENABLE_OVERLAY)\n");
        }
    }
    
    if (!enable || !layerInfo->src_direct_link) {
        DISP_DisableDirectLinkMode(id);
    }
	
    // set layer enable
    LCD_CHECK_RET(LCD_LayerEnable(id, enable));

    if (!enable) {
        ret = 0;
        goto LeaveOverlayMode;
    }

    if (layerInfo->src_direct_link) {
        DISP_EnableDirectLinkMode(id);
    }

	switch (layerInfo->src_fmt)
    {
    case MTK_FB_FORMAT_YUV422:
        eFormat = LCD_LAYER_FORMAT_YUYV422;
        layerpitch = 2;
		layerbpp = 24;
        break;
    
    case MTK_FB_FORMAT_RGB565:
        eFormat = LCD_LAYER_FORMAT_RGB565;
        layerpitch = 2;
		layerbpp = 16;
        break;

    case MTK_FB_FORMAT_RGB888:
    case MTK_FB_FORMAT_BGR888:
        eFormat = LCD_LAYER_FORMAT_RGB888;
        layerpitch = 3;
		layerbpp = 24;
        break;

    case MTK_FB_FORMAT_ARGB8888:
    case MTK_FB_FORMAT_ABGR8888:
#if defined(CONFIG_ARCH_MT6516)
        eFormat = LCD_LAYER_FORMAT_ARGB8888;
#else
        /* Since MT6573 LCD controller support pre-multiplied alpha blending,
           SurfaceFlinger is assumed to output pre-multiplied alpha content
           to framebuffer layer
        */
        eFormat = LCD_LAYER_FORMAT_PARGB8888;
#endif
        layerpitch = 4;
		layerbpp = 32;
        break;

    default:
        PRNERR("Invalid color format: 0x%x\n", layerInfo->src_fmt);
        ret = -EFAULT;
        goto LeaveOverlayMode;
    }

#if defined(MTK_M4U_SUPPORT)
	if(FB_LAYER != id){
		struct fb_overlay_buffer_list* searched_node;
		u4OvlPhyAddr = (unsigned int)(layerInfo->src_base_addr);
		if(u4OvlPhyAddr == 0)
		{
			printk("[FB Error]overlay_va should not be 0x00000000\n");
			LCD_CHECK_RET(LCD_LayerEnable(id, 0));
			ret = -EFAULT;
        	goto LeaveOverlayMode;
		}
		searched_node = mtkfb_search_overlayList(overlay_buffer_head, u4OvlPhyAddr);
		LCD_CHECK_RET(LCD_LayerSetAddress(id, searched_node->src_mva));
	}
	else{
		u4OvlPhyAddr = (unsigned int)(layerInfo->src_phy_addr);
		LCD_CHECK_RET(LCD_LayerSetAddress(id, u4OvlPhyAddr));
	}
#else
	if(FB_LAYER == id){
		u4OvlPhyAddr = layerInfo->src_phy_addr;
	}
	else{
		u4OvlPhyAddr = mtkfb_user_v2p(layerInfo->src_base_addr);
		if(u4OvlPhyAddr == 0)
		{
			printk("[FB Error]overlay_va should not be 0x00000000\n");
			LCD_CHECK_RET(LCD_LayerEnable(id, 0));
			ret = -EFAULT;
        	goto LeaveOverlayMode;
		}
		if(!is_pmem_range(u4OvlPhyAddr, layerpitch * layerInfo->src_width * layerInfo->src_height)){
			printk("error: M4U is not supported but non-PMEM is set to video-layer\n");
			ASSERT(0);
		}
	}
	LCD_CHECK_RET(LCD_LayerSetAddress(id, u4OvlPhyAddr));
#endif

    LCD_CHECK_RET(LCD_LayerSetFormat(id, eFormat));

    //set Alpha blending
	if (MTK_FB_FORMAT_ARGB8888 == layerInfo->src_fmt ||
        MTK_FB_FORMAT_ABGR8888 == layerInfo->src_fmt)
    {
        LCD_CHECK_RET(LCD_LayerSetAlphaBlending(id, TRUE, 0xFF));
	} else {
		LCD_CHECK_RET(LCD_LayerSetAlphaBlending(id, FALSE, 0xFF));
	}

    //set src x, y offset
    //mt65616 do not support source x ,y offset
    ASSERT((layerInfo->src_offset_x) == 0);
    ASSERT((layerInfo->src_offset_y) == 0);

    //set src width, src height
    LCD_CHECK_RET(LCD_LayerSetSize(id, layerInfo->src_width, layerInfo->src_height));

    #if defined(CONFIG_ARCH_MT6516)

    //set line pitch.
    //mt6516 hw do not support line pitch    
    ASSERT((layerInfo->src_pitch) == (layerInfo->src_width));
    
    #elif defined(CONFIG_ARCH_MT6573)

	//printk("[mtkfb_set_overlay_layer] id : %d, pitch : %d, width : %d \n", id, layerInfo->src_pitch, layerInfo->src_width);

	if(id < VIDEO_LAYER_COUNT)
		LCD_CHECK_RET(LCD_LayerSetPitch(id, layerInfo->src_pitch*layerpitch));
	else
		LCD_CHECK_RET(LCD_LayerSetPitch(id, layerInfo->src_width*layerpitch));

	{
		bool ditherenabled = false;
		UINT32 ditherbpp = DISP_GetOutputBPPforDithering();
		UINT32 dbr = 0;
		UINT32 dbg = 0;
		UINT32 dbb = 0;

		if(ditherbpp < layerbpp)
		{
			if(ditherbpp == 16)
			{
				if(layerbpp == 18) 
				{
					dbr = 1;
					dbg = 0;
					dbb = 1;
				}
				else if(layerbpp == 24 || layerbpp == 32)
				{
					dbr = 2;
					dbg = 1;
					dbb = 2;
				}
				else
				{
					printk("ERROR, error dithring bpp settings\n");
				}
			}
			else if(ditherbpp == 18)
			{
				if(layerbpp == 24 || layerbpp == 32)
				{
					dbr = 1;
					dbg = 1;
					dbb = 1;
				}
				else
				{
					printk("ERROR, error dithring bpp settings\n");
					ASSERT(0);
				}
			}
            else if(ditherbpp == 24)
            {
                // do nothing here.
            }
			else
			{
				printk("ERROR, error dithering bpp settings, diterbpp = %d\n",ditherbpp);
				ASSERT(0);
			}
			
			ditherenabled = true;
			LCD_CHECK_RET(LCD_LayerEnableDither(id, true));
			LCD_ConfigDither(14, 14, 14, dbr, dbg, dbb);
		}
		else
		{
			// no dithering needed.
		}

		// debug message
        #if 0
		printk("[%s] layer %d, ditherbpp=%d, layerbpp=%d\n", __func__, id, ditherbpp, layerbpp);
		printk("[%s] dithering enabled: %d, dbr=%d, dbg=%d, dbb=%d\n", __func__, ditherenabled, dbr, dbg, dbb);
        #endif
 	}
    #else
        #error "unknown arch"
    #endif   
    

    //set target x, y offset
    LCD_CHECK_RET(LCD_LayerSetOffset(id, layerInfo->tgt_offset_x, layerInfo->tgt_offset_y));

	// xuecheng add, set rotation.
	LCD_CHECK_RET(LCD_LayerSetRotation(id, layerInfo->layer_rotation));

    //set target width, height
    //mt6516: target w/h must = sourc width/height
    ASSERT((layerInfo->src_width) == (layerInfo->tgt_width));
    ASSERT((layerInfo->src_height) == (layerInfo->tgt_height));
    
    //set color key
    LCD_CHECK_RET(LCD_LayerSetSourceColorKey(id, layerInfo->src_use_color_key, layerInfo->src_color_key));

    //data transferring is triggerred in MTKFB_TRIG_OVERLAY_OUT

	// force writing cached data into dram
#if 0
	dmac_clean_range(layerInfo->src_base_addr, 
                     layerInfo->src_base_addr + 
                     (layerInfo->src_pitch * layerInfo->src_height *
                     GET_MTK_FB_FORMAT_BPP(layerInfo->src_fmt)));
#endif
LeaveOverlayMode:
    // Leave Overlay Mode if only FB layer is enabled

    if ((fbdev->layer_enable & ~(1 << FB_LAYER)) == 0) {
        if (DISP_STATUS_OK == DISP_LeaveOverlayMode()) {
            printk("mtkfb_ioctl(MTKFB_DISABLE_OVERLAY)\n");
        }
    }
 
    if (is_early_suspended) {
        LCD_CHECK_RET(LCD_PowerOff());
    }

    up(&sem_early_suspend);

    MSG_FUNC_LEAVE();

    return ret;
}

static int mtkfb_get_video_layer(struct fb_info *info, struct fb_overlay_layer *layerInfo)
{
	struct mtkfb_device *fbdev = (struct mtkfb_device *)info->par;
    int ret = 0;
	unsigned int id = 2;  //layer 2 is video layer
	MTKFB_FUNC();
    if(LCD_STATUS_OK != LCD_Capture_VideoLayer_Query()){
	    printk("[FB Driver] capture video layer not support\n");
		return -1;
	}
	layerInfo->layer_id = id; //layer_2 is video layer
    layerInfo->layer_enable = (fbdev->layer_enable >> id) & 1;

    if(layerInfo->layer_enable == 0){
	    printk("[FB Driver] Video Layer not enable when mtkfb_get_video_layer()\n");
		return -1;
	}

	if (down_interruptible(&sem_early_suspend)) {
        printk("[FB Driver] can't get semaphore in mtkfb_capture_framebuffer()\n");
        return -ERESTARTSYS;
    }
    if (is_early_suspended) {
//        LCD_CHECK_RET(LCD_PowerOn());
          up(&sem_early_suspend);
          return -1;
    }

    LCD_Get_VideoLayerSize(id, &layerInfo->src_width, &layerInfo->src_height);

    up(&sem_early_suspend);

    MSG_FUNC_LEAVE();

    return ret;
}

static int mtkfb_capture_videobuffer(struct fb_info *info, unsigned int pvbuf)
{
    int ret = 0;

    MTKFB_FUNC();

	if(LCD_STATUS_OK != LCD_Capture_VideoLayer_Query()){
	    printk("[FB Driver] capture video layer not support\n");
		return -1;
	}

    if(0 == video_layerInfo.layer_enable){// video layer not enable
	    printk("[FB Driver] Video Layer not enable when mtkfb_capture_videobuffer()\n");
		return -1;
	}

    if (down_interruptible(&sem_early_suspend)) {
        printk("[FB Driver] can't get semaphore in mtkfb_capture_framebuffer()\n");
        return -ERESTARTSYS;
    }

    /** LCD registers can't be R/W when its clock is gated in early suspend
        mode; power on/off LCD to modify register values before/after func.
    */
    if (is_early_suspended) {
//        LCD_CHECK_RET(LCD_PowerOn());
          up(&sem_early_suspend);
          return -1;
    }

    DISP_Capture_Videobuffer(pvbuf, info->var.bits_per_pixel);
        
    up(&sem_early_suspend);

    MSG_FUNC_LEAVE();

    return ret;    
}
#if defined(MTK_TVOUT_SUPPORT)
extern bool capture_tv_buffer;
#endif


static int mtkfb_capture_framebuffer(struct fb_info *info, unsigned int pvbuf)
{
    int ret = 0;

    MTKFB_FUNC();

    if (down_interruptible(&sem_early_suspend)) {
        printk("[FB Driver] can't get semaphore in mtkfb_capture_framebuffer()\n");
        return -ERESTARTSYS;
    }

    /** LCD registers can't be R/W when its clock is gated in early suspend
        mode; power on/off LCD to modify register values before/after func.
    */
    if (is_early_suspended) {
        LCD_CHECK_RET(LCD_PowerOn());
#if defined(MTK_M4U_SUPPORT)
		LCD_M4UPowerOn();
#endif
    }

#if defined (MTK_TVOUT_SUPPORT)
    if (!capture_tv_buffer) 
    {
        DISP_Capture_Framebuffer(pvbuf, info->var.bits_per_pixel);
    }
    else
    {
        TVOUT_Capture_Tvrotbuffer(pvbuf, info->var.bits_per_pixel);
    }
#else
    DISP_Capture_Framebuffer(pvbuf, info->var.bits_per_pixel);
#endif    

    
    if (is_early_suspended) {
        LCD_CHECK_RET(LCD_PowerOff());
#if defined(MTK_M4U_SUPPORT)
		LCD_M4UPowerOff();
#endif
    }

    up(&sem_early_suspend);

    MSG_FUNC_LEAVE();

    return ret;    
}


static int mtkfb_ioctl(struct file *file, struct fb_info *info, unsigned int cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;
    struct mtkfb_device *fbdev = (struct mtkfb_device *)info->par;
    DISP_STATUS ret;
    int r = 0;
	
	MTKFB_FUNC();

    switch (cmd) {
	case MTKFB_POWEROFF:
   	{ 
    	if (down_interruptible(&sem_early_suspend)) 
		{
        	printk("[FB Driver] can't get semaphore in mtkfb_early_suspend()\n");
        	return -ERESTARTSYS;
    	}

    	is_early_suspended = TRUE;
    
		DISP_CHECK_RET(DISP_PanelEnable(FALSE));
 		DISP_CHECK_RET(DISP_PowerEnable(FALSE));

    	up(&sem_early_suspend);

		return r;
	}

	case MTKFB_POWERON:
   	{
		if (down_interruptible(&sem_early_suspend)) 
		{
        	printk("[FB Driver] can't get semaphore in mtkfb_late_resume()\n");
        	return -ERESTARTSYS;
    	}

    	DISP_CHECK_RET(DISP_PowerEnable(TRUE));
    	DISP_CHECK_RET(DISP_PanelEnable(TRUE));

		is_early_suspended = FALSE;

    	up(&sem_early_suspend);
		
		return r;
	}

    case MTKFB_GETVFRAMEPHYSICAL:
        return copy_to_user(argp, &fbdev->fb_pa_base,
                            sizeof(fbdev->fb_pa_base)) ? -EFAULT : 0;
        
    case MTKFB_CONFIG_IMMEDIATE_UPDATE:
    {
        MTKFB_LOG("[%s] MTKFB_CONFIG_IMMEDIATE_UPDATE, enable = %lu\n",
            __func__, arg);
            
        ret = DISP_ConfigImmediateUpdate((BOOL)arg);

        return (r);
    }
			    
    case MTKFB_CAPTURE_FRAMEBUFFER:
    {
        unsigned int pbuf = 0;
        if (copy_from_user(&pbuf, (void __user *)arg, sizeof(pbuf))) 
        {
            printk("[FB]: copy_from_user failed! line:%d \n", __LINE__);
            r = -EFAULT;
        } 
        else 
        {
            mtkfb_capture_framebuffer(info, pbuf);
        }

        return (r);
    }

#ifdef MTK_FB_OVERLAY_SUPPORT
    case MTKFB_SET_OVERLAY_LAYER:
    {
        struct fb_overlay_layer layerInfo;
        MTKFB_LOG(" mtkfb_ioctl():MTKFB_SET_OVERLAY_LAYER\n");

        if (copy_from_user(&layerInfo, (void __user *)arg, sizeof(layerInfo))) {
            printk("[FB]: copy_from_user failed! line:%d \n", __LINE__);
            r = -EFAULT;
        } else {
            mtkfb_set_overlay_layer(info, &layerInfo);
        }
        return (r);
    }

	case MTKFB_GET_VIDEOLAYER_SIZE:
    {
        MTKFB_LOG(" mtkfb_ioctl():MTKFB_GET_VIDEO_LAYER\n");

        if(mtkfb_get_video_layer(info, &video_layerInfo) < 0) 
		    return -EFAULT;
		if (copy_to_user((void __user *)arg, &video_layerInfo, sizeof(video_layerInfo))){
            printk("[FB]: copy_to_user failed! line:%d \n", __LINE__);
            r = -EFAULT;
        }
        return (r);
    }

	case MTKFB_CAPTURE_VIDEOBUFFER:
    {
        unsigned int pbuf = 0;
		MTKFB_LOG(" mtkfb_ioctl(): MTKFB_CAPTURE_VIDEOBUFFER\n");
        if (copy_from_user(&pbuf, (void __user *)arg, sizeof(pbuf))) 
        {
            printk("[FB]: copy_from_user failed! line:%d \n", __LINE__);
            r = -EFAULT;
        } 
        else 
        {
            if(mtkfb_capture_videobuffer(info, pbuf) < 0)
			    return -EFAULT;
        }

        return (r);
    }

    case MTKFB_SET_VIDEO_LAYERS:
    {
        struct fb_overlay_layer layerInfo[VIDEO_LAYER_COUNT];
        MTKFB_LOG(" mtkfb_ioctl():MTKFB_SET_VIDEO_LAYERS\n");

        if (copy_from_user(&layerInfo, (void __user *)arg, sizeof(layerInfo))) {
            printk("[FB]: copy_from_user failed! line:%d \n", __LINE__);
            r = -EFAULT;
        } else {
            int32_t i;
            for (i = 0; i < VIDEO_LAYER_COUNT; ++i) {
                mtkfb_set_overlay_layer(info, &layerInfo[i]);
            }
        }

        return (r);
    }

    case MTKFB_WAIT_OVERLAY_READY:
        ret = LCD_WaitForNotBusy();
        ASSERT(LCD_STATUS_OK == ret);
        r = 0;
        return (r);

    case MTKFB_GET_OVERLAY_LAYER_COUNT:
    {
        int hw_layer_count = HW_OVERLAY_COUNT; 
        if (copy_to_user((void __user *)arg, &hw_layer_count, sizeof(hw_layer_count)))
        {
            return -EFAULT;
        }
        return 0;
    }

    case MTKFB_TRIG_OVERLAY_OUT:
	{
        MTKFB_LOG(" mtkfb_ioctl():MTKFB_TRIG_OVERLAY_OUT\n");
        return mtkfb_update_screen(info);
	}

	case MTKFB_REGISTER_OVERLAYBUFFER:
    {
		struct fb_overlay_buffer_info overlay_buffer;
		printk("[mtkfb_ioctl]MTKFB_REGISTER_OVERLAYBUFFER\n");
#if defined(MTK_M4U_SUPPORT) 
		if (copy_from_user(&overlay_buffer, (void __user *)arg, sizeof(overlay_buffer))) {
            printk("[FB]: copy_from_user failed! line:%d \n", __LINE__);
            r = -EFAULT;
        }
		else
		{
			struct fb_overlay_buffer_list *c,*n;
			unsigned int overlay_mva;
			if(overlay_buffer.src_vir_addr == 0)
			{
				printk("[mtkfb_ioctl Error]MTKFB_REGISTER_OVERLAYBUFFER VA should not be 0x00000000\n");
				return (r);
			}
			c = overlay_buffer_head;
			{
				struct fb_overlay_buffer_list *a;
				a = overlay_buffer_head;
				printk("[mtkfb_ioctl] before add a node,list node Addr:\n");
				while(a)
				{
					printk("0x%x,  ", (unsigned int)a);
					a = a->next;
				}
			}
			printk("\n[mtkfb_ioctl]MTKFB_REGISTER_OVERLAYBUFFER,va = 0x%x,size = %d\n", overlay_buffer.src_vir_addr, overlay_buffer.size);
			while(c->next)
			{
				c = c->next;
			}
			n = (struct fb_overlay_buffer_list*)vmalloc(sizeof(struct fb_overlay_buffer_list));
			if(!n){
				printk("[mtkfb_ioctl] vmalloc failed\n");
				return -ENOMEM;
			}

			if (down_interruptible(&sem_flipping)) {
    	    	printk("[mtkfb_ioctl] can't get semaphore\n");
        		return -ERESTARTSYS;
   	 		}
			if (down_interruptible(&sem_early_suspend)) {
        		printk("[mtkfb_ioctl] can't get semaphore\n");
        		return -ERESTARTSYS;
    		}

            DISP_AllocOverlayMva(overlay_buffer.src_vir_addr, &overlay_mva, overlay_buffer.size);
			printk("[mtkfb_ioctl]MTKFB_REGISTER_OVERLAYBUFFER,allocated mva = 0x%x\n", overlay_mva);
			n->src_mva = overlay_mva;
			n->buffer.src_vir_addr = overlay_buffer.src_vir_addr;
			n->buffer.size = overlay_buffer.size;
			n->pid = current->tgid;
			n->file_addr = (void*)file;
			printk("[current process ID = %d, current process name:%s]\n", current->tgid, current->comm);
			n->next = NULL;
			c->next = n;
			{
				struct fb_overlay_buffer_list *b;
				b = overlay_buffer_head;
				printk("[mtkfb_ioctl] after add a node,list node Addr:\n");
			
				while(b)
				{
					printk("0x%x,  ", (unsigned int)b);
					b = b->next;
				}
				printk("\n");
			}

 		   	up(&sem_early_suspend);
			up(&sem_flipping);

		}
#else
        printk("[FB]: not enable m4u! line:%d \n", __LINE__);
#endif
		return (r);
    }

	case MTKFB_UNREGISTER_OVERLAYBUFFER:
    {
		unsigned int overlay_bufferVA;
		printk("[mtkfb_ioctl]MTKFB_UNREGISTER_OVERLAYBUFFER\n");
#if defined(MTK_M4U_SUPPORT) 
		if (copy_from_user(&overlay_bufferVA, (void __user *)arg, sizeof(overlay_bufferVA))) {
            printk("[FB]: copy_from_user failed! line:%d \n", __LINE__);
            r = -EFAULT;
        }
		else
		{
			struct fb_overlay_buffer_list *c,*n;
			printk("[mtkfb_ioctl]MTKFB_UNREGISTER_OVERLAYBUFFER,va0 = 0x%x\n", overlay_bufferVA);
			if(overlay_bufferVA == 0)
			{
				printk("[mtkfb_ioctl Error]MTKFB_UNREGISTER_OVERLAYBUFFER VA should not be 0x00000000\n");
				return (r);
			}

			if (down_interruptible(&sem_flipping)) {
    	    	printk("[mtkfb_ioctl] can't get semaphore\n");
        		return -ERESTARTSYS;
   	 		}
			if (down_interruptible(&sem_early_suspend)) {
        		printk("[mtkfb_ioctl] can't get semaphore\n");
        		return -ERESTARTSYS;
    		}

			c = overlay_buffer_head;
			n = c->next;
			while(overlay_bufferVA != n->buffer.src_vir_addr || n->pid != current->tgid)
			{
				c = n;
				n = c->next;
				if(!n){
					struct fb_overlay_buffer_list *p;
					p = overlay_buffer_head->next;
					ASSERT(p);
					printk("[FB driver] current va = 0x%x, buffer_list va:\n",overlay_bufferVA);
					while(p){
						printk("0x%x\n", p->buffer.src_vir_addr);
						p = p->next;
					}
					printk("[FB driver] ERROR: Can't find matched VA in buffer list\n");
				}
				ASSERT(n); //n is NULL, but not find matched buffer
			}

			printk("[mtkfb_ioctl]MTKFB_UNREGISTER_OVERLAYBUFFER,va1 = 0x%x, size = %d\n", 
					n->buffer.src_vir_addr, n->buffer.size);
			LCD_WaitForNotBusy();
        	DISP_DeallocMva(n->buffer.src_vir_addr, n->src_mva, n->buffer.size);
			{
				struct fb_overlay_buffer_list *a;
				a = overlay_buffer_head;
				printk("[mtkfb_ioctl] before delete a node,list node Addr:\n");
				
				while(a)
				{
					printk("0x%x,  ", (unsigned int)a);
					a = a->next;
				}
			}
			c->next = n->next;
			vfree(n);
			{
				struct fb_overlay_buffer_list *b;
				b = overlay_buffer_head;
				printk("\n[mtkfb_ioctl] after delete a node,list node Addr:\n");
				while(b)
				{
					printk("0x%x,  ", (unsigned int)b);
					b = b->next;
					printk("\n");
				}
			}

		   	up(&sem_early_suspend);
			up(&sem_flipping);

		}
#else
        printk("[FB]: not enable m4u! line:%d \n", __LINE__);
#endif
		return (r);
    }

#endif // MTK_FB_OVERLAY_SUPPORT


    case MTKFB_SET_ORIENTATION:
    {
        printk("[MTKFB] Set Orientation: %lu\n", arg);
#if defined(MTK_TVOUT_SUPPORT)
        // surface flinger orientation definition of 90 and 270
        // is different than DISP_TV_ROT
        if (arg & 0x1) arg ^= 0x2;
		TVOUT_SetOrientation((TVOUT_ROT)arg);
#endif
        return 0;
    }

    case MTKFB_TV_POST_VIDEO_BUFFER:
    {
        struct fb_post_video_buffer b;
        MSG(ARGU, " mtkfb_ioctl():MTKFB_TV_POST_VIDEO_BUFFER\n");

#if defined(MTK_TVOUT_SUPPORT)
        if (copy_from_user(&b, (void __user *)arg, sizeof(b)))
        {
            printk("[FB]: copy_from_user failed! line:%d \n", __LINE__);
            r = -EFAULT;
        } else {
			
            TVOUT_PostVideoBuffer((UINT32)b.vir_addr, 
                                      (TVOUT_SRC_FORMAT)b.format,
                                      b.width, b.height);
        }
#endif            
        return (r);
    }

    case MTKFB_TV_LEAVE_VIDEO_PLAYBACK_MODE:
    {
        MSG(ARGU, " mtkfb_ioctl():MTKFB_TV_LEAVE_VIDEO_PLAYBACK_MODE\n");

#if defined(MTK_TVOUT_SUPPORT)
		TVOUT_LeaveVideoBuffer();
#endif
        return 0;
    }


    case MTKFB_META_RESTORE_SCREEN:
    {
        struct fb_var_screeninfo var;

		if (copy_from_user(&var, argp, sizeof(var)))
			return -EFAULT;

        info->var.yoffset = var.yoffset;
        init_framebuffer(info);

        return mtkfb_pan_display_impl(&var, info);
    }

    case MTKFB_LOCK_FRONT_BUFFER:
        if (down_interruptible(&sem_flipping)) {
            printk("[FB Driver] can't get semaphore when lock front buffer\n");
            return -ERESTARTSYS;
        }
        return 0;

    case MTKFB_UNLOCK_FRONT_BUFFER:
        up(&sem_flipping);
        return 0;
////////////////////////////////////////////FM De-sense
    case MTKFB_FM_NOTIFY_FREQ:
	{
		unsigned long freq;
		printk("[MTKFB] FM set new channel\n");
		if(DISP_STATUS_OK != DISP_FMDesense_Query()){
		    printk("[FB]: this project not support FM De-sense\n");
			return -EFAULT;
		}

		if (copy_from_user(&freq, (void __user *)arg, sizeof(freq))) {
            printk("[FB]: copy_from_user failed! line:%d \n", __LINE__);
            r = -EFAULT;
        } else {
            printk("[MTKFB] FM channel freq is %ld\n", freq);
			DISP_FM_Desense(freq);
        }
	    return (r);
	}

	case MTKFB_RESET_UPDATESPEED:
	{
		printk("[MTKFB] FM be turned off\n");
		if(DISP_STATUS_OK != DISP_FMDesense_Query()){
		    printk("[FB]: this project not support FM De-sense\n");
			return -EFAULT;
		}

		DISP_Reset_Update();
        return (r);
	}

    case MTKFB_GET_DEFAULT_UPDATESPEED:
	{
	    unsigned int speed;
		printk("[MTKFB] get default update speed\n");
		DISP_Get_Default_UpdateSpeed(&speed);
		return copy_to_user(argp, &speed,
                            sizeof(speed)) ? -EFAULT : 0;
    }

    case MTKFB_GET_CURR_UPDATESPEED:
	{
	    unsigned int speed;
		printk("[MTKFB] get current update speed\n");
		DISP_Get_Current_UpdateSpeed(&speed);
		return copy_to_user(argp, &speed,
                            sizeof(speed)) ? -EFAULT : 0;
	}

	case MTKFB_CHANGE_UPDATESPEED:
	{
	    unsigned int speed;
		printk("[MTKFB] change update speed\n");

		if (copy_from_user(&speed, (void __user *)arg, sizeof(speed))) {
            printk("[FB]: copy_from_user failed! line:%d \n", __LINE__);
            r = -EFAULT;
        } else {
			DISP_Change_Update(speed);
        }
        return (r);
	}
////////////////////////////////////////////////
    default:
        return -EINVAL;
    }
}


/* Callback table for the frame buffer framework. Some of these pointers
 * will be changed according to the current setting of fb_info->accel_flags.
 */
static struct fb_ops mtkfb_ops = {
    .owner          = THIS_MODULE,
    .fb_open        = mtkfb_open,
    .fb_release     = mtkfb_release,
    .fb_setcolreg   = mtkfb_setcolreg,
    .fb_pan_display = mtkfb_pan_display_proxy,
    .fb_fillrect    = cfb_fillrect,
    .fb_copyarea    = cfb_copyarea,
    .fb_imageblit   = cfb_imageblit,
    .fb_cursor      = mtkfb_soft_cursor,
    .fb_check_var   = mtkfb_check_var,
    .fb_set_par     = mtkfb_set_par,
    .fb_ioctl       = mtkfb_ioctl,
};

/*
 * ---------------------------------------------------------------------------
 * Sysfs interface 
 * ---------------------------------------------------------------------------
 */

static int mtkfb_register_sysfs(struct mtkfb_device *fbdev)
{
    NOT_REFERENCED(fbdev);

    return 0;
}

static void mtkfb_unregister_sysfs(struct mtkfb_device *fbdev)
{
    NOT_REFERENCED(fbdev);
}

/*
 * ---------------------------------------------------------------------------
 * LDM callbacks
 * ---------------------------------------------------------------------------
 */
/* Initialize system fb_info object and set the default video mode.
 * The frame buffer memory already allocated by lcddma_init
 */
static int mtkfb_fbinfo_init(struct fb_info *info)
{
    struct mtkfb_device *fbdev = (struct mtkfb_device *)info->par;
    struct fb_var_screeninfo var;
    int r = 0;

    MSG_FUNC_ENTER();

    BUG_ON(!fbdev->fb_va_base);
    info->fbops = &mtkfb_ops;
    info->flags = FBINFO_FLAG_DEFAULT;
    info->screen_base = (char *) fbdev->fb_va_base;
    info->screen_size = fbdev->fb_size_in_byte;
    info->pseudo_palette = fbdev->pseudo_palette;

    r = fb_alloc_cmap(&info->cmap, 16, 0);
    if (r != 0)
        PRNERR("unable to allocate color map memory\n");

    // setup the initial video mode (RGB565)

    memset(&var, 0, sizeof(var));
    
    var.xres         = MTK_FB_XRES;
    var.yres         = MTK_FB_YRES;
    var.xres_virtual = MTK_FB_XRESV;
    var.yres_virtual = MTK_FB_YRESV;

    var.bits_per_pixel = 16;

    var.red.offset   = 11; var.red.length   = 5;
    var.green.offset =  5; var.green.length = 6;
    var.blue.offset  =  0; var.blue.length  = 5;

    var.activate = FB_ACTIVATE_NOW;

    r = mtkfb_check_var(&var, info);
    if (r != 0)
        PRNERR("failed to mtkfb_check_var\n");

    info->var = var;

    r = mtkfb_set_par(info);
    if (r != 0)
        PRNERR("failed to mtkfb_set_par\n");

    MSG_FUNC_LEAVE();
    return r;
}

/* Release the fb_info object */
static void mtkfb_fbinfo_cleanup(struct mtkfb_device *fbdev)
{
    MSG_FUNC_ENTER();

    fb_dealloc_cmap(&fbdev->fb_info->cmap);

    MSG_FUNC_LEAVE();
}


#if INIT_FB_AS_COLOR_BAR
static void fill_color(u8 *buffer,
                       u32 fillColor,
                       u8  bpp,
                       u32 linePitchInPixels,
                       u32 startX,
                       u32 startY,
                       u32 fillWidth,
                       u32 fillHeight)
{
    u32 linePitchInBytes = linePitchInPixels * bpp;
    u8 *linePtr = buffer + startY * linePitchInBytes + startX * bpp;
    s32 h;
    u32 i;
    u8 color[4];

    for(i = 0; i < bpp; ++ i)
    {
        color[i] = fillColor & 0xFF;
        fillColor >>= 8;
    }

    h = (s32)fillHeight;
    while (--h >= 0)
    {
        u8 *ptr = linePtr;
        s32 w = (s32)fillWidth;
        while (--w >= 0)
        {
            memcpy(ptr, color, bpp);
            ptr += bpp;
        }
        linePtr += linePitchInBytes;
    }
}
#endif

#define RGB565_TO_ARGB8888(x)   \
    ((((x) &   0x1F) << 3) |    \
     (((x) &  0x7E0) << 5) |    \
     (((x) & 0xF800) << 8) |    \
     (0xFF << 24)) // opaque

#if 0
static void copy_rect(u8 *dstBuffer,
                      const u8 *srcBuffer,
                      u8  dstBpp,
                      u8  srcBpp,
                      u32 dstPitchInPixels,
                      u32 srcPitchInPixels,
                      u32 dstX,
                      u32 dstY,
                      u32 copyWidth,
                      u32 copyHeight)
{
    u32 dstPitchInBytes  = dstPitchInPixels * dstBpp;
    u32 srcPitchInBytes  = srcPitchInPixels * srcBpp;
    u8 *dstPtr = dstBuffer + dstY * dstPitchInBytes + dstX * dstBpp;
    const u8 *srcPtr = srcBuffer;
    s32 h = (s32)copyHeight;
    
    if (dstBpp == srcBpp)
    {
        u32 copyBytesPerLine = copyWidth * dstBpp;
        
        while (--h >= 0)
        {
            memcpy(dstPtr, srcPtr, copyBytesPerLine);
            dstPtr += dstPitchInBytes;
            srcPtr += srcPitchInBytes;
        }
    }
    else if (srcBpp == 2 && dstBpp == 4)    // RGB565 copy to ARGB8888
    {
        while (--h >= 0)
        {
            const u16 *s = (const u16 *)srcPtr;
            u32 *d = (u32 *)dstPtr;
            s32 w = (s32)copyWidth;

            while (--w >= 0)
            {
                u16 rgb565 = *s;
                *d = RGB565_TO_ARGB8888(rgb565);
                ++ d; ++ s;
            }
            
            dstPtr += dstPitchInBytes;
            srcPtr += srcPitchInBytes;
        }
    }
    else
    {
        printk("un-supported bpp in copy_rect(), srcBpp: %d --> dstBpp: %d\n",
               srcBpp, dstBpp);

        ASSERT(0);
    }
}
#endif

/* Init frame buffer content as 3 R/G/B color bars for debug */
static int init_framebuffer(struct fb_info *info)
{
    void *buffer = info->screen_base + 
                   info->var.yoffset * info->fix.line_length;

    u32 bpp = (info->var.bits_per_pixel + 7) >> 3;

#if INIT_FB_AS_COLOR_BAR
    int i;
    
    u32 colorRGB565[] =
    {
        0xffff, // White
        0xf800, // Red
        0x07e0, // Green
        0x001f, // Blue
    };

    u32 xSteps[ARY_SIZE(colorRGB565) + 1];

    xSteps[0] = 0;
    xSteps[1] = info->var.xres / 4 * 1;
    xSteps[2] = info->var.xres / 4 * 2;
    xSteps[3] = info->var.xres / 4 * 3;
    xSteps[4] = info->var.xres;

    for(i = 0; i < ARY_SIZE(colorRGB565); ++ i)
    {
        fill_color(buffer,
                   colorRGB565[i],
                   bpp,
                   info->var.xres,
                   xSteps[i],
                   0,
                   xSteps[i+1] - xSteps[i],
                   info->var.yres);
    }
#else
    // clean whole frame buffer as black
    memset(buffer, 0, info->var.xres * info->var.yres * bpp);

#if defined(CONFIG_ARCH_MT6516)
    if (is_meta_mode())
    {
        MFC_HANDLE handle = NULL;
        MFC_CHECK_RET(MFC_Open(&handle, buffer,
                               info->var.xres, info->var.yres,
                               bpp, 0xFFFF, 0x0));
        MFC_CHECK_RET(MFC_Print(handle, "<< META Test Mode >>\n"));
        MFC_CHECK_RET(MFC_Close(handle));
    }
#elif defined(CONFIG_ARCH_MT6573)
#else
#endif   
#endif
    return 0;
}


/* Free driver resources. Can be called to rollback an aborted initialization
 * sequence.
 */
static void mtkfb_free_resources(struct mtkfb_device *fbdev, int state)
{
    int r = 0;
    
    switch (state) {
    case MTKFB_ACTIVE:
        r = unregister_framebuffer(fbdev->fb_info);
        ASSERT(0 == r);
      //lint -fallthrough
    case 5:
        mtkfb_unregister_sysfs(fbdev);
      //lint -fallthrough
    case 4:
        mtkfb_fbinfo_cleanup(fbdev);
      //lint -fallthrough
    case 3:
        DISP_CHECK_RET(DISP_Deinit());
      //lint -fallthrough
    case 2:
        dma_free_coherent(0, fbdev->fb_size_in_byte,
                          fbdev->fb_va_base, fbdev->fb_pa_base);
      //lint -fallthrough
    case 1:
        dev_set_drvdata(fbdev->dev, NULL);
        framebuffer_release(fbdev->fb_info);
      //lint -fallthrough
    case 0:
      /* nothing to free */
        break;
    default:
        BUG();
    }
}

extern char* saved_command_line;
char mtkfb_lcm_name[256] = {0};
BOOL mtkfb_find_lcm_driver(void)
{
	BOOL ret = FALSE;
	char *p, *q;

	p = strstr(saved_command_line, "lcm=");
	if(p == NULL)
	{
		// we can't find lcm string in the command line, the uboot should be old version
		return DISP_SelectDevice(NULL);
	}

	p += 4;
	if((p - saved_command_line) > strlen(saved_command_line+1))
	{
		ret = FALSE;
		goto done;
	}

	printk("%s, %s\n", __func__, p);
	q = p;
	while(*q != ' ' && *q != '\0')
		q++;

	memset((void*)mtkfb_lcm_name, 0, sizeof(mtkfb_lcm_name));
	strncpy((char*)mtkfb_lcm_name, (const char*)p, (int)(q-p));

	printk("%s, %s\n", __func__, mtkfb_lcm_name);
	if(DISP_SelectDevice(mtkfb_lcm_name))
		ret = TRUE;

done:
	return ret;
}

/* Called by LDM binding to probe and attach a new device.
 * Initialization sequence:
 *   1. allocate system fb_info structure
 *      select panel type according to machine type
 *   2. init LCD panel
 *   3. init LCD controller and LCD DMA
 *   4. init system fb_info structure
 *   5. init gfx DMA
 *   6. enable LCD panel
 *      start LCD frame transfer
 *   7. register system fb_info structure
 */
static int mtkfb_probe(struct device *dev)
{
    struct platform_device *pdev;
    struct mtkfb_device    *fbdev = NULL;
    struct fb_info         *fbi;
    int                    init_state;
    int                    r = 0;

    MSG_FUNC_ENTER();
	
	printk("%s, %s\n", __func__, saved_command_line);

	if(DISP_IsContextInited() == FALSE)
	{
		if(mtkfb_find_lcm_driver())
		{
			printk("%s, we have found the lcm - %s\n", __func__, mtkfb_lcm_name);
			is_lcm_inited = TRUE;
		}
		else if(DISP_DetectDevice() != DISP_STATUS_OK)
		{
			printk("[mtkfb] detect device fail, maybe caused by the two reasons below:\n");
			printk("\t\t1.no lcm connected\n");
			printk("\t\t2.we can't support this lcm\n");
		}
	}
	else
	{
		LCD_CHECK_RET(LCD_Init());
	}

	MTK_FB_XRES  = DISP_GetScreenWidth();
    MTK_FB_YRES  = DISP_GetScreenHeight();

	// in factory mode or recovery mode, 
	// the framebuffer can't by rotated by middleware like surfaceflinger
	// so we have to do the rotation by lcd controller
#ifdef MTK_QVGA_LANDSCAPE_SUPPORT 
	printk("[MTKFB] MTK_QVGA_LANDSCAPE_SUPPORT defined\n");
	if((MTK_LCM_PHYSICAL_ROTATION == 90 || MTK_LCM_PHYSICAL_ROTATION == 270) && 
			(get_boot_mode() == FACTORY_BOOT ||	get_boot_mode() == RECOVERY_BOOT))
	{
		printk("[MTKFB] FACTORY_BOOT mode or RECOVERY_BOOT, MTK_LCM_PHYSICAL_ROTATION=%d\n",
				MTK_LCM_PHYSICAL_ROTATION);
    	MTK_FB_XRES  = DISP_GetScreenHeight();
    	MTK_FB_YRES  = DISP_GetScreenWidth();
	}
#endif
	printk("[MTKFB] XRES=%d, YRES=%d\n", MTK_FB_XRES, MTK_FB_YRES);

    MTK_FB_BPP   = DISP_GetScreenBpp();
    MTK_FB_PAGES = DISP_GetPages();

    XGPT_Init(xgpt_cfg.num, XGPT_ISR);

    init_waitqueue_head(&screen_update_wq);

    screen_update_task = kthread_create(
        screen_update_kthread, NULL, "screen_update_kthread");

    if (IS_ERR(screen_update_task)) {
        return PTR_ERR(screen_update_task);
    }
    wake_up_process(screen_update_task);


    init_state = 0;

    pdev = to_platform_device(dev);
    if (pdev->num_resources != 1) {
        PRNERR("probed for an unknown device\n");
        r = -ENODEV;
        goto cleanup;
    }

    fbi = framebuffer_alloc(sizeof(struct mtkfb_device), dev);
    if (!fbi) {
        PRNERR("unable to allocate memory for device info\n");
        r = -ENOMEM;
        goto cleanup;
    }

    fbdev = (struct mtkfb_device *)fbi->par;
    fbdev->fb_info = fbi;
    fbdev->dev = dev;
    dev_set_drvdata(dev, fbdev);

    init_state++;   // 1

    /* Allocate and initialize video frame buffer */
    
    fbdev->fb_size_in_byte = MTK_FB_SIZEV;
    {
        struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
        fbdev->fb_pa_base = res->start;
        fbdev->fb_va_base = ioremap_nocache(res->start, res->end - res->start + 1);
        ASSERT(DISP_GetVRamSize() <= (res->end - res->start + 1));
        //memset(fbdev->fb_va_base, 0, (res->end - res->start + 1));
    }
#if defined (MTK_M4U_SUPPORT)   
	fb_va_m4u = fbdev->fb_pa_base;
	fb_size_m4u = fbdev->fb_size_in_byte;
	overlay_buffer_head = (struct fb_overlay_buffer_list*)vmalloc(sizeof(struct fb_overlay_buffer_list));
	if(!overlay_buffer_head){
		printk("[FB driver] vmalloc failed\n");
		r = -ENOMEM;
		goto cleanup;
	}
	overlay_buffer_head->next = NULL;
#endif

	printk("[FB Driver] fbdev->fb_pa_base = %x, fbdev->fb_va_base = %x\n", fbdev->fb_pa_base, (unsigned int)(fbdev->fb_va_base));

    if (!fbdev->fb_va_base) {
        PRNERR("unable to allocate memory for frame buffer\n");
        r = -ENOMEM;
        goto cleanup;
    }

    init_state++;   // 2

    /* Initialize Display Driver PDD Layer */

    if (DISP_STATUS_OK != DISP_Init((DWORD)fbdev->fb_va_base,
                                    (DWORD)fbdev->fb_pa_base,
                                    is_lcm_inited))
    {
        r = -1;
        goto cleanup;
    }

    init_state++;   // 3

    /* Register to system */

    r = mtkfb_fbinfo_init(fbi);
    if (r)
        goto cleanup;
    init_state++;   // 4

    r = mtkfb_register_sysfs(fbdev);
    if (r)
        goto cleanup;
    init_state++;   // 5

    r = register_framebuffer(fbi);
    if (r != 0) {
        PRNERR("register_framebuffer failed\n");
        goto cleanup;
    }

    fbdev->state = MTKFB_ACTIVE;

    MSG(INFO, "MTK framebuffer initialized vram=%lu\n", fbdev->fb_size_in_byte);

    MSG_FUNC_LEAVE();
    return 0;

cleanup:
    mtkfb_free_resources(fbdev, init_state);

    MSG_FUNC_LEAVE();
    return r;
}

/* Called when the device is being detached from the driver */
static int mtkfb_remove(struct device *dev)
{
    struct mtkfb_device *fbdev = dev_get_drvdata(dev);
    enum mtkfb_state saved_state = fbdev->state;

    MSG_FUNC_ENTER();
    /* FIXME: wait till completion of pending events */

    fbdev->state = MTKFB_DISABLED;
    mtkfb_free_resources(fbdev, saved_state);

    MSG_FUNC_LEAVE();
    return 0;
}

/* PM suspend */
static int mtkfb_suspend(struct device *pdev, pm_message_t mesg)
{
    NOT_REFERENCED(pdev);
    MSG_FUNC_ENTER();
    printk("[FB Driver] mtkfb_suspend(): 0x%x\n", mesg.event);
    MSG_FUNC_LEAVE();
    return 0;
}

#ifdef CONFIG_HAS_EARLYSUSPEND
static void mtkfb_early_suspend(struct early_suspend *h)
{
    MSG_FUNC_ENTER();

    printk("[FB Driver] enter early_suspend\n");
    
    if (down_interruptible(&sem_early_suspend)) {
        printk("[FB Driver] can't get semaphore in mtkfb_early_suspend()\n");
        return;
    }

    is_early_suspended = TRUE;
    
#if defined (MTK_TVOUT_SUPPORT)
	TVOUT_PowerEnable(FALSE);
#endif
	DISP_CHECK_RET(DISP_PanelEnable(FALSE));
 	DISP_CHECK_RET(DISP_PowerEnable(FALSE));

    up(&sem_early_suspend);

    printk("[FB Driver] leave early_suspend\n");

    MSG_FUNC_LEAVE();
}
#endif

/* PM resume */
static int mtkfb_resume(struct device *pdev)
{
    NOT_REFERENCED(pdev);
    MSG_FUNC_ENTER();
    printk("[FB Driver] mtkfb_resume()\n");
    MSG_FUNC_LEAVE();
    return 0;
}

#ifdef CONFIG_HAS_EARLYSUSPEND
static void mtkfb_late_resume(struct early_suspend *h)
{
    MSG_FUNC_ENTER();

    printk("[FB Driver] enter late_resume\n");

    if (down_interruptible(&sem_early_suspend)) {
        printk("[FB Driver] can't get semaphore in mtkfb_late_resume()\n");
        return;
    }

    DISP_CHECK_RET(DISP_PowerEnable(TRUE));
    DISP_CHECK_RET(DISP_PanelEnable(TRUE));
#if defined (MTK_TVOUT_SUPPORT)
	TVOUT_PowerEnable(TRUE);
#endif  	
	is_early_suspended = FALSE;

    up(&sem_early_suspend);

    printk("[FB Driver] leave late_resume\n");
    
    MSG_FUNC_LEAVE();
}
#endif


static struct platform_driver mtkfb_driver = 
{
    .driver = {
        .name    = MTKFB_DRIVER,
        .bus     = &platform_bus_type,
        .probe   = mtkfb_probe,
        .remove  = mtkfb_remove,    
        .suspend = mtkfb_suspend,
        .resume  = mtkfb_resume,
    },    
};

#ifdef CONFIG_HAS_EARLYSUSPEND
static struct early_suspend mtkfb_early_suspend_handler = 
{
	.level = EARLY_SUSPEND_LEVEL_DISABLE_FB,
	.suspend = mtkfb_early_suspend,
	.resume = mtkfb_late_resume,
};
#endif

/* Register both the driver and the device */
int __init mtkfb_init(void)
{
    int r = 0;

    MSG_FUNC_ENTER();
	
	

    /* Register the driver with LDM */

    if (platform_driver_register(&mtkfb_driver)) {
        PRNERR("failed to register mtkfb driver\n");
        r = -ENODEV;
        goto exit;
    }
   
#ifdef CONFIG_HAS_EARLYSUSPEND
   	register_early_suspend(&mtkfb_early_suspend_handler);
#endif

    DBG_Init();

exit:
    MSG_FUNC_LEAVE();
    return r;
}


static void __exit mtkfb_cleanup(void)
{
    MSG_FUNC_ENTER();

    platform_driver_unregister(&mtkfb_driver);

#ifdef CONFIG_HAS_EARLYSUSPEND
	unregister_early_suspend(&mtkfb_early_suspend_handler);
#endif

    kthread_stop(screen_update_task);

    DBG_Deinit();

    MSG_FUNC_LEAVE();
}


module_init(mtkfb_init);
module_exit(mtkfb_cleanup);

MODULE_DESCRIPTION("MEDIATEK framebuffer driver");
MODULE_AUTHOR("Zaikuo Wang <zaikuo.wang@mediatek.com>");
MODULE_LICENSE("GPL");
