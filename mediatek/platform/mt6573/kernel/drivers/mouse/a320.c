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

/* alps/ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/fm/mt6573_fm.c
 *
 * (C) Copyright 2009 
 * MediaTek <www.MediaTek.com>
 * MingHsien Hsieh <minghsien.hsieh@MediaTek.com>
 *
 * ADBS-A320 driver (OFN device)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/earlysuspend.h>
#include <linux/hwmon-sysfs.h>
#include <linux/delay.h>
#include <mach/mt6573_reg_base.h>
#include <mach/mt6573_typedefs.h>
#include <mach/mt6573_gpio.h>
#include <mach/mt6573_pll.h>
#include <mach/irqs.h>
#include <asm/io.h>
#include <linux/platform_device.h>
#include <linux/autoconf.h>
#include <linux/workqueue.h>
#include <cust_gpio_usage.h>
#include <cust_eint.h>
#include <cust_ofn.h>
#include "a320.h"
#include <linux/slab.h>

/******************************************************************************
 * configuration
*******************************************************************************/
//#define A320_DEBUG_RW
#define CONFIG_ACCU_COUNT      /*!< use accumulated count to adjust sensitivity */        
/******************************************************************************
 * macro
*******************************************************************************/
#define C_I2C_FIFO_SIZE         8       /*according i2c_mt6573.c*/
#define ABS(X)                  ((X > 0) ? (X) : (-X))
/*----------------------------------------------------------------------------*/
#define AVA_TAG					"[A320] "
#define A320_DEV_NAME		    "A320"
#define AVA_FUN(f)				printk(AVA_TAG"%s\n", __FUNCTION__)
#define AVA_ERR(fmt, args...)	printk(KERN_ERR  AVA_TAG"%s %d : "fmt, __FUNCTION__, __LINE__, ##args)
#define AVA_LOG(fmt, args...)	printk(KERN_INFO AVA_TAG fmt, ##args)
#define AVA_MSG(...)	        printk(__VA_ARGS__)
#define AVA_VER(fmt, args...)   ((void)0)
/******************************************************************************
 * extern functions
*******************************************************************************/
extern void mt65xx_eint_unmask(unsigned int line);
extern void mt65xx_eint_mask(unsigned int line);
extern void mt65xx_eint_set_polarity(kal_uint8 eintno, kal_bool ACT_Polarity);
extern void mt65xx_eint_set_hw_debounce(kal_uint8 eintno, kal_uint32 ms);
extern kal_uint32 mt65xx_eint_set_sens(kal_uint8 eintno, kal_bool sens);
extern void mt65xx_eint_registration(kal_uint8 eintno, kal_bool Dbounce_En,
                                     kal_bool ACT_Polarity, void (EINT_FUNC_PTR)(void),
                                     kal_bool auto_umask);
/******************************************************************************
 * local functions
*******************************************************************************/
static int a320_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id); 
static int a320_i2c_remove(struct i2c_client *client);
static int a320_i2c_detect(struct i2c_client *client, int kind, struct i2c_board_info *info);
static ssize_t a320_show_trace(struct device *dev, 
                               struct device_attribute *attr, char *buf);
static ssize_t a320_store_trace(struct device* dev, 
                                struct device_attribute *attr, const char *buf, size_t count);
#if !defined(CONFIG_HAS_EARLYSUSPEND)                                 
static int a320_i2c_suspend(struct i2c_client *client, pm_message_t msg);
static int a320_i2c_resume(struct i2c_client *client);
#endif
static int a320_reset_and_init(struct i2c_client *client);
/******************************************************************************
 * Configration Settings
*******************************************************************************/
/******************************************************************************
 * enumeration
*******************************************************************************/
typedef enum {
    AVA_DIR_UP  = 0,
    AVA_DIR_DN  = 1,
    AVA_DIR_LF  = 2,
    AVA_DIR_RG  = 3,
    AVA_DIR_NUM = 4,
} AVA_DIR;
/*----------------------------------------------------------------------------*/
#define AVA_BIT_UP  (1 << AVA_DIR_UP)
#define AVA_BIT_DN  (1 << AVA_DIR_DN)
#define AVA_BIT_LF  (1 << AVA_DIR_LF)
#define AVA_BIT_RG  (1 << AVA_DIR_RG)
/*----------------------------------------------------------------------------*/
typedef enum {
    AVA_TRC_KEY_DOWN    = 0x0001,
    AVA_TRC_KEY_UP      = 0x0002,   
    AVA_TRC_EINT        = 0x0004,
    AVA_TRC_WORK        = 0x0008,
    AVA_TRC_POLL        = 0x0010,
    AVA_TRC_MOTION      = 0x0020,
    AVA_TRC_I2C         = 0x0040,
    AVA_TRC_SHORT_LOG   = 0x8000,
}AVA_TRC;
/*----------------------------------------------------------------------------*/
typedef enum {
    AVA_DETECT_POLL     = 0,
    AVA_DETECT_EINT     = 1,            
}AVA_DETECT;
/******************************************************************************
 * structure
*******************************************************************************/
struct a320_dir
{
    /*trackball class*/
    s16      step_x;    /*the step contributed to x-axis*/
    s16      step_y;    /*the step contributed to y-axis*/
    /*keyboard class*/    
    atomic_t val;       /*current value in the direction*/
    atomic_t cnt;       /*counter*/
    int64_t  last_trig; /*last trigger time. converted from timespec*/
    int64_t  first_acc; /*the time stamp for first accumulation, it's defined when count becomes from zero to positive*/
    int      key_evt;   /*key event*/
};
/*----------------------------------------------------------------------------*/
struct a320_priv
{
    struct ofn_hw          *hw;
	struct i2c_client	   *client;    
    struct input_dev       *dev;
    struct timer_list       timer;
    atomic_t                report_cls;
    atomic_t                suspended;

    /*trackball class*/
    struct work_struct      eint_ball_work;
    atomic_t                quan_x;
    atomic_t                quan_y;
    atomic_t                accu_max;
    int64_t                 last_time;
    int                     accu_dx;
    int                     accu_dy;
    atomic_t                tb_inact_cnt;

    /*keyboard class*/
    struct work_struct      eint_key_work;
    struct work_struct      poll_key_work;
    atomic_t detect; /*functionality config: 0: eint; 1: polling*/
    atomic_t step;   /*minimum step to trigger key event*/
    atomic_t trace;  /*trace on/off*/
    atomic_t acc_cnt;
    atomic_t inact_cnt;
    atomic_t act_cnt;
    atomic_t sup_cnt;

    struct a320_dir dir[AVA_DIR_NUM];
    u_long   pending;   /*bit mask, to indicate if event is pending in some direction*/        
       
