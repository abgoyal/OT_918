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

/*
 * Copyright (C) 2010 MediaTek, Inc.
 *
 * Author: Terry Chang <terry.chang@mediatek.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/input.h>
#include <linux/workqueue.h>
#include <linux/timer.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/earlysuspend.h>

#include <asm/atomic.h>
#include <asm/uaccess.h>
#include <asm/tcm.h>

#include <mach/mt6573_reg_base.h>
#include <mt6573_kpd.h>
#include <mach/irqs.h>
#include <mach/mt6573_eint.h>
#include <linux/delay.h>
#include <mach/mt6573_gpio.h>
#include <linux/list.h>
#include <linux/string.h>

#include <linux/aee.h>
#define KPD_AUTOTEST	KPD_YES
#define KPD_DEBUG	KPD_NO

#define KPD_NAME	"mt6573-kpd"

/* Keypad registers */
#define KP_STA		(KP_BASE + 0x0000)
#define KP_MEM1		(KP_BASE + 0x0004)
#define KP_MEM2		(KP_BASE + 0x0008)
#define KP_MEM3		(KP_BASE + 0x000c)
#define KP_MEM4		(KP_BASE + 0x0010)
#define KP_MEM5		(KP_BASE + 0x0014)
#define KP_DEBOUNCE	(KP_BASE + 0x0018)
#define PIN_PUPD0	(0xF7000000+0x26094)

#define KPD_NUM_MEMS	5
#define KPD_MEM5_BITS	8

#define KPD_NUM_KEYS	72	/* 4 * 16 + KPD_MEM5_BITS */

#define KPD_DEBOUNCE_MASK	((1U << 14) - 1)
#define kpd_debounce_time(val)	((val) >> 5)		/* ms */

#define KPD_SAY		"kpd: "
#if KPD_DEBUG
#define kpd_print(fmt, arg...)	printk(KPD_SAY fmt, ##arg)
#else
#define kpd_print(fmt, arg...)	do {} while (0)
#endif

struct kpd_ledctl {
	u8 onoff;
	u8 div;		/* 0 ~ 15 */
	u8 duty;	/* 0 ~ 31 */
};

#if KPD_AUTOTEST
#define PRESS_OK_KEY		_IO('k', 1)
#define RELEASE_OK_KEY		_IO('k', 2)
#define PRESS_MENU_KEY		_IO('k', 3)
#define RELEASE_MENU_KEY	_IO('k', 4)
#define PRESS_UP_KEY		_IO('k', 5)
#define RELEASE_UP_KEY		_IO('k', 6)
#define PRESS_DOWN_KEY		_IO('k', 7)
#define RELEASE_DOWN_KEY	_IO('k', 8)
#define PRESS_LEFT_KEY		_IO('k', 9)
#define RELEASE_LEFT_KEY	_IO('k', 10)
#define PRESS_RIGHT_KEY		_IO('k', 11)
#define RELEASE_RIGHT_KEY	_IO('k', 12)
#define PRESS_HOME_KEY		_IO('k', 13)
#define RELEASE_HOME_KEY	_IO('k', 14)
#define PRESS_BACK_KEY		_IO('k', 15)
#define RELEASE_BACK_KEY	_IO('k', 16)
#define PRESS_CALL_KEY		_IO('k', 17)
#define RELEASE_CALL_KEY	_IO('k', 18)
#define PRESS_ENDCALL_KEY	_IO('k', 19)
#define RELEASE_ENDCALL_KEY	_IO('k', 20)
#define PRESS_VLUP_KEY		_IO('k', 21)
#define RELEASE_VLUP_KEY	_IO('k', 22)
#define PRESS_VLDOWN_KEY	_IO('k', 23)
#define RELEASE_VLDOWN_KEY	_IO('k', 24)
#define PRESS_FOCUS_KEY		_IO('k', 25)
#define RELEASE_FOCUS_KEY	_IO('k', 26)
#define PRESS_CAMERA_KEY	_IO('k', 27)
#define RELEASE_CAMERA_KEY	_IO('k', 28)
#endif
#define SET_KPD_BACKLIGHT	_IOW('k', 29, struct kpd_ledctl)

