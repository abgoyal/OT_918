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

#include "tpd.h"

extern struct tpd_device *tpd;

//#ifdef TPD_HAVE_BUTTON
//static int tpd_keys[TPD_KEY_COUNT] = TPD_KEYS;
//static int tpd_keys_dim[TPD_KEY_COUNT][4] = TPD_KEYS_DIM;
static unsigned int tpd_keycnt = 0;
static int tpd_keys[TPD_VIRTUAL_KEY_MAX]={0};
static int tpd_keys_dim[TPD_VIRTUAL_KEY_MAX][4];// = {0};
static ssize_t mtk_virtual_keys_show(struct kobject *kobj,
                   struct kobj_attribute *attr, char *buf) {
    int i, j;
    for(i=0, j=0;i<tpd_keycnt;i++)
        j+=sprintf(buf, "%s%s:%d:%d:%d:%d:%d%s",buf,
           __stringify(EV_KEY),tpd_keys[i],
           tpd_keys_dim[i][0],tpd_keys_dim[i][1],
           tpd_keys_dim[i][2],tpd_keys_dim[i][3],
           (i==tpd_keycnt-1?"\n":":"));
    return j;
}

static struct kobj_attribute mtk_virtual_keys_attr = {
    .attr = {
        .name = "virtualkeys.mtk-tpd",
        .mode = S_IRUGO,
    },
    .show = &mtk_virtual_keys_show,
};

static struct attribute *mtk_properties_attrs[] = {
    &mtk_virtual_keys_attr.attr,
    NULL
};

static struct attribute_group mtk_properties_attr_group = {
    .attrs = mtk_properties_attrs,
};

struct kobject *properties_kobj;

void tpd_button_init(void) {
    int ret = 0, i = 0, j=0;

/*
	for(i=0; i<TPD_VIRTUAL_KEY_MAX; i++)
	{
		for(j=0; j<4; j++)
		{
			tpd_keys_dim[i][j]=0;
		}
	}
	*/
//    if((tpd->kpd=input_allocate_device())==NULL) return -ENOMEM;
    tpd->kpd=input_allocate_device();
    /* struct input_dev kpd initialization and registration */
    tpd->kpd->name = TPD_DEVICE "-kpd";
    set_bit(EV_KEY, tpd->kpd->evbit);
    set_bit(EV_REL, tpd->kpd->evbit);
    set_bit(EV_ABS, tpd->kpd->evbit);
    for(i=0;i<tpd_keycnt;i++)
        __set_bit(tpd_keys[i], tpd->kpd->keybit);
    tpd->kpd->id.bustype = BUS_HOST;
    tpd->kpd->id.vendor  = 0x0001;
    tpd->kpd->id.product = 0x0001;
    tpd->kpd->id.version = 0x0100;
    if(input_register_device(tpd->kpd))
        TPD_DMESG("input_register_device failed.(kpd)\n");
    set_bit(EV_KEY, tpd->dev->evbit);
    for(i=0;i<tpd_keycnt;i++)
        __set_bit(tpd_keys[i], tpd->dev->keybit);
    properties_kobj = kobject_create_and_add("board_properties", NULL);
    if(properties_kobj)
        ret = sysfs_create_group(properties_kobj,&mtk_properties_attr_group);
    if(!properties_kobj || ret)
    printk("failed to create board_properties\n");
}

void tpd_button(unsigned int x, unsigned int y, unsigned int down) {
    int i;
    if(down) {
        for(i=0;i<tpd_keycnt;i++) {
            if(x>=tpd_keys_dim[i][0]-(tpd_keys_dim[i][2]/2) &&
               x<=tpd_keys_dim[i][0]+(tpd_keys_dim[i][2]/2) &&
               y>=tpd_keys_dim[i][1]-(tpd_keys_dim[i][3]/2) &&
               y<=tpd_keys_dim[i][1]+(tpd_keys_dim[i][3]/2) &&
               !(tpd->btn_state&(1<<i))) {
                input_report_key(tpd->kpd, tpd_keys[i], 1);
                tpd->btn_state|=(1<<i);
                TPD_DEBUG("[mtk-tpd] press key %d (%d)\n",i, tpd_keys[i]);
            }
        }
    } else {
        for(i=0;i<tpd_keycnt;i++) {
            if(tpd->btn_state&(1<<i)) {
                input_report_key(tpd->kpd, tpd_keys[i], 0);
                TPD_DEBUG("[mtk-tpd] release key %d (%d)\n",i, tpd_keys[i]);
            }
        }
        tpd->btn_state=0;
    }
}
void tpd_button_setting(int keycnt, void *keys, void *keys_dim)
{
		tpd_keycnt = keycnt;
		memcpy(tpd_keys, keys, keycnt*4);
		memcpy(tpd_keys_dim, keys_dim, keycnt*4*4);
}
//#endif