    /*early suspend*/
#if defined(CONFIG_HAS_EARLYSUSPEND)    
    struct early_suspend early_drv;
#endif     
};
/*----------------------------------------------------------------------------*/
struct a320_reg{
    const char *name;
    u16 addr;
};
/*----------------------------------------------------------------------------*/
static struct a320_priv *g_a320_ptr = NULL;
/*----------------------------------------------------------------------------*/
static const struct i2c_device_id a320_i2c_id[] = {{A320_DEV_NAME,0},{}};
/*the adapter id & i2c address will be available in cust_ofn.c*/
static unsigned short a320_force[] = {0x00, 0x00, I2C_CLIENT_END, I2C_CLIENT_END};
static const unsigned short *const a320_forces[] = { a320_force, NULL };
static struct i2c_client_address_data a320_addr_data = { .forces = a320_forces,};
/*----------------------------------------------------------------------------*/
static struct i2c_driver a320_i2c_driver = {
    .probe      = a320_i2c_probe,
    .remove     = a320_i2c_remove,
    .detect     = a320_i2c_detect,
#if !defined(CONFIG_HAS_EARLYSUSPEND)    	
	.suspend    = a320_i2c_suspend,
	.resume     = a320_i2c_resume,
#endif
	.driver.name = A320_DEV_NAME,
	.id_table = a320_i2c_id,
    .address_data = &a320_addr_data,
};
/*----------------------------------------------------------------------------*/
static struct a320_reg a320_regs[] = {
    {"PRODUCT_ID",              A320_REG_PRODUCT_ID        }, 
    {"REVISION_ID",             A320_REG_REVISION_ID       },
    {"MOTION",                  A320_REG_MOTION            },
    {"DELTA_X",                 A320_REG_DELTA_X           },
    {"DELTA_Y",                 A320_REG_DELTA_Y           },
    {"SQUAL",                   A320_REG_SQUAL             }, 
    {"SHUTTER_UPPER",           A320_REG_SHUTTER_UPPER     },
    {"SHUTTER_LOWER",           A320_REG_SHUTTER_LOWER     },
    {"MAXIMUM_PIXEL",           A320_REG_MAXIMUM_PIXEL     },
    {"PIXEL_SUM",               A320_REG_PIXEL_SUM         },
    {"MINIMUM_PIXEL",           A320_REG_MINIMUM_PIXEL     },
    {"PIXEL_GRAB",              A320_REG_PIXEL_GRAB        },
    {"CRC0",                    A320_REG_CRC0              },
    {"CRC1",                    A320_REG_CRC1              },
    {"CRC2",                    A320_REG_CRC2              },
    {"CRC3",                    A320_REG_CRC3              },
    {"SELF_TEST",               A320_REG_SELF_TEST         },
    {"CONFIGRATIONS",           A320_REG_CONFIGRATIONS     },
    {"LED_CONTROL",             A320_REG_LED_CONTROL       },
    {"IO_MODE",                 A320_REG_IO_MODE           },
    {"MOTION_CONTROL",          A320_REG_MOTION_CONTROL    },
    {"OBSERVATION",             A320_REG_OBSERVATION       },
    {"SOFT_RESET",              A320_REG_SOFT_RESET        },
    {"SHUTTER_MAX_HI",          A320_REG_SHUTTER_MAX_HI    },
    {"SHUTTER_MAX_LO",          A320_REG_SHUTTER_MAX_LO    },
    {"INVERSE_REVION_ID",       A320_REG_INVERSE_REVION_ID },
    {"INVERSE_PRODUCT_ID",      A320_REG_INVERSE_PRODUCT_ID},
    {"OFN_ENGINE",              A320_REG_OFN_ENGINE        },
    {"OFN_RESOLUTION",          A320_REG_OFN_RESOLUTION    },
    {"OFN_SPEED_CONTROL",       A320_REG_OFN_SPEED_CONTROL },
    {"OFN_SPEED_ST12",          A320_REG_OFN_SPEED_ST12    },
    {"OFN_SPEED_ST21",          A320_REG_OFN_SPEED_ST21    },
    {"OFN_SPEED_ST23",          A320_REG_OFN_SPEED_ST23    },
    {"OFN_SPEED_ST32",          A320_REG_OFN_SPEED_ST32    },
    {"OFN_SPEED_ST34",          A320_REG_OFN_SPEED_ST34    },
    {"OFN_SPEED_ST43",          A320_REG_OFN_SPEED_ST43    },
    {"OFN_SPEED_ST45",          A320_REG_OFN_SPEED_ST45    },
    {"OFN_SPEED_ST54",          A320_REG_OFN_SPEED_ST54    },
    {"OFN_AD_CTRL",             A320_REG_OFN_AD_CTRL       },
    {"OFN_AD_ATH_HIGH",         A320_REG_OFN_AD_ATH_HIGH   },
    {"OFN_AD_DTH_HIGH",         A320_REG_OFN_AD_DTH_HIGH   },
    {"OFN_AD_ATH_LOW",          A320_REG_OFN_AD_ATH_LOW    },
    {"OFN_AD_DTH_LOW",          A320_REG_OFN_AD_DTH_LOW    },
    {"OFN_QUANTIZE_CTRL",       A320_REG_OFN_QUANTIZE_CTRL },
    {"OFN_XYQ_THRESH",          A320_REG_OFN_XYQ_THRESH    },
    {"OFN_FPD_CTRL",            A320_REG_OFN_FPD_CTRL      },
    {"OFN_ORIENTATION",         A320_REG_OFN_ORIENTATION   },
};
static struct timeval t1,t2;
/******************************************************************************
 * Sysfs attributes
*******************************************************************************/
int a320_read_byte(struct i2c_client *client, u8 addr, u8 *data)
{
    u8 buf;
    int ret = 0;
    
    buf = addr;
    ret = i2c_master_send(client, (const char*)&buf, 1);
    if (ret < 0) {
        AVA_ERR("send command error!!\n");
        return -EFAULT;
    }
    ret = i2c_master_recv(client, (char*)&buf, 1);
    if (ret < 0) {
        AVA_ERR("reads data error!!\n");
        return -EFAULT;
    } else {
#if defined(A320_DEBUG_RW)    
        AVA_LOG("%s(0x%02X) = %02X\n", __func__, addr, buf);    
#endif
    }
    *data = buf;
    return 0;
}
/*----------------------------------------------------------------------------*/
int a320_write_byte(struct i2c_client *client, u8 addr, u8 data)
{
    u8 buf[] = {addr, data};
    int ret = 0;

    ret = i2c_master_send(client, (const char*)buf, sizeof(buf));
    if (ret < 0) {
        AVA_ERR("send command error!!\n");
        return -EFAULT;
    } else {
#if defined(A320_DEBUG_RW)    
        AVA_LOG("%s(0x%02X)= %02X\n", __func__, addr, data);
#endif
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
int a320_set_bits(struct i2c_client *client, u8 addr, u8 bits)
{
    int err;
    u8 cur, nxt;

    if ((err = a320_read_byte(client, addr, &cur))) {
        AVA_ERR("read err: 0x%02X\n", addr);
        return -EFAULT;
    }
    
    nxt = (cur | bits);

    if (nxt ^ cur) {
        if ((err = a320_write_byte(client, addr, nxt))) {
            AVA_ERR("write err: 0x%02X\n", addr);
            return -EFAULT;
        }
    }
    return 0;    
}
/*----------------------------------------------------------------------------*/
int a320_clr_bits(struct i2c_client *client, u8 addr, u8 bits)
{
    int err;
    u8 cur, nxt;

    if ((err = a320_read_byte(client, addr, &cur))) {
        AVA_ERR("read err: 0x%02X\n", addr);
        return -EFAULT;
    }
    
    nxt = cur & (~bits);
    
    if (nxt ^ cur) {
        if ((err = a320_write_byte(client, addr, nxt))) {
            AVA_ERR("write err: 0x%02X\n", addr);
            return -EFAULT;
        }
    }
    return 0;    
}
/*----------------------------------------------------------------------------*/
int a320_read_block(struct i2c_client *client, u8 addr, u8 *data, u8 len)
{
    if (len == 1) {
        return a320_read_byte(client, addr, data);
    } else {
        u8 beg = addr; 
        struct i2c_msg msgs[2] = {
            {
                .addr = client->addr,    .flags = 0,
                .len = 1,                .buf= &beg
            },
            {
                .addr = client->addr,    .flags = I2C_M_RD,
                .len = len,             .buf = data,
            }
        };
        int err;

        if (!client)
            return -EINVAL;
        else if (len > C_I2C_FIFO_SIZE) {        
            AVA_ERR(" length %d exceeds %d\n", len, C_I2C_FIFO_SIZE);
            return -EINVAL;
        }

        err = i2c_transfer(client->adapter, msgs, sizeof(msgs)/sizeof(msgs[0]));
        if (err != 2) {
            AVA_ERR("i2c_transfer error: (%d %p %d) %d\n", addr, data, len, err);
            err = -EIO;
        } else {
#if defined(A320_DEBUG_RW)        
            static char buf[128];
            int idx, buflen = 0;
            for (idx = 0; idx < len; idx++)
                buflen += snprintf(buf+buflen, sizeof(buf)-buflen, "%02X ", data[idx]);
            AVA_LOG("%s(0x%02X,%2d) = %s\n", __func__, addr, len, buf);
#endif             
            err = 0;    /*no error*/
        }
        return err;
    }

}
/*----------------------------------------------------------------------------*/
int a320_write_block(struct i2c_client *client, u8 addr, u8 *data, u8 len)
{   /*because address also occupies one byte, the maximum length for write is 7 bytes*/
    int err, idx, num;
    char buf[C_I2C_FIFO_SIZE];

    if (!client)
        return -EINVAL;
    else if (len >= C_I2C_FIFO_SIZE) {        
        AVA_ERR(" length %d exceeds %d\n", len, C_I2C_FIFO_SIZE);
        return -EINVAL;
    }    

    num = 0;
    buf[num++] = addr;
    for (idx = 0; idx < len; idx++)
        buf[num++] = data[idx];

    err = i2c_master_send(client, buf, num);
    if (err < 0) {
        AVA_ERR("send command error!!\n");
        return -EFAULT;
    } else {
#if defined(A320_DEBUG_RW)    
        static char buf[128];
        int idx, buflen = 0;
        for (idx = 0; idx < len; idx++)
            buflen += snprintf(buf+buflen, sizeof(buf)-buflen, "%02X ", data[idx]);
        AVA_LOG("%s(0x%02X,%2d)= %s\n", __func__, addr, len, buf);    
#endif        
        err = 0;    /*no error*/
    }
    return err;
}
/******************************************************************************
 * Sysfs attributes
*******************************************************************************/
static ssize_t a320_show_trace(struct device *dev, 
                               struct device_attribute *attr, char *buf)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct a320_priv *obj = i2c_get_clientdata(client);
    
	return snprintf(buf, PAGE_SIZE, "0x%08X\n", atomic_read(&obj->trace));
}
/*----------------------------------------------------------------------------*/
static ssize_t a320_store_trace(struct device* dev, 
                                struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
    struct a320_priv *obj = i2c_get_clientdata(client);    
    int trc;

    if (1 == sscanf(buf, "0x%x\n", &trc)) 
        atomic_set(&obj->trace, trc);
    else
        AVA_ERR("set trace level fail!!\n");
    return count;
}                
/*----------------------------------------------------------------------------*/
static ssize_t a320_show_data(struct device *dev, 
                               struct device_attribute *attr, char *buf)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct a320_priv *obj = i2c_get_clientdata(client);
    u8 dat[3];
    int idx, err;

    for (idx = 0; idx < sizeof(dat); idx++) {
        if ((err = a320_read_byte(obj->client, A320_REG_MOTION+idx, &dat[idx]))) {
            AVA_ERR("read fail: %d\n", err);
            break;
        }
    }
            
	return snprintf(buf, PAGE_SIZE, "0x%02X => [0x%02X 0x%02X]: %d\n", dat[0], dat[1], dat[2], mt_get_gpio_in(GPIO_OFN_EINT_PIN));
}
/*----------------------------------------------------------------------------*/
static ssize_t a320_show_dump(struct device *dev, 
                               struct device_attribute *attr, char *buf)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct a320_priv *obj = i2c_get_clientdata(client);
    u8 dat;
    int idx, err;
    int len = 0;

    for (idx = 0; idx < sizeof(a320_regs)/sizeof(a320_regs[0]); idx++) {
        if ((err = a320_read_byte(obj->client, a320_regs[idx].addr, &dat))) {
            AVA_ERR("read data fail: %d\n", err);
            break;
        }
        len += snprintf(buf+len, PAGE_SIZE-len, "%-20s = 0x%02X\n", a320_regs[idx].name, dat);
    }
        
	return len;
}
/*----------------------------------------------------------------------------*/
static ssize_t a320_show_tbcnf(struct device *dev, 
                               struct device_attribute *attr, char *buf)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct a320_priv *obj = i2c_get_clientdata(client);

    if (!dev || !client) {
        AVA_ERR("null pointer: %p %p!!\n", dev, client);
        return 0;
    } else if (!(obj = (struct a320_priv*)i2c_get_clientdata(client))) {
        AVA_ERR("null client data\n");
        return 0;    
    }

    return snprintf(buf, PAGE_SIZE, "(%d %d %d %d)\n", atomic_read(&obj->quan_x),
                    atomic_read(&obj->quan_y), atomic_read(&obj->accu_max),
                    atomic_read(&obj->tb_inact_cnt));
}
/*----------------------------------------------------------------------------*/
static ssize_t a320_store_tbcnf(struct device* dev, 
                                struct device_attribute *attr, const char *buf, size_t count)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct a320_priv *obj = i2c_get_clientdata(client);
    int quan_x, quan_y, inact_cnt, accu_max;

    if (!dev || !client) {
        AVA_ERR("null pointer: %p %p!!\n", dev, client);
    } else if (!(obj = (struct a320_priv*)i2c_get_clientdata(client))) {
        AVA_ERR("null client data\n");
    } else if (4 == sscanf(buf, "%d %d %d %d", &quan_x, &quan_y, &accu_max, &inact_cnt)) {
        atomic_set(&obj->quan_x, quan_x);
        atomic_set(&obj->quan_y, quan_y);
        atomic_set(&obj->accu_max, accu_max);
        atomic_set(&obj->tb_inact_cnt, inact_cnt);
    } else {
        AVA_ERR("invalid format '%s'\n", buf);
    }
    return count;
}
/*----------------------------------------------------------------------------*/
static ssize_t a320_show_kbcnf(struct device *dev, 
                               struct device_attribute *attr, char *buf)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct a320_priv *obj = i2c_get_clientdata(client);

    if (!dev || !client) {
        AVA_ERR("null pointer: %p %p!!\n", dev, client);
        return 0;
    } else if (!(obj = (struct a320_priv*)i2c_get_clientdata(client))) {
        AVA_ERR("null client data\n");
        return 0;    
    }

    return snprintf(buf, PAGE_SIZE, "(%d %d %d %d %d)\n",  
                    atomic_read(&obj->acc_cnt), atomic_read(&obj->inact_cnt), 
                    atomic_read(&obj->act_cnt), atomic_read(&obj->sup_cnt), atomic_read(&obj->step));
}
/*----------------------------------------------------------------------------*/
static ssize_t a320_store_kbcnf(struct device* dev, 
                                struct device_attribute *attr, const char *buf, size_t count)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct a320_priv *obj = i2c_get_clientdata(client);
    int acc, inact, act, sup, step;

    if (!dev || !client) {
        AVA_ERR("null pointer: %p %p!!\n", dev, client);
    } else if (!(obj = (struct a320_priv*)i2c_get_clientdata(client))) {
        AVA_ERR("null client data\n");
    } else if (5 == sscanf(buf, "%d %d %d %d %d", &acc, &inact, &act, &sup, &step)) {
        atomic_set(&obj->acc_cnt, acc);
        atomic_set(&obj->inact_cnt, inact);
        atomic_set(&obj->act_cnt, act);
        atomic_set(&obj->sup_cnt, sup);
        atomic_set(&obj->step, step);
    } else {
        AVA_ERR("invalid format '%s'\n", buf);
    }
    return count;
}
/*----------------------------------------------------------------------------*/
static ssize_t a320_show_eint(struct device* dev, 
                             struct device_attribute *attr, char *buf)
{
    #define READREG(ADDR) (*(volatile unsigned int *)(ADDR))
    struct i2c_client *client = to_i2c_client(dev);
    struct a320_priv *obj = i2c_get_clientdata(client);
    int len = 0;