static struct input_dev *kpd_input_dev;
static bool kpd_suspend = false;
static int kpd_show_hw_keycode = 0;
static int kpd_show_register = 0;

/* for backlight control */
#if KPD_DRV_CTRL_BACKLIGHT
static void kpd_switch_backlight(struct work_struct *work);
static void kpd_backlight_timeout(unsigned long data);
static DECLARE_WORK(kpd_backlight_work, kpd_switch_backlight);
static DEFINE_TIMER(kpd_backlight_timer, kpd_backlight_timeout, 0, 0);

static unsigned long kpd_wake_keybit[BITS_TO_LONGS(KEY_CNT)];
static u16 kpd_wake_key[] __initdata = KPD_BACKLIGHT_WAKE_KEY;

static volatile bool kpd_backlight_on;
static atomic_t kpd_key_pressed = ATOMIC_INIT(0);
#endif

/* for slide QWERTY */
#if KPD_HAS_SLIDE_QWERTY
static void kpd_slide_handler(unsigned long data);
static DECLARE_TASKLET(kpd_slide_tasklet, kpd_slide_handler, 0);

static u8 kpd_slide_state = !KPD_SLIDE_POLARITY;
#endif

/* for Power key using EINT */
#if KPD_PWRKEY_USE_EINT
static void kpd_pwrkey_handler(unsigned long data);
static DECLARE_TASKLET(kpd_pwrkey_tasklet, kpd_pwrkey_handler, 0);

static u8 kpd_pwrkey_state = !KPD_PWRKEY_POLARITY;
#endif

/* for keymap handling */
static void kpd_keymap_handler(unsigned long data);
static DECLARE_TASKLET(kpd_keymap_tasklet, kpd_keymap_handler, 0);

static u16 kpd_keymap[KPD_NUM_KEYS] = KPD_INIT_KEYMAP();
static u16 kpd_keymap_state[KPD_NUM_MEMS] = {
	0xffff, 0xffff, 0xffff, 0xffff, 0x00ff
};

/* for autotest */
#if KPD_AUTOTEST
static const u16 kpd_auto_keymap[] = {
	KEY_OK, KEY_MENU,
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,
	KEY_HOME, KEY_BACK,
	KEY_CALL, KEY_ENDCALL,
	KEY_VOLUMEUP, KEY_VOLUMEDOWN,
	KEY_FOCUS, KEY_CAMERA,
};
#endif

static	struct timeval t1,t2;
static inline void kpd_get_keymap_state(u16 state[])
{
	state[0] = *(volatile u16 *)KP_MEM1;
	state[1] = *(volatile u16 *)KP_MEM2;
	state[2] = *(volatile u16 *)KP_MEM3;
	state[3] = *(volatile u16 *)KP_MEM4;
	state[4] = *(volatile u16 *)KP_MEM5;
	if (kpd_show_register) {
		printk(KPD_SAY "register = %x %x %x %x %x\n",
		       state[0], state[1], state[2], state[3], state[4]);
	}
}

static inline void kpd_set_debounce(u16 val)
{
	*(volatile u16 *)KP_DEBOUNCE = (u16)(val & KPD_DEBOUNCE_MASK);
}

#if KPD_DRV_CTRL_BACKLIGHT
static void kpd_switch_backlight(struct work_struct *work)
{
	if (kpd_backlight_on) {
		kpd_enable_backlight();
		kpd_print("backlight is on\n");
	} else {
		kpd_disable_backlight();
		kpd_print("backlight is off\n");
	}
}

static void kpd_backlight_timeout(unsigned long data)
{
	if (!atomic_read(&kpd_key_pressed)) {
		kpd_backlight_on = !!atomic_read(&kpd_key_pressed);
		schedule_work(&kpd_backlight_work);
		data = 1;
	}
	kpd_print("backlight timeout%s\n", 
	          data ? ": schedule backlight work" : "");
}

