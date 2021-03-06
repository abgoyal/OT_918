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

/*
 * LTT core in-kernel infrastructure.
 *
 * Copyright 2006 - Mathieu Desnoyers mathieu.desnoyers@polymtl.ca
 *
 * Dual LGPL v2.1/GPL v2 license.
 */

#include <linux/percpu.h>
#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/kref.h>
#include <linux/cpu.h>

#include "ltt-tracer-core.h"

/* Traces structures */
struct ltt_traces ltt_traces = {
	.setup_head = LIST_HEAD_INIT(ltt_traces.setup_head),
	.head = LIST_HEAD_INIT(ltt_traces.head),
};
EXPORT_SYMBOL(ltt_traces);

/* Traces list writer locking */
static DEFINE_MUTEX(ltt_traces_mutex);

/* root dentry mutex */
static DEFINE_MUTEX(ltt_root_mutex);
/* dentry of ltt's root dir */
static struct dentry *ltt_root_dentry;
static struct kref ltt_root_kref = {
	.refcount = ATOMIC_INIT(0),
};

static void ltt_root_release(struct kref *ref)
{
	debugfs_remove(ltt_root_dentry);
	ltt_root_dentry = NULL;
}

void put_ltt_root(void)
{
	mutex_lock(&ltt_root_mutex);
	if (ltt_root_dentry)
		kref_put(&ltt_root_kref, ltt_root_release);
	mutex_unlock(&ltt_root_mutex);
}
EXPORT_SYMBOL_GPL(put_ltt_root);

struct dentry *get_ltt_root(void)
{
	mutex_lock(&ltt_root_mutex);
	if (!ltt_root_dentry) {
		ltt_root_dentry = debugfs_create_dir(LTT_ROOT, NULL);
		if (!ltt_root_dentry) {
			printk(KERN_ERR "LTT : create ltt root dir failed\n");
			goto out;
		}
		kref_init(&ltt_root_kref);
		goto out;
	}
	kref_get(&ltt_root_kref);
out:
	mutex_unlock(&ltt_root_mutex);
	return ltt_root_dentry;
}
EXPORT_SYMBOL_GPL(get_ltt_root);

/*
 * ltt_lock_traces/ltt_unlock_traces also disables cpu hotplug.
 */
void ltt_lock_traces(void)
{
	mutex_lock(&ltt_traces_mutex);
	get_online_cpus();
}
EXPORT_SYMBOL_GPL(ltt_lock_traces);

void ltt_unlock_traces(void)
{
	put_online_cpus();
	mutex_unlock(&ltt_traces_mutex);
}
EXPORT_SYMBOL_GPL(ltt_unlock_traces);

DEFINE_PER_CPU(unsigned int, ltt_nesting);
EXPORT_PER_CPU_SYMBOL(ltt_nesting);

int ltt_run_filter_default(void *trace, uint16_t eID)
{
	return 1;
}

/* This function pointer is protected by a trace activation check */
ltt_run_filter_functor ltt_run_filter = ltt_run_filter_default;
EXPORT_SYMBOL_GPL(ltt_run_filter);

void ltt_filter_register(ltt_run_filter_functor func)
{
	ltt_run_filter = func;
}
EXPORT_SYMBOL_GPL(ltt_filter_register);

void ltt_filter_unregister(void)
{
	ltt_run_filter = ltt_run_filter_default;
}
EXPORT_SYMBOL_GPL(ltt_filter_unregister);

MODULE_LICENSE("GPL and additional rights");
MODULE_AUTHOR("Mathieu Desnoyers");
MODULE_DESCRIPTION("Linux Trace Toolkit Next Generation Tracer Core");