    if (!dev || !client) {
        AVA_ERR("null pointer: %p %p!!\n", dev, client);
        return 0;
    } else if (!(obj = (struct a320_priv*)i2c_get_clientdata(client))) {
        AVA_ERR("null client data\n");
        return 0;
    }    
#if 0
    len += snprintf(buf+len, PAGE_SIZE-len, "IRQ_SEL : ");
    len += snprintf(buf+len, PAGE_SIZE-len, "%08X %08X %08X %08X %08X %08X %08X %08X\n",
                    READREG(MT6573_IRQ_SEL0), READREG(MT6573_IRQ_SEL1), READREG(MT6573_IRQ_SEL2), READREG(MT6573_IRQ_SEL3),
                    READREG(MT6573_IRQ_SEL4), READREG(MT6573_IRQ_SEL5), READREG(MT6573_IRQ_SEL6), READREG(MT6573_IRQ_SEL7));
    len += snprintf(buf+len, PAGE_SIZE-len, "FIQ_SEL : %08X\n", READREG(MT6573_FIQ_SEL));
    len += snprintf(buf+len, PAGE_SIZE-len, "IRQ_MASK: %08X %08X %08X %08X %08X %08X\n",
                    READREG(MT6573_IRQ_MASKL), READREG(MT6573_IRQ_MASKH), 
                    READREG(MT6573_IRQ_MASK_CLRL), READREG(MT6573_IRQ_MASK_CLRH),
                    READREG(MT6573_IRQ_MASK_SETL), READREG(MT6573_IRQ_MASK_SETH));
    len += snprintf(buf+len, PAGE_SIZE-len, "IRQ_STA : %08X %08X\n", 
                    READREG(MT6573_IRQ_STAL), READREG(MT6573_IRQ_STAH));
    len += snprintf(buf+len, PAGE_SIZE-len, "IRQ_EOI : %08X %08X\n",
                    READREG(MT6573_IRQ_EOIL), READREG(MT6573_IRQ_EOIH));
    len += snprintf(buf+len, PAGE_SIZE-len, "IRQ_SENS: %08X %08X\n",
                    READREG(MT6573_IRQ_SENSL), READREG(MT6573_IRQ_SENSH));
    len += snprintf(buf+len, PAGE_SIZE-len, "IRQ_SOFT: %08X %08X\n",
                    READREG(MT6573_IRQ_SOFTL), READREG(MT6573_IRQ_SOFTH));
    len += snprintf(buf+len, PAGE_SIZE-len, "FIQ_CON : %08X\n", READREG(MT6573_FIQ_CON));
    len += snprintf(buf+len, PAGE_SIZE-len, "FIQ_CON : %08X\n", READREG(MT6573_FIQ_EOI));
    len += snprintf(buf+len, PAGE_SIZE-len, "IRQ_STA2: %08X\n", READREG(MT6573_IRQ_STA2));
    len += snprintf(buf+len, PAGE_SIZE-len, "IRQ_EOI2: %08X\n", READREG(MT6573_IRQ_EOI2));
    len += snprintf(buf+len, PAGE_SIZE-len, "IRQ_SFT2: %08X\n", READREG(MT6573_IRQ_SOFT2));
    len += snprintf(buf+len, PAGE_SIZE-len, "EINTSTA : %08X\n", READREG(MT6573_EINT_STATUS));
    len += snprintf(buf+len, PAGE_SIZE-len, "EINTMASK: %08X\n", READREG(MT6573_EINT_MASK));
    len += snprintf(buf+len, PAGE_SIZE-len, "EINTMSKC: %08X\n", READREG(MT6573_EINT_MASK_CLR));
    len += snprintf(buf+len, PAGE_SIZE-len, "EINTMSKS: %08X\n", READREG(MT6573_EINT_MASK_SET));
    len += snprintf(buf+len, PAGE_SIZE-len, "EINTINTA: %08X\n", READREG(MT6573_EINT_INTACK));
    len += snprintf(buf+len, PAGE_SIZE-len, "EINTSENS: %08X\n", READREG(MT6573_EINT_SENS));
    len += snprintf(buf+len, PAGE_SIZE-len, "EINTCN00: %08X %08X %08X %08X %08X %08X %08X %08X\n",
                    READREG(MT6573_EINT0_CON), READREG(MT6573_EINT1_CON), READREG(MT6573_EINT2_CON), READREG(MT6573_EINT3_CON),
                    READREG(MT6573_EINT4_CON), READREG(MT6573_EINT5_CON), READREG(MT6573_EINT6_CON), READREG(MT6573_EINT7_CON));
    len += snprintf(buf+len, PAGE_SIZE-len, "EINTCN08: %08X %08X %08X %08X %08X %08X %08X %08X\n",
                    READREG(MT6573_EINT8_CON), READREG(MT6573_EINT9_CON), READREG(MT6573_EINT10_CON), READREG(MT6573_EINT11_CON),
                    READREG(MT6573_EINT12_CON), READREG(MT6573_EINT13_CON), READREG(MT6573_EINT14_CON), READREG(MT6573_EINT15_CON));
    len += snprintf(buf+len, PAGE_SIZE-len, "EINTCN16: %08X %08X %08X %08X %08X %08X %08X %08X\n",
                    READREG(MT6573_EINT16_CON), READREG(MT6573_EINT17_CON), READREG(MT6573_EINT18_CON), READREG(MT6573_EINT19_CON),
                    READREG(MT6573_EINT20_CON), READREG(MT6573_EINT21_CON), READREG(MT6573_EINT22_CON), READREG(MT6573_EINT23_CON));
#endif   
    return len;    
}
/*----------------------------------------------------------------------------*/
static ssize_t a320_store_eint(struct device* dev, struct device_attribute *attr,
                              const char *buf, size_t count)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct a320_priv *obj = i2c_get_clientdata(client);