void kpd_backlight_handler(bool pressed, u16 linux_keycode)
{
	if (kpd_suspend && !test_bit(linux_keycode, kpd_wake_keybit)) {
		kpd_print("Linux keycode %u is not WAKE key\n", linux_keycode);
		return;
	}

	/* not in suspend or the key pressed is WAKE key */
	if (pressed) {
		atomic_inc(&kpd_key_pressed);
		kpd_backlight_on = !!atomic_read(&kpd_key_pressed);
		schedule_work(&kpd_backlight_work);
		kpd_print("switch backlight on\n");
	} else {
		atomic_dec(&kpd_key_pressed);
		mod_timer(&kpd_backlight_timer,
		          jiffies + KPD_BACKLIGHT_TIME * HZ);
		kpd_print("activate backlight timer\n");
	}
}
#endif

#if KPD_HAS_SLIDE_QWERTY
static void kpd_slide_handler(unsigned long data)
{
	bool slid;
	u8 old_state = kpd_slide_state;
	u32 temp;
	
	mt65xx_eint_mask(KPD_SLIDE_EINT);
	kpd_slide_state = !kpd_slide_state;
	slid = (kpd_slide_state == !!KPD_SLIDE_POLARITY);
	/* for SW_LID, 0: lid open => slid, 1: lid shut => closed */
	input_report_switch(kpd_input_dev, SW_LID, !slid);
	kpd_print("report QWERTY = %s\n", slid ? "slid" : "closed");
	if(old_state==0)
	{
		temp =  *(volatile u32 *)PIN_PUPD0;	
		temp |= (0x1<<20);
		temp &=~(0x1<<28);
		*(volatile u32 *)PIN_PUPD0 = (u32)temp;
	}
	else
	{
		temp =  *(volatile u32 *)PIN_PUPD0;	
		temp &=~(0x1<<20);
		temp |=(0x1<<28);
		*(volatile u32 *)PIN_PUPD0 = (u32)temp;
	}
	/* for detecting the return to old_state */
	mt65xx_eint_set_polarity(KPD_SLIDE_EINT, old_state);
	mdelay(60);
	mt65xx_eint_unmask(KPD_SLIDE_EINT);
}

static void kpd_slide_eint_handler(void)
{
	tasklet_schedule(&kpd_slide_tasklet);
}
#endif

#if KPD_PWRKEY_USE_EINT
static void kpd_pwrkey_handler(unsigned long data)
{
	bool pressed;
	u8 old_state = kpd_pwrkey_state;

	kpd_pwrkey_state = !kpd_pwrkey_state;
	pressed = (kpd_pwrkey_state == !!KPD_PWRKEY_POLARITY);
	if (kpd_show_hw_keycode) {
		printk(KPD_SAY "(%s) HW keycode = using EINT\n",
		       pressed ? "pressed" : "released");
	}
	kpd_backlight_handler(pressed, KPD_PWRKEY_MAP);
	input_report_key(kpd_input_dev, KPD_PWRKEY_MAP, pressed);
	kpd_print("report Linux keycode = %u\n", KPD_PWRKEY_MAP);

	/* for detecting the return to old_state */
	mt65xx_eint_set_polarity(KPD_PWRKEY_EINT, old_state);
	mt65xx_eint_unmask(KPD_PWRKEY_EINT);
}

static void kpd_pwrkey_eint_handler(void)
{
	tasklet_schedule(&kpd_pwrkey_tasklet);
}
#endif

static void kpd_keymap_handler(unsigned long data)
{
	int i, j;
	bool pressed;
	u16 new_state[KPD_NUM_MEMS], change, mask;
	u16 hw_keycode, linux_keycode;
	bool kpd_volumn_down_flag = false;
	bool kpd_volumn_up_flag = false;
	kpd_get_keymap_state(new_state);

	for (i = 0; i < KPD_NUM_MEMS; i++) {
		change = new_state[i] ^ kpd_keymap_state[i];
		if (!change)
			continue;

		for (j = 0; j < 16; j++) {
			mask = 1U << j;
			if (!(change & mask))
				continue;

			hw_keycode = (i << 4) + j;
			/* bit is 1: not pressed, 0: pressed */
			pressed = !(new_state[i] & mask);

			BUG_ON(hw_keycode >= KPD_NUM_KEYS);
			linux_keycode = kpd_keymap[hw_keycode];
			if(pressed && linux_keycode == KEY_VOLUMEDOWN)
			{
				
				kpd_volumn_down_flag = true;
			}
			if(pressed && linux_keycode == KEY_VOLUMEUP)
			{
				kpd_volumn_up_flag= true;
			}
			if (unlikely(linux_keycode == 0)) {
				kpd_print("Linux keycode = 0\n");
				continue;
			}

			kpd_backlight_handler(pressed, linux_keycode);
			input_report_key(kpd_input_dev, linux_keycode, pressed);
			do_gettimeofday(&t2);
			if (kpd_show_hw_keycode) {
				printk(KPD_SAY "(%s) HW keycode = %d, time:%ld(ms)\n",
				       pressed ? "pressed" : "released",
				       hw_keycode, (t2.tv_sec*1000+t2.tv_usec/1000)-(t1.tv_sec*1000+t1.tv_usec/1000));
			}
			kpd_print("report Linux keycode = %u\n", linux_keycode);
		}
	}

	if( (kpd_volumn_down_flag == true) && (kpd_volumn_up_flag == true))
	{
		printk(KPD_SAY "kpd_volumn_up+ volumn_down,will trige DB ");
		#ifdef CONFIG_MTK_AEE_FEATURE
		aee_kernel_reminding("manual dump ", "Triggered by press KEY_VOLUMEUP+KEY_VOLUMEDOWN");
		#endif
		kpd_volumn_down_flag = false;
		kpd_volumn_up_flag = false;
	}
	memcpy(kpd_keymap_state, new_state, sizeof(new_state));
	kpd_print("save new keymap state\n");
	enable_irq(MT6573_KEYPAD_IRQ_LINE);
}

static irqreturn_t __tcmfunc kpd_irq_handler(int irq, void *dev_id)
{
	/* use _nosync to avoid deadlock */
	do_gettimeofday(&t1);
	disable_irq_nosync(MT6573_KEYPAD_IRQ_LINE);

	tasklet_schedule(&kpd_keymap_tasklet);
	return IRQ_HANDLED;
}