//    char cmd[10];
//    int eint;
    if (!dev) {
        AVA_ERR("dev is null!!\n");
        return 0;
    } else if (!(obj = (struct a320_priv*)dev_get_drvdata(dev))) {
        AVA_ERR("drv data is null!!\n");
        return 0;
    }
#if 0    
    if (2 == sscanf(buf, "%s %d", cmd, &eint)) {
        if (eint >= 23) {
            AVA_ERR("invalid eintno: %d\n", eint);
        } else if (0 == strncmp(cmd, "ack", sizeof(cmd)))  {
            *MT6573_EINT_INTACK = (1 << (eint));
        } else if (0 == strncmp(cmd, "mask", sizeof(cmd))) {
            *MT6573_EINT_MASK_SET = (1 << eint);
        } else if (0 == strncmp(cmd, "unmask", sizeof(cmd))) {
            *MT6573_EINT_MASK_CLR = (1 << eint);
        } else {
            AVA_ERR("invalid cmd: '%s'\n", cmd);
        }
    } else {
        AVA_ERR("invalid content: '%s', length = %d\n", buf, count);
    }
#endif    
    return count;    
}  
/*----------------------------------------------------------------------------*/
static ssize_t a320_store_status(struct device* dev, struct device_attribute *attr,
                              const char *buf, size_t count)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct a320_priv *obj = i2c_get_clientdata(client);
    int rst = 0;
    if (!dev) {
        AVA_ERR("dev is null!!\n");
        return 0;
    } else if (!(obj = (struct a320_priv*)dev_get_drvdata(dev))) {
        AVA_ERR("drv data is null!!\n");
        return 0;
    }
    if (1 == sscanf(buf, "%d", &rst)) {
        if (rst)
            a320_reset_and_init(client);
    } else {
        AVA_ERR("invalid content: '%s', length = %d\n", buf, count);
    }
    return count;    
}  
/*----------------------------------------------------------------------------*/
static ssize_t a320_show_status(struct device *dev, 
                               struct device_attribute *attr, char *buf)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct a320_priv *obj = i2c_get_clientdata(client);
    ssize_t len = 0;
    int err;
    u8 data;

    if (!dev || !client) {
        AVA_ERR("null pointer: %p %p!!\n", dev, client);
        return 0;
    } else if (!(obj = (struct a320_priv*)i2c_get_clientdata(client))) {
        AVA_ERR("null client data\n");
        return 0;    
    }
    if (obj->hw) {
        len += snprintf(buf+len, PAGE_SIZE-len, 
               "CUST: %d %d (%d %d) (%d 0x%02X) (0x%02X)\n",
               obj->hw->chip_id, obj->hw->report_cls, obj->hw->power_id, obj->hw->power_vol,
               obj->hw->i2c_num, obj->hw->slave_addr, obj->hw->layout);
        len += snprintf(buf+len, PAGE_SIZE-len, 
               "CUST: (tb) (%d %d)\n", obj->hw->quan_x, obj->hw->quan_y);
        len += snprintf(buf+len, PAGE_SIZE-len, 
               "CUST: (kb) (%d %d %d) (%d %d %d %d %d)\n", obj->hw->detect, obj->hw->gpt_num, obj->hw->gpt_period,
               obj->hw->acc_cnt, obj->hw->inact_cnt, obj->hw->act_cnt, obj->hw->sup_cnt, obj->hw->step);                
    } else {
        len += snprintf(buf+len, PAGE_SIZE-len, "CUST: NULL\n");
    }

    len += snprintf(buf+len, PAGE_SIZE-len, "GPIO: (%d %d %d %d %d)\n", GPIO_OFN_EINT_PIN, 
           mt_get_gpio_dir(GPIO_OFN_EINT_PIN), mt_get_gpio_mode(GPIO_OFN_EINT_PIN), 
           mt_get_gpio_pull_enable(GPIO_OFN_EINT_PIN), mt_get_gpio_pull_select(GPIO_OFN_EINT_PIN));
    len += snprintf(buf+len, PAGE_SIZE-len, "EINT: (%d %d %d %d)\n", 
           CUST_EINT_OFN_NUM, CUST_EINT_OFN_POLARITY, CUST_EINT_OFN_DEBOUNCE_EN, CUST_EINT_OFN_DEBOUNCE_CN);

    if ((err = a320_read_byte(obj->client, 0x77, &data))) 
        len += snprintf(buf+len, PAGE_SIZE-len, "LAYOUT: err = %d\n", err);
    else
        len += snprintf(buf+len, PAGE_SIZE-len, "LAYOUT: 0x%02X\n", data);
    return len;
}
/*----------------------------------------------------------------------------*/
static SENSOR_DEVICE_ATTR(trace         , 0664, a320_show_trace,  a320_store_trace,  0);
static SENSOR_DEVICE_ATTR(data          , 0664, a320_show_data,   NULL,  0);
static SENSOR_DEVICE_ATTR(dump          , 0664, a320_show_dump,   NULL,  0);
static SENSOR_DEVICE_ATTR(tbcnf         , 0664, a320_show_tbcnf,  a320_store_tbcnf,  0);
static SENSOR_DEVICE_ATTR(kbcnf         , 0664, a320_show_kbcnf,  a320_store_kbcnf,  0);
static SENSOR_DEVICE_ATTR(eint          , 0664, a320_show_eint,   a320_store_eint,  0);
static SENSOR_DEVICE_ATTR(status        , 0664, a320_show_status, a320_store_status,  0);
/*----------------------------------------------------------------------------*/
static struct attribute *a320_attributes[] = {
	&sensor_dev_attr_trace.dev_attr.attr,   /*!< trace level */
	&sensor_dev_attr_data.dev_attr.attr,    /*!< dump dx, dy read from register & motion interrupt status */
	&sensor_dev_attr_dump.dev_attr.attr,    /*!< dump count of all registers */
	&sensor_dev_attr_eint.dev_attr.attr,	/*!< dump cotent of eint register */
	&sensor_dev_attr_kbcnf.dev_attr.attr,	/*!< the config of keyboard class */
	&sensor_dev_attr_tbcnf.dev_attr.attr,	/*!< the config of trackball class */ 
	&sensor_dev_attr_status.dev_attr.attr,	/*!< status */ 
	NULL
};
/*----------------------------------------------------------------------------*/
static const struct attribute_group a320_group = {
	.attrs = a320_attributes,
};
/******************************************************************************
 *             Common function: EINT implementation
*******************************************************************************/
static void a320_power(struct ofn_hw *hw, unsigned int on) 
{
    static unsigned int power_on = 0;

    if (hw->power_id != MT65XX_POWER_NONE) {        
        AVA_LOG("power %s\n", on ? "on" : "off");
        if (power_on == on) {
            AVA_LOG("ignore power control: %d\n", on);
        } else if (on) {
            if (!hwPowerOn(hw->power_id, hw->power_vol, "A320")) 
                AVA_ERR("power on fails!!\n");
        } else {
            if (!hwPowerDown(hw->power_id, "A320")) 
                AVA_ERR("power off fail!!\n");   
        }
    }
    power_on = on;    
}
/*----------------------------------------------------------------------------*/
static int a320_init_gpio(struct a320_priv *obj)
{    
    mt_set_gpio_mode(GPIO_OFN_DWN_PIN, GPIO_OFN_DWN_PIN_M_GPIO);
    mt_set_gpio_dir(GPIO_OFN_DWN_PIN, GPIO_DIR_OUT);
    mt_set_gpio_out(GPIO_OFN_DWN_PIN, GPIO_OUT_ONE);    /*push device to shutdown mode*/

    mt_set_gpio_mode(GPIO_OFN_RST_PIN, GPIO_OFN_DWN_PIN_M_GPIO);
    mt_set_gpio_dir(GPIO_OFN_RST_PIN, GPIO_DIR_OUT);
    mt_set_gpio_out(GPIO_OFN_RST_PIN, GPIO_OUT_ZERO);   /*push device to shutdown mode*/
    return 0;
}
/*----------------------------------------------------------------------------*/
int a320_setup_eint(struct a320_priv *obj, void (*eint_motion)(void))
{
    /*configure to GPIO function, external interrupt*/
    mt_set_gpio_dir(GPIO_OFN_EINT_PIN, GPIO_DIR_IN);
    mt_set_gpio_mode(GPIO_OFN_EINT_PIN, GPIO_OFN_EINT_PIN_M_EINT);
    mt_set_gpio_pull_enable(GPIO_OFN_EINT_PIN, TRUE);
    mt_set_gpio_pull_select(GPIO_OFN_EINT_PIN, GPIO_PULL_UP);

    mt65xx_eint_set_sens(CUST_EINT_OFN_NUM, CUST_EINT_OFN_SENSITIVE);
    mt65xx_eint_set_polarity(CUST_EINT_OFN_NUM, CUST_EINT_OFN_POLARITY);
    mt65xx_eint_set_hw_debounce(CUST_EINT_OFN_NUM, CUST_EINT_OFN_DEBOUNCE_CN);
    mt65xx_eint_registration(CUST_EINT_OFN_NUM, CUST_EINT_OFN_DEBOUNCE_EN, CUST_EINT_OFN_POLARITY, eint_motion, 0);

    mt65xx_eint_unmask(CUST_EINT_OFN_NUM);
    return 0;
}