static long kpd_dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	void __user *uarg = (void __user *)arg;
	struct kpd_ledctl ledctl;

	switch (cmd) {
#if KPD_AUTOTEST
	case PRESS_OK_KEY:
		printk("[AUTOTEST] PRESS OK KEY!!\n");
		input_report_key(kpd_input_dev, KEY_OK, 1);
		break;
	case RELEASE_OK_KEY:
		printk("[AUTOTEST] RELEASE OK KEY!!\n");
		input_report_key(kpd_input_dev, KEY_OK, 0);
		break;

	case PRESS_MENU_KEY:
		printk("[AUTOTEST] PRESS MENU KEY!!\n");
		input_report_key(kpd_input_dev, KEY_MENU, 1);
		break;
	case RELEASE_MENU_KEY:
		printk("[AUTOTEST] RELEASE MENU KEY!!\n");
		input_report_key(kpd_input_dev, KEY_MENU, 0);
		break;

	case PRESS_UP_KEY:
		printk("[AUTOTEST] PRESS UP KEY!!\n");
		input_report_key(kpd_input_dev, KEY_UP, 1);
		break;
	case RELEASE_UP_KEY:
		printk("[AUTOTEST] RELEASE UP KEY!!\n");
		input_report_key(kpd_input_dev, KEY_UP, 0);
		break;

	case PRESS_DOWN_KEY:
		printk("[AUTOTEST] PRESS DOWN KEY!!\n");
		input_report_key(kpd_input_dev, KEY_DOWN, 1);
		break;
	case RELEASE_DOWN_KEY:
		printk("[AUTOTEST] RELEASE DOWN KEY!!\n");
		input_report_key(kpd_input_dev, KEY_DOWN, 0);
		break;

	case PRESS_LEFT_KEY:
		printk("[AUTOTEST] PRESS LEFT KEY!!\n");
		input_report_key(kpd_input_dev, KEY_LEFT, 1);
		break;
	case RELEASE_LEFT_KEY:
		printk("[AUTOTEST] RELEASE LEFT KEY!!\n");
		input_report_key(kpd_input_dev, KEY_LEFT, 0);
		break;

	case PRESS_RIGHT_KEY:
		printk("[AUTOTEST] PRESS RIGHT KEY!!\n");
		input_report_key(kpd_input_dev, KEY_RIGHT, 1);
		break;
	case RELEASE_RIGHT_KEY:
		printk("[AUTOTEST] RELEASE RIGHT KEY!!\n");
		input_report_key(kpd_input_dev, KEY_RIGHT, 0);
		break;

	case PRESS_HOME_KEY:
		printk("[AUTOTEST] PRESS HOME KEY!!\n");
		input_report_key(kpd_input_dev, KEY_HOME, 1);
		break;
	case RELEASE_HOME_KEY:
		printk("[AUTOTEST] RELEASE HOME KEY!!\n");
		input_report_key(kpd_input_dev, KEY_HOME, 0);
		break;

	case PRESS_BACK_KEY:
		printk("[AUTOTEST] PRESS BACK KEY!!\n");
		input_report_key(kpd_input_dev, KEY_BACK, 1);
		break;
	case RELEASE_BACK_KEY:
		printk("[AUTOTEST] RELEASE BACK KEY!!\n");
		input_report_key(kpd_input_dev, KEY_BACK, 0);
		break;

	case PRESS_CALL_KEY:
		printk("[AUTOTEST] PRESS CALL KEY!!\n");
		input_report_key(kpd_input_dev, KEY_CALL, 1);
		break;
	case RELEASE_CALL_KEY:
		printk("[AUTOTEST] RELEASE CALL KEY!!\n");
		input_report_key(kpd_input_dev, KEY_CALL, 0);
		break;

	case PRESS_ENDCALL_KEY:
		printk("[AUTOTEST] PRESS ENDCALL KEY!!\n");
		input_report_key(kpd_input_dev, KEY_ENDCALL, 1);
		break;
	case RELEASE_ENDCALL_KEY:
		printk("[AUTOTEST] RELEASE ENDCALL KEY!!\n");
		input_report_key(kpd_input_dev, KEY_ENDCALL, 0);
		break;

	case PRESS_VLUP_KEY:
		printk("[AUTOTEST] PRESS VOLUMEUP KEY!!\n");
		input_report_key(kpd_input_dev, KEY_VOLUMEUP, 1);
		break;
	case RELEASE_VLUP_KEY:
		printk("[AUTOTEST] RELEASE VOLUMEUP KEY!!\n");
		input_report_key(kpd_input_dev, KEY_VOLUMEUP, 0);
		break;

	case PRESS_VLDOWN_KEY:
		printk("[AUTOTEST] PRESS VOLUMEDOWN KEY!!\n");
		input_report_key(kpd_input_dev, KEY_VOLUMEDOWN, 1);
		break;
	case RELEASE_VLDOWN_KEY:
		printk("[AUTOTEST] RELEASE VOLUMEDOWN KEY!!\n");
		input_report_key(kpd_input_dev, KEY_VOLUMEDOWN, 0);
		break;

	case PRESS_FOCUS_KEY:
		printk("[AUTOTEST] PRESS FOCUS KEY!!\n");
		input_report_key(kpd_input_dev, KEY_FOCUS, 1);
		break;
	case RELEASE_FOCUS_KEY:
		printk("[AUTOTEST] RELEASE FOCUS KEY!!\n");
		input_report_key(kpd_input_dev, KEY_FOCUS, 0);
		break;

	case PRESS_CAMERA_KEY:
		printk("[AUTOTEST] PRESS CAMERA KEY!!\n");
		input_report_key(kpd_input_dev, KEY_CAMERA, 1);
		break;
	case RELEASE_CAMERA_KEY:
		printk("[AUTOTEST] RELEASE CAMERA KEY!!\n");
		input_report_key(kpd_input_dev, KEY_CAMERA, 0);
		break;
#endif

	case SET_KPD_BACKLIGHT:
		if (copy_from_user(&ledctl, uarg, sizeof(struct kpd_ledctl)))
			return -EFAULT;

		//kpd_set_backlight(ledctl.onoff, &ledctl.div, &ledctl.duty);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}

static int kpd_dev_open(struct inode *inode, struct file *file)
{
	return 0;
}

static struct file_operations kpd_dev_fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= kpd_dev_ioctl,
	.open		= kpd_dev_open,
};

static struct miscdevice kpd_dev = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= KPD_NAME,
	.fops	= &kpd_dev_fops,
};

static int kpd_open(struct input_dev *dev)
{
#if KPD_HAS_SLIDE_QWERTY
	u32 temp;
	bool evdev_flag=false;
	struct input_handler *handler;
	struct input_handle *handle;
	handle = rcu_dereference(dev->grab);
	if (handle)
	{
		handler = handle->handler;
		if(strcmp(handler->name, "evdev")==0) 
		{
			return -1;
		}	
	}
	else 
	{
		list_for_each_entry_rcu(handle, &dev->h_list, d_node) {
			handler = handle->handler;
			if(strcmp(handler->name, "evdev")==0) 
			{
				evdev_flag=true;
				break;
			}
		}
		if(evdev_flag==false)
		{
			return -1;	
		}	
	}

	temp =  *(volatile u32 *)PIN_PUPD0;	
	temp &=~(0x1<<20);
	temp |= (0x1<<28);
	*(volatile u32 *)PIN_PUPD0 = (u32)temp;
	mt65xx_eint_set_sens(KPD_SLIDE_EINT, KPD_SLIDE_SENSITIVE);
	mt65xx_eint_set_hw_debounce(KPD_SLIDE_EINT,KPD_SLIDE_DEBOUNCE);
	mt65xx_eint_registration(KPD_SLIDE_EINT, true, KPD_SLIDE_POLARITY,
	                         kpd_slide_eint_handler, false);	
#endif	                         
	return 0;
}
static int kpd_pdrv_probe(struct platform_device *pdev)
{
	int i, r;
//	u32 temp;
	/* initialize and register input device (/dev/input/eventX) */
	kpd_input_dev = input_allocate_device();
	if (!kpd_input_dev)
		return -ENOMEM;

	kpd_input_dev->name = KPD_NAME;
	kpd_input_dev->id.bustype = BUS_HOST;
	kpd_input_dev->id.vendor = 0x2454;
	kpd_input_dev->id.product = 0x6573;
	kpd_input_dev->id.version = 0x0010;
	kpd_input_dev->open = kpd_open;

	__set_bit(EV_KEY, kpd_input_dev->evbit);

#if KPD_PWRKEY_USE_EINT
	__set_bit(KPD_PWRKEY_MAP, kpd_input_dev->keybit);
	kpd_keymap[8] = 0;
#endif
	for (i = 17; i < KPD_NUM_KEYS; i += 9)	/* only [8] works for Power key */
		kpd_keymap[i] = 0;

	for (i = 0; i < KPD_NUM_KEYS; i++) {
		if (kpd_keymap[i] != 0)
			__set_bit(kpd_keymap[i], kpd_input_dev->keybit);
	}

#if KPD_AUTOTEST
	for (i = 0; i < ARRAY_SIZE(kpd_auto_keymap); i++)
		__set_bit(kpd_auto_keymap[i], kpd_input_dev->keybit);
#endif

#if KPD_HAS_SLIDE_QWERTY
	__set_bit(EV_SW, kpd_input_dev->evbit);
	__set_bit(SW_LID, kpd_input_dev->swbit);
	__set_bit(SW_LID, kpd_input_dev->sw);	/* 1: lid shut => closed */
#endif

	kpd_input_dev->dev.parent = &pdev->dev;
	r = input_register_device(kpd_input_dev);
	if (r) {
		printk(KPD_SAY "register input device failed (%d)\n", r);
		input_free_device(kpd_input_dev);
		return r;
	}

	/* register device (/dev/mt6573-kpd) */
	kpd_dev.parent = &pdev->dev;
	r = misc_register(&kpd_dev);
	if (r) {
		printk(KPD_SAY "register device failed (%d)\n", r);
		input_unregister_device(kpd_input_dev);
		return r;
	}

	/* register IRQ and EINT */
	kpd_set_debounce(KPD_KEY_DEBOUNCE);
	r = request_irq(MT6573_KEYPAD_IRQ_LINE, (irq_handler_t)kpd_irq_handler, 0, KPD_NAME, NULL);
	if (r) {
		printk(KPD_SAY "register IRQ failed (%d)\n", r);
		misc_deregister(&kpd_dev);
		input_unregister_device(kpd_input_dev);
		return r;
	}

#if KPD_PWRKEY_USE_EINT
	mt65xx_eint_set_sens(KPD_PWRKEY_EINT, KPD_PWRKEY_SENSITIVE);
	mt65xx_eint_set_hw_debounce(KPD_PWRKEY_EINT,
	                            kpd_debounce_time(KPD_PWRKEY_DEBOUNCE));
	mt65xx_eint_registration(KPD_PWRKEY_EINT, true, KPD_PWRKEY_POLARITY,
	                         kpd_pwrkey_eint_handler, false);
#endif
#if 0
#if KPD_HAS_SLIDE_QWERTY
	temp =  *(volatile u32 *)PIN_PUPD0;	
	temp |= (0x1<<20);
	temp &=~(0x1<<28);
	*(volatile u32 *)PIN_PUPD0 = (u32)temp;
	mt65xx_eint_set_sens(KPD_SLIDE_EINT, KPD_SLIDE_SENSITIVE);
	mt65xx_eint_set_hw_debounce(KPD_SLIDE_EINT,KPD_SLIDE_DEBOUNCE);
	mt65xx_eint_registration(KPD_SLIDE_EINT, true, KPD_SLIDE_POLARITY,
	                         kpd_slide_eint_handler, false);
#endif
#endif
	/* switch backlight on */
	kpd_backlight_handler(true, 0);
	kpd_backlight_handler(false, 0);

	return 0;
}