/******************************************************************************
 *         Keyboard class: Algorithm for reporting key event
*******************************************************************************/
int64_t a320_get_timecount(void)
{
    struct timeval tv;
    int64_t count;

    do_gettimeofday(&tv);
    count = tv.tv_sec*1000 + tv.tv_usec/1000; /*convert to millisecond*/
    return count;
}
#if 0
/*----------------------------------------------------------------------------*/
static int a320_report(struct a320_priv* obj)
{
    int idx, len = 0, trc = atomic_read(&obj->trace), report = 0, flag = 0;    
    int err, step = atomic_read(&obj->step), sup_cnt = atomic_read(&obj->sup_cnt);   
    u8  status, delta_x, delta_y;
    char buf[512];    
    struct a320_dir *dir = NULL;
    int64_t diff, timecnt = a320_get_timecount();    
    signed char diff_x, diff_y;

    if ((err = a320_read_byte(obj->client, A320_REG_MOTION, &status))) {
        AVA_ERR("read status fail: %d\n", err);
        return err;
    }

    if ((err = a320_read_byte(obj->client, A320_REG_DELTA_X, &delta_x))) {
        AVA_ERR("read delta_x fail: %d\n", err);
        return err;
    }

    if ((err = a320_read_byte(obj->client, A320_REG_DELTA_Y, &delta_y))) {
        AVA_ERR("read delta_y fail: %d\n", err);
        return err;
    }
    
    diff_x = (signed char)delta_x;
    diff_y = (signed char)delta_y;

    if (0 == (status & MOTION)) {
        if (trc & AVA_TRC_MOTION)
            AVA_LOG("MOTION: 0, (X,Y) = (%+3d, %+3d)\n", diff_x, diff_y);        
        return -EAGAIN;
    } else {
        int abs_y = abs(diff_y);
        int abs_x = abs(diff_x);

        if (abs_x > sup_cnt) 
            abs_x = sup_cnt;
        if (abs_y > sup_cnt) 
            abs_y = sup_cnt;
        if (diff_y > 0) {
            atomic_set(&obj->dir[AVA_DIR_UP].val, abs_y);
            atomic_set(&obj->dir[AVA_DIR_DN].cnt, 0);
            set_bit(AVA_DIR_UP, &obj->pending);
        } else if (diff_y < 0) {
            atomic_set(&obj->dir[AVA_DIR_DN].val, abs_y);
            atomic_set(&obj->dir[AVA_DIR_UP].cnt, 0);
            set_bit(AVA_DIR_DN, &obj->pending);
        }
        if (diff_x > 0) {
            atomic_set(&obj->dir[AVA_DIR_RG].val, abs_x);
            atomic_set(&obj->dir[AVA_DIR_LF].cnt, 0);
            set_bit(AVA_DIR_RG, &obj->pending);
        } else if (diff_x < 0) {
            atomic_set(&obj->dir[AVA_DIR_LF].val, abs_x);
            atomic_set(&obj->dir[AVA_DIR_RG].cnt, 0);
            set_bit(AVA_DIR_LF, &obj->pending);
        }
    }

    if (trc & AVA_TRC_WORK)
        len += snprintf(buf + len, sizeof(buf)-len, "[%2X](%+3d, %+3d) (", (unsigned int)obj->pending, diff_x, diff_y);
    for (idx = 0; idx < AVA_DIR_NUM; idx++) {
        dir = &obj->dir[idx];
        diff = timecnt - dir->last_trig;
        if (trc & AVA_TRC_WORK) 
            len += snprintf(buf + len, sizeof(buf)-len, "%8lld ", diff);
        if ((timecnt - dir->first_acc) >= atomic_read(&obj->acc_cnt)) {
            atomic_set(&dir->cnt, 0);
            dir->first_acc = 0;
        }         
        if (diff > atomic_read(&obj->inact_cnt))
            atomic_set(&dir->cnt, 0);
        if (!test_and_clear_bit(idx, &obj->pending))
            continue;

        dir->last_trig = timecnt;
        if (diff > atomic_read(&obj->act_cnt)) {          
            if (atomic_read(&dir->cnt) == 0) 
                dir->first_acc = timecnt;
            atomic_add(atomic_read(&dir->val), &dir->cnt);            
        }
        if (atomic_read(&dir->cnt) > step) {
            input_report_key(obj->dev, dir->key_evt, 1);
            kpd_backlight_handler(1, dir->key_evt);
            input_report_key(obj->dev, dir->key_evt, 0);
            kpd_backlight_handler(0, dir->key_evt);
            input_sync(obj->dev);
            atomic_set(&dir->cnt, 0);
            report |= (1 << idx);
        }

        flag |= (1 << idx);
    }
       
    if (trc & AVA_TRC_WORK) {
        char ptr[8];
        memset(ptr, ' ', sizeof(ptr));
        if (report & AVA_BIT_UP)
            ptr[0] = 'U';
        if (report & AVA_BIT_DN)
            ptr[2] = 'D';
        if (report & AVA_BIT_LF)
            ptr[4] = 'L';
        if (report & AVA_BIT_RG)
            ptr[6] = 'R';
        ptr[7] = 0;
        len = snprintf(buf + len, sizeof(buf)-len, ") (%2d %2d %2d %2d) (%02X) %s\n", 
                       atomic_read(&obj->dir[AVA_DIR_UP].cnt), atomic_read(&obj->dir[AVA_DIR_DN].cnt),
                       atomic_read(&obj->dir[AVA_DIR_LF].cnt), atomic_read(&obj->dir[AVA_DIR_RG].cnt),
                       flag, ptr);
        AVA_MSG("(%4lld %4llu %4llu %4llu) ", 
                (obj->dir[AVA_DIR_UP].first_acc) ? (timecnt - obj->dir[AVA_DIR_UP].first_acc) : (0), 
                (obj->dir[AVA_DIR_DN].first_acc) ? (timecnt - obj->dir[AVA_DIR_DN].first_acc) : (0), 
                (obj->dir[AVA_DIR_LF].first_acc) ? (timecnt - obj->dir[AVA_DIR_LF].first_acc) : (0), 
                (obj->dir[AVA_DIR_RG].first_acc) ? (timecnt - obj->dir[AVA_DIR_RG].first_acc) : (0));        
        AVA_MSG("%s", buf);
    }
    return 0;
}
/******************************************************************************
 *             Keyboard Class: EINT implementation
*******************************************************************************/
void a320_eint_key_motion(void)
{
    struct a320_priv *obj = g_a320_ptr;
    if (!obj)
        return;

    schedule_work(&obj->eint_key_work);
    if (atomic_read(&obj->trace) & AVA_TRC_EINT)
        AVA_LOG("eint: motion interrupt\n");
}
/*----------------------------------------------------------------------------*/
static void a320_eint_key_work(struct work_struct *work)
{
    struct a320_priv *obj = (struct a320_priv *)container_of(work, struct a320_priv, eint_key_work);

    a320_report(obj);
    mt65xx_eint_unmask(CUST_EINT_OFN_NUM);      
}
/******************************************************************************
 *           Keyboard Class: POLL implementation
*******************************************************************************/
void a320_gpt_isr(u16 unused) 
{
    struct a320_priv *obj = g_a320_ptr;
    
    if (!obj)
        return;

    schedule_work(&obj->poll_key_work);
}
/*----------------------------------------------------------------------------*/
int a320_XGPTConfig(struct a320_priv *obj)
{
    XGPT_CONFIG config;
    XGPT_NUM  gpt_num = obj->hw->gpt_num;    
    XGPT_CLK_DIV clkDiv = XGPT_CLK_DIV_1;

    XGPT_Reset(gpt_num);   
    XGPT_Init (gpt_num, a320_gpt_isr);
    config.num = gpt_num;
    config.mode = XGPT_REPEAT;
    config.clkDiv = clkDiv;
    config.bIrqEnable = TRUE;
    config.u4Compare = obj->hw->gpt_period;
    
    if (XGPT_Config(config) == FALSE)
        return -1;                    
        
    XGPT_Start(gpt_num);           
	return 0;
}
/*----------------------------------------------------------------------------*/
int a320_setup_poll(struct a320_priv *obj)
{
    int err;

    AVA_FUN();
    /*configure to GPIO function, input*/
    mt_set_gpio_dir(GPIO_OFN_EINT_PIN, GPIO_DIR_IN);
    mt_set_gpio_mode(GPIO_OFN_EINT_PIN, GPIO_OFN_EINT_PIN_M_EINT);
    mt_set_gpio_pull_enable(GPIO_OFN_EINT_PIN, TRUE);
    mt_set_gpio_pull_select(GPIO_OFN_EINT_PIN, GPIO_PULL_UP);
    
    if ((err = a320_XGPTConfig(obj)))
        return err;
    return 0;
}
/*----------------------------------------------------------------------------*/
static void a320_poll_key_work(struct work_struct *work) 
{
    struct a320_priv *obj = (struct a320_priv *)container_of(work, struct a320_priv, poll_key_work);
    u8 dat[3];
    int idx, err, trc = atomic_read(&obj->trace);

    for (idx = 0; idx < sizeof(dat); idx++) {
        if ((err = a320_read_byte(obj->client, A320_REG_MOTION+idx, &dat[idx]))) {
            AVA_ERR("read fail: %d\n", err);
            break;
        }
    }
    if (trc & AVA_TRC_MOTION)
    	AVA_LOG("0x%02X => [0x%02X 0x%02X]: %d\n", dat[0], dat[1], dat[2], mt_get_gpio_in(GPIO_OFN_EINT_PIN));
    a320_report(obj);
}
/******************************************************************************
 *           Keyboard Class: setup function
*******************************************************************************/
static int a320_setup_class_key(struct a320_priv *obj)
{   
    /*NOTICE: the polling mode could be used only if OFN is the only one client in the i2c bus*/
    AVA_FUN();    
    g_a320_ptr = obj;    
    if (atomic_read(&obj->detect) == AVA_DETECT_EINT) 
        return a320_setup_eint(obj, a320_eint_key_motion);
    else if (atomic_read(&obj->detect) == AVA_DETECT_POLL) 
        return a320_setup_poll(obj);
    return -EINVAL;
}
#endif
/******************************************************************************
 *             Trackball Class: EINT implementation
*******************************************************************************/
static void a320_eint_ball_work(struct work_struct *work) 
{
    struct a320_priv *obj = (struct a320_priv *)container_of(work, struct a320_priv, eint_ball_work);
    int err, dx = 0, dy = 0, trc = atomic_read(&obj->trace);   
    u8  status, delta_x, delta_y;
    int quan_x = atomic_read(&obj->quan_x), quan_y = atomic_read(&obj->quan_y);
    int accu_max = atomic_read(&obj->accu_max), accu_dx, accu_dy;
    signed char diff_x, diff_y;
    int64_t curtime, diff;

    /*the specification suggest that the three values should be read continously*/
    if ((err = a320_read_byte(obj->client, A320_REG_MOTION, &status))) {
        AVA_ERR("read status fail: %d\n", err);
        goto exit;
    }

    if ((err = a320_read_byte(obj->client, A320_REG_DELTA_X, &delta_x))) {
        AVA_ERR("read delta_x fail: %d\n", err);
        goto exit;
    }

    if ((err = a320_read_byte(obj->client, A320_REG_DELTA_Y, &delta_y))) {
        AVA_ERR("read delta_y fail: %d\n", err);
        goto exit;
    }
    
    diff_x = (signed char)delta_x;
    diff_y = (signed char)delta_y;   

    if (0 == (status & MOTION)) {
        if (trc & AVA_TRC_MOTION)
            AVA_LOG("MOTION: 0, (X,Y) = (%+4d, %+4d)\n", diff_x, diff_y);        
        goto exit;
    } else {
    #if defined(CONFIG_ACCU_COUNT)
        curtime = a320_get_timecount();
        diff = curtime - obj->last_time;
        if (diff > atomic_read(&obj->tb_inact_cnt)) 
            obj->accu_dx = obj->accu_dy = 0;
        if (diff_x > 0)    
            accu_dx = (diff_x >  accu_max) ? ( accu_max) : (diff_x);
        else
            accu_dx = (diff_x < -accu_max) ? (-accu_max) : (diff_x);
        if (diff_y > 0)
            accu_dy = (diff_y >  accu_max) ? ( accu_max) : (diff_y); 
        else
            accu_dy = (diff_y < -accu_max) ? (-accu_max) : (diff_y);
        
        obj->accu_dx += accu_dx;
        obj->accu_dy += accu_dy;
        obj->last_time = curtime;

        if ((ABS(obj->accu_dx) < quan_x) && (ABS(obj->accu_dy) < quan_y)) {
            if (trc & AVA_TRC_WORK) { 
                if (trc & AVA_TRC_SHORT_LOG)
                    AVA_MSG(".");
                else    
                    AVA_MSG("(%+4d, %+4d)(%+4d, %+4d) => [%16lld] (%+4d, %+4d) (%+4d, %+4d)\n", diff_x, diff_y, accu_dx, accu_dy,
                            diff, obj->accu_dx, obj->accu_dy, obj->accu_dx, obj->accu_dy);
            }
        } else {       
            dx = obj->accu_dx / quan_x;
            dy = obj->accu_dy / quan_y;
            //dy = -dy;   /*reverse the sign*/
            dx=-dx;

            if (trc & AVA_TRC_WORK) {
                if (trc & AVA_TRC_SHORT_LOG)
                    AVA_MSG(".");
                else    
                    AVA_MSG("(%+4d, %+4d)(%+4d, %+4d) => [%16lld] (%+4d, %+4d) (%+4d, %+4d) => (%+4d, %+4d)\n", diff_x, diff_y, 
                            accu_dx, accu_dy, diff, 
                            obj->accu_dx, obj->accu_dy, obj->accu_dx % quan_x, obj->accu_dy % quan_y, dx, dy);
            }
            obj->accu_dx = obj->accu_dx % quan_x;
            obj->accu_dy = obj->accu_dy % quan_y;
        }
    #else
        dx = (diff_x > 0) ? ((diff_x+quan_x-1)/quan_x) : ((diff_x-quan_x+1)/quan_x);
        dy = (diff_y > 0) ? ((diff_y+quan_y-1)/quan_y) : ((diff_y-quan_y+1)/quan_y);
        //dy = -dy; /*reverse the sign*/
        dx=-dx;
        if (trc & AVA_TRC_WORK) 
            AVA_MSG("New(%+2d, %+2d) => (%+2d, %+2d)\n", diff_x, diff_y, dx, dy);        
        
    #endif    
        input_report_rel(obj->dev, REL_X, dx);
        input_report_rel(obj->dev, REL_Y, dy);
        input_sync(obj->dev);        
        do_gettimeofday(&t2);
        if(trc & AVA_TRC_WORK)  
        {
        		AVA_MSG("time:%ld(ms)\n", (t2.tv_sec*1000+t2.tv_usec/1000)-(t1.tv_sec*1000+t1.tv_usec/1000));
        }       
    }
       
exit:
    if (err) 
        a320_reset_and_init(obj->client);
    if (!atomic_read(&obj->suspended))
        mt65xx_eint_unmask(CUST_EINT_OFN_NUM);      
    else
        AVA_LOG("ignore unmask\n");
}
/*----------------------------------------------------------------------------*/
void a320_eint_ball_motion(void)
{
    struct a320_priv *obj = g_a320_ptr;
    
    do_gettimeofday(&t1);    
    if (!obj)
        return;

    schedule_work(&obj->eint_ball_work);
    if (atomic_read(&obj->trace) & AVA_TRC_EINT)
        AVA_LOG("eint: motion interrupt\n");
}
/******************************************************************************
 *             Trackball Class: setup function
*******************************************************************************/
static int a320_setup_class_ball(struct a320_priv *obj)
{   
    g_a320_ptr = obj;    
    if (atomic_read(&obj->detect) == AVA_DETECT_EINT) 
        return a320_setup_eint(obj, a320_eint_ball_motion);
    return -EINVAL;
}
/******************************************************************************
 *
 *                      General function   
 *
*******************************************************************************/
static int a320_reset_device(struct a320_priv *obj)
{
    int err;

    mt_set_gpio_out(GPIO_OFN_DWN_PIN, GPIO_OUT_ONE);   
    mdelay(10);
    /*push to working state*/
    mt_set_gpio_out(GPIO_OFN_DWN_PIN, GPIO_OUT_ZERO);  
    
    mdelay(110);  

    /*hardware reset*/
    mt_set_gpio_out(GPIO_OFN_RST_PIN, GPIO_OUT_ZERO);   
    udelay(100);
    mt_set_gpio_out(GPIO_OFN_RST_PIN, GPIO_OUT_ONE);
    udelay(100);

    /*software reset*/
    if ((err = a320_write_byte(obj->client, A320_REG_SOFT_RESET, 0x5A))) {
        AVA_ERR("software reset fail: %d\n", err);
        return err;
    }

    return err;
}
/*----------------------------------------------------------------------------*/
static int a320_check_device(struct a320_priv *obj)
{   
    int err;
    u8 cur;

    if ((err = a320_read_byte(obj->client, A320_REG_PRODUCT_ID, &cur))) {
        AVA_ERR("read fail\n");
    } else if (cur != A320_PRODUCT_ID) {
        AVA_ERR("product id mismatch");
        err = -EINVAL;
    } else {
        AVA_LOG("device found: 0x%02X\n", cur);
    }
    return err;
}
/*----------------------------------------------------------------------------*/
static int a320_init_device(struct a320_priv *obj)
{
    int err;    

    //if ((err = a320_write_byte(obj->client, A320_REG_OFN_ENGINE, ENGINE|SPEED|ASSERT_DEASSERT|FINGER))) { /*auto-mode*/
    if ((err = a320_write_byte(obj->client, A320_REG_OFN_ENGINE, ENGINE|ASSERT_DEASSERT|FINGER))) { /*manual mode*/
        AVA_ERR("set OFN_ENGINE fail: %d\n", err);
        return err;
    }
    /*setup speed*/
    if ((err = a320_write_byte(obj->client, 0x62, 0x12))) {
        AVA_ERR("set 0x62 => 0x12: %d\n", err);
        return err;
    }

    if ((err = a320_write_byte(obj->client, 0x63, 0x0E))) {
        AVA_ERR("set 0x63 => 0x0E: %d\n", err);
        return err;
    }

    if ((err = a320_write_byte(obj->client, 0x64, 0x08))) {
        AVA_ERR("set 0x64 => 0x08: %d\n", err);
        return err;
    }

    if ((err = a320_write_byte(obj->client, 0x65, 0x06))) {
        AVA_ERR("set 0x65 => 0x06: %d\n", err);
        return err;
    }

    if ((err = a320_write_byte(obj->client, 0x66, 0x40))) {
        AVA_ERR("set 0x66 => 0x40: %d\n", err);
        return err;
    }

    if ((err = a320_write_byte(obj->client, 0x67, 0x08))) {
        AVA_ERR("set 0x67 => 0x08: %d\n", err);
        return err;
    }

    if ((err = a320_write_byte(obj->client, 0x68, 0x48))) {
        AVA_ERR("set 0x68 => 0x48: %d\n", err);
        return err;
    }

    if ((err = a320_write_byte(obj->client, 0x69, 0x0A))) {
        AVA_ERR("set 0x69 => 0x0A: %d\n", err);
        return err;
    }

    if ((err = a320_write_byte(obj->client, 0x6A, 0x50))) {
        AVA_ERR("set 0x6A => 0x50: %d\n", err);
        return err;
    }

    if ((err = a320_write_byte(obj->client, 0x6B, 0x48))) {
        AVA_ERR("set 0x6B => 0x48: %d\n", err);
        return err;
    }

    /*setup interrupt*/
    if ((err = a320_write_byte(obj->client, 0x6E, 0x34))) {
        AVA_ERR("set 0x6B => 0x48: %d\n", err);
        return err;
    }

    if (obj->hw->chip_id == OFN1026)
    {
        if ((err = a320_write_byte(obj->client, 0x6F, 0x3C))) {
            AVA_ERR("set 0x6B => 0x48: %d\n", err);
            return err;
        }

        if ((err = a320_write_byte(obj->client, 0x70, 0x18))) {
            AVA_ERR("set 0x6B => 0x48: %d\n", err);
            return err;
        }

        if ((err = a320_write_byte(obj->client, 0x71, 0x20))) {
            AVA_ERR("set 0x6B => 0x48: %d\n", err);
            return err;
        }
    } else if (obj->hw->chip_id == OFN1090 || obj->hw->chip_id == OFN1086) {
        if ((err = a320_write_byte(obj->client, 0x40, 0x3C))) {
            AVA_ERR("set 0x6B => 0x48: %d\n", err);
            return err;
        }

        if ((err = a320_write_byte(obj->client, 0x34, 0x18))) {
            AVA_ERR("set 0x6B => 0x48: %d\n", err);
            return err;
        }

        if ((err = a320_write_byte(obj->client, 0x40, 0x20))) {
            AVA_ERR("set 0x6B => 0x48: %d\n", err);
            return err;
        }
    }

    if ((err = a320_write_byte(obj->client, 0x77, obj->hw->layout << 5))) {
        AVA_ERR("set 0x77: %d\n", err);
        return err;
    } 
    return 0;
}
/*----------------------------------------------------------------------------*/
int a320_init_client(struct i2c_client* client)
{
    struct a320_priv *obj = i2c_get_clientdata(client);    	 
    int err;

    if ((err = a320_init_gpio(obj))) {
        AVA_ERR("init_gpio: %d\n", err);
        return err;
    }

    if ((err = a320_reset_device(obj))) {
        AVA_ERR("reset_device: %d\n", err);
        return err;
    }
   
    if ((err = a320_check_device(obj))) {
        AVA_ERR("check_device: %d\n", err);
        return err;
    }

    if ((err = a320_init_device(obj))) {
        AVA_ERR("init_device: %d\n", err);
        return err;    
    }
#if 0
    if (obj->hw->report_cls == OFN_CLASS_KEYBOARD)
        err = a320_setup_class_key(obj);
#endif //    else
    err = a320_setup_class_ball(obj);
    if (err)
        AVA_ERR("setup class fail: %d\n", err);
    return err;
}
/*----------------------------------------------------------------------------*/
static int a320_reset_and_init(struct i2c_client* client)
{
    struct a320_priv *obj = i2c_get_clientdata(client);    	 
    int err;
    
    /*set device to shutdown*/
    mt_set_gpio_out(GPIO_OFN_DWN_PIN, GPIO_OUT_ONE);
    mt65xx_eint_mask(CUST_EINT_OFN_NUM);
    a320_power(obj->hw, 0);
    
    /*re-init the devices*/
    mt65xx_eint_unmask(CUST_EINT_OFN_NUM);
    a320_power(obj->hw, 1);
    if ((err = a320_init_client(obj->client))) {
        AVA_ERR("initialize client fail!!\n");
        return err;        
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
/* timer keep polling Jog Ball status                                         */
/*----------------------------------------------------------------------------*/
#if !defined(CONFIG_HAS_EARLYSUSPEND)
/*----------------------------------------------------------------------------*/
static int a320_i2c_suspend(struct i2c_client *client, pm_message_t msg) 
{
    struct a320_priv *obj = i2c_get_clientdata(client);        
    int err;
    AVA_FUN();    

    if (msg.event == PM_EVENT_SUSPEND) {   
        atomic_set(&obj->suspended, 1);
        mt_set_gpio_out(GPIO_OFN_DWN_PIN, GPIO_OUT_ONE);
        a320_power(obj->hw, 0);
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
static int a320_i2c_resume(struct i2c_client *client)
{
    struct a320_priv *obj = i2c_get_clientdata(client);           
    int err;    
    AVA_FUN();
    
    a320_power(obj->hw, 1);
    if ((err = a320_init_client(AMI304_FORCE_MODE))) {
        AMI_ERR("initialize client fail!!\n");
        return err;        
    }
    atomic_set(&obj->suspended, 0);
    return 0;
}
/*----------------------------------------------------------------------------*/
#else
/*----------------------------------------------------------------------------*/
static void a320_early_suspend(struct early_suspend *h)
{
    struct a320_priv *obj = container_of(h, struct a320_priv, early_drv);   
    AVA_FUN();    

    if (!obj) {
        AVA_ERR("null pointer!!\n");
        return;
    }
    atomic_set(&obj->suspended, 1);
    mt_set_gpio_out(GPIO_OFN_DWN_PIN, GPIO_OUT_ONE);
    mt65xx_eint_mask(CUST_EINT_OFN_NUM);
    a320_power(obj->hw, 0);
}
/*----------------------------------------------------------------------------*/
static void a320_late_resume(struct early_suspend *h)
{
    struct a320_priv *obj = container_of(h, struct a320_priv, early_drv);         
    int err;
    AVA_FUN();

    if (!obj) {
        AVA_ERR("null pointer!!\n");
        return;
    }
    
    atomic_set(&obj->suspended, 0);
    mt65xx_eint_unmask(CUST_EINT_OFN_NUM);
    a320_power(obj->hw, 1);
    if ((err = a320_init_client(obj->client))) {
        AVA_ERR("initialize client fail!!\n");
        return;        
    }    
}
/*----------------------------------------------------------------------------*/
#endif
/*----------------------------------------------------------------------------*/
static int a320_i2c_detect(struct i2c_client *client, int kind, struct i2c_board_info *info) 
{    
    strcpy(info->type, A320_DEV_NAME);
    return 0;
}
/*----------------------------------------------------------------------------*/
static int a320_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id) 
{
    struct a320_priv* obj = NULL;
    int idx, err = 0;

    AVA_FUN();
    
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		goto exit;    
    obj = (struct a320_priv*)kzalloc(sizeof(*obj), GFP_KERNEL);
    if (!obj)
        return -ENOMEM;

    obj->hw = get_cust_ofn_hw();
    /* allocate input device */
    obj->dev = input_allocate_device();
    if (!obj->dev) {
        err = -ENOMEM;
        goto err_input_alloc_device;
    }
    
    /* struct input_dev dev initialization and registration */
    obj->dev->name = "mtofn"; /*used in factory mode*/
#if 0
    if (obj->hw->report_cls == OFN_CLASS_KEYBOARD) {
        /* setup input subsystem: key class*/ 
        input_set_capability(obj->dev, EV_KEY, KEY_UP);
        input_set_capability(obj->dev, EV_KEY, KEY_DOWN);
        input_set_capability(obj->dev, EV_KEY, KEY_LEFT);
        input_set_capability(obj->dev, EV_KEY, KEY_RIGHT);    
#endif//    } else 
	{     
        /* setup input subsystem: trackball class*/
        input_set_capability(obj->dev, EV_KEY, BTN_MOUSE);        
        input_set_capability(obj->dev, EV_REL, REL_X);
        input_set_capability(obj->dev, EV_REL, REL_Y);
    }

    /* reigster input device */
    if (input_register_device(obj->dev)) {
        AVA_ERR("input_register_device failed.\n");
        goto err_input_register_device;
    }
   
    /* init workqueue */
#if 0	
    INIT_WORK(&obj->eint_key_work, a320_eint_key_work);
    INIT_WORK(&obj->poll_key_work, a320_poll_key_work);
#endif
    INIT_WORK(&obj->eint_ball_work, a320_eint_ball_work);
	obj->client = client;
    i2c_set_clientdata(client, obj);

    /* init counter */
    for (idx = 0; idx < AVA_DIR_NUM; idx++) {        
        atomic_set(&obj->dir[idx].cnt, 0);
        atomic_set(&obj->dir[idx].val, 0);
        obj->dir[idx].last_trig = 0;
    }
#if 0	
    /*keyboard class*/
    obj->dir[AVA_DIR_UP].key_evt = KEY_UP;
    obj->dir[AVA_DIR_LF].key_evt = KEY_LEFT;
    obj->dir[AVA_DIR_RG].key_evt = KEY_RIGHT;
    obj->dir[AVA_DIR_DN].key_evt = KEY_DOWN;
#endif	
    atomic_set(&obj->detect, obj->hw->detect);
    atomic_set(&obj->trace,  0x00);
    atomic_set(&obj->acc_cnt, obj->hw->acc_cnt);
    atomic_set(&obj->inact_cnt, obj->hw->inact_cnt);
    atomic_set(&obj->act_cnt, obj->hw->act_cnt);
    atomic_set(&obj->sup_cnt, obj->hw->sup_cnt);
    atomic_set(&obj->step,   obj->hw->step);   
    obj->pending = 0;

    /*trackball class*/
    atomic_set(&obj->quan_x, obj->hw->quan_x);
    atomic_set(&obj->quan_y, obj->hw->quan_y);
    atomic_set(&obj->suspended, 0);
    atomic_set(&obj->tb_inact_cnt, 500);
    atomic_set(&obj->accu_max, obj->hw->accu_max);
    obj->dir[AVA_DIR_UP].step_y = -1;
    obj->dir[AVA_DIR_DN].step_y = +1;
    obj->dir[AVA_DIR_LF].step_x = -1;
    obj->dir[AVA_DIR_RG].step_x = +1;    
            
    if ((err = a320_init_client(client))) {
        AVA_ERR("start detect fail: %d\n", err);
        goto err_init_client;
    }

    if ((err = sysfs_create_group(&client->dev.kobj, &a320_group))) {
        AVA_ERR("create attr fail\n");
        goto err_create_attr;
    }
    
#if defined(CONFIG_HAS_EARLYSUSPEND)
    obj->early_drv.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 1;
    obj->early_drv.suspend = a320_early_suspend;
    obj->early_drv.resume = a320_late_resume;
    register_early_suspend(&obj->early_drv);
#endif
    AVA_LOG("%s: OK\n", __func__);
    return 0;

err_create_attr:    
err_init_client:
    input_unregister_device(obj->dev);  
err_input_register_device:
    input_free_device(obj->dev);
err_input_alloc_device:
	//i2c_unregister_device(client);	    
    kfree(obj);
exit:
    AVA_ERR("%s: err = %d\n", __func__, err);
    return err;
}
/*----------------------------------------------------------------------------*/
static int a320_i2c_remove(struct i2c_client *client)
{
	struct a320_priv *obj = i2c_get_clientdata(client);

	AVA_FUN();

	sysfs_remove_group(&client->dev.kobj, &a320_group);
	i2c_unregister_device(client);	
	kfree(obj);
	return 0;
}   
/*----------------------------------------------------------------------------*/
static int a320_probe(struct platform_device *pdev)
{
    struct ofn_hw* hw = get_cust_ofn_hw();
    int err;

    a320_force[0] = hw->i2c_num;
    a320_force[1] = hw->slave_addr << 1; 
    if ((err = i2c_add_driver(&a320_i2c_driver)))
        AVA_ERR("i2c_add_driver err = %d\n", err);
    return err;    
}
/*----------------------------------------------------------------------------*/
static int a320_remove(struct platform_device *pdev)
{
    AVA_FUN();
    i2c_del_driver(&a320_i2c_driver);
    return 0;
}
/*----------------------------------------------------------------------------*/
static struct platform_driver a320_driver = {
    .probe  = a320_probe,
    .remove = a320_remove,
    .driver = {
        .name = "mtofn",
        .owner = THIS_MODULE,
    }
};
/*----------------------------------------------------------------------------*/
static int __init a320_priv_init(void) 
{
    AVA_FUN();

    if (platform_driver_register(&a320_driver)) {
        AVA_ERR("failed to register driver");
        return -ENODEV;
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
static void __exit a320_priv_exit(void) 
{
    AVA_FUN();
    platform_driver_unregister(&a320_driver);
}
/*----------------------------------------------------------------------------*/
module_init(a320_priv_init);
module_exit(a320_priv_exit);