/* should never be called */
static int kpd_pdrv_remove(struct platform_device *pdev)
{
	return 0;
}

//#ifndef CONFIG_HAS_EARLYSUSPEND
static int kpd_pdrv_suspend(struct platform_device *pdev, pm_message_t state)
{
	kpd_suspend = true;
	kpd_disable_backlight();
	kpd_print("suspend!! (%d)\n", kpd_suspend);
//	mt_set_gpio_dir(GPIO_KPD_KCOL1_PIN, GPIO_DIR_IN);
	mt_set_gpio_dir(GPIO_KPD_KCOL2_PIN, GPIO_DIR_IN);
	mt_set_gpio_dir(GPIO_KPD_KROW0_PIN, GPIO_DIR_OUT);
	mt_set_gpio_dir(GPIO_KPD_KROW2_PIN, GPIO_DIR_OUT);
//	mt_set_gpio_mode(GPIO_KPD_KCOL1_PIN, GPIO_MODE_00);
	mt_set_gpio_mode(GPIO_KPD_KCOL2_PIN, GPIO_MODE_00);
	mt_set_gpio_mode(GPIO_KPD_KROW0_PIN, GPIO_MODE_00);
	mt_set_gpio_mode(GPIO_KPD_KROW2_PIN, GPIO_MODE_00);
//	mt_set_gpio_pull_enable(GPIO_KPD_KCOL1_PIN, true);
//	mt_set_gpio_pull_select(GPIO_KPD_KCOL1_PIN, GPIO_PULL_DOWN);
	mt_set_gpio_pull_enable(GPIO_KPD_KCOL2_PIN, true);
	mt_set_gpio_pull_select(GPIO_KPD_KCOL2_PIN, GPIO_PULL_DOWN);
	mt_set_gpio_out(GPIO_KPD_KROW0_PIN, GPIO_OUT_ONE);
	mt_set_gpio_out(GPIO_KPD_KROW2_PIN, GPIO_OUT_ONE);
	return 0;
}

static int kpd_pdrv_resume(struct platform_device *pdev)
{
	kpd_suspend = false;
	//kpd_enable_backlight();
	kpd_print("resume!! (%d)\n", kpd_suspend);
//	mt_set_gpio_dir(GPIO_KPD_KCOL1_PIN, GPIO_DIR_IN);
	mt_set_gpio_dir(GPIO_KPD_KCOL2_PIN, GPIO_DIR_IN);
	mt_set_gpio_dir(GPIO_KPD_KROW0_PIN, GPIO_DIR_OUT);
	mt_set_gpio_dir(GPIO_KPD_KROW2_PIN, GPIO_DIR_OUT);
//	mt_set_gpio_mode(GPIO_KPD_KCOL1_PIN, GPIO_MODE_01);
	mt_set_gpio_mode(GPIO_KPD_KCOL2_PIN, GPIO_MODE_01);
	mt_set_gpio_mode(GPIO_KPD_KROW0_PIN, GPIO_MODE_01);
	mt_set_gpio_mode(GPIO_KPD_KROW2_PIN, GPIO_MODE_01);
//	mt_set_gpio_pull_enable(GPIO_KPD_KCOL1_PIN, true);
//	mt_set_gpio_pull_select(GPIO_KPD_KCOL1_PIN, GPIO_PULL_UP);
	mt_set_gpio_pull_enable(GPIO_KPD_KCOL2_PIN, true);
	mt_set_gpio_pull_select(GPIO_KPD_KCOL2_PIN, GPIO_PULL_UP);
	return 0;
}
//#else
//#define kpd_pdrv_suspend	NULL
//#define kpd_pdrv_resume	NULL
//#endif

static struct platform_driver kpd_pdrv = {
	.probe		= kpd_pdrv_probe,
	.remove		= kpd_pdrv_remove,
	.suspend	= kpd_pdrv_suspend,
	.resume		= kpd_pdrv_resume,
	.driver		= {
		.name	= KPD_NAME,
		.owner	= THIS_MODULE,
	},
};

#ifdef CONFIG_HAS_EARLYSUSPEND
static void kpd_early_suspend(struct early_suspend *h)
{
	kpd_suspend = true;
	kpd_disable_backlight();
	kpd_print("early suspend!! (%d)\n", kpd_suspend);
}

static void kpd_early_resume(struct early_suspend *h)
{
	kpd_suspend = false;
	//kpd_enable_backlight();
	kpd_print("early resume!! (%d)\n", kpd_suspend);
}

static struct early_suspend kpd_early_suspend_desc = {
	.level		= EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 1,
	.suspend	= kpd_early_suspend,
	.resume		= kpd_early_resume,
};
#endif

static int __init kpd_mod_init(void)
{
	int r;
#if KPD_DRV_CTRL_BACKLIGHT
	for (r = 0; r < ARRAY_SIZE(kpd_wake_key); r++)
		__set_bit(kpd_wake_key[r], kpd_wake_keybit);
#endif

	r = platform_driver_register(&kpd_pdrv);
	if (r) {
		printk(KPD_SAY "register driver failed (%d)\n", r);
		return r;
	}

#ifdef CONFIG_HAS_EARLYSUSPEND
	register_early_suspend(&kpd_early_suspend_desc);
#endif
	return 0;
}

/* should never be called */
static void __exit kpd_mod_exit(void)
{
}

module_init(kpd_mod_init);
module_exit(kpd_mod_exit);

module_param(kpd_show_hw_keycode, bool, 0644);
module_param(kpd_show_register, bool, 0644);

MODULE_AUTHOR("Terry Chang <terry.chang@mediatek.com>");
MODULE_DESCRIPTION("MT6573 Keypad (KPD) Driver v0.2");
MODULE_LICENSE("GPL");
