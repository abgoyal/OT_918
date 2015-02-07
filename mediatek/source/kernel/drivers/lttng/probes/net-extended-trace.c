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
 * ltt/probes/net-extended-trace.c
 *
 * Net tracepoint extended probes.
 *
 * These probes record many header fields from TCP and UDP messages. Here are
 * the consequences of this:
 * 1) it allows analyzing network traffic to provide some pcap-like
 *    functionality within LTTng
 * 2) it allows offline synchronization of a group of concurrent traces
 *    recorded on different nodes
 * 3) it increases tracing overhead
 *
 * You can leave out these probes or not activate them if you are not
 * especially interested in the details of network traffic and do not wish to
 * synchronize distributed traces.
 *
 * Dual LGPL v2.1/GPL v2 license.
 */

#include <linux/in_route.h>
#include <linux/ip.h>
#include <linux/module.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <net/route.h>
#include <trace/net.h>

#include "../ltt-type-serializer.h"

void probe_net_dev_xmit_extended(void *_data, struct sk_buff *skb);

DEFINE_MARKER_TP(net, dev_xmit_extended, net_dev_xmit,
	probe_net_dev_xmit_extended, "skb 0x%lX network_protocol #n2u%hu "
	"transport_protocol #1u%u saddr #n4u%lu daddr #n4u%lu "
	"tot_len #n2u%hu ihl #1u%u source #n2u%hu dest #n2u%hu seq #n4u%lu "
	"ack_seq #n4u%lu doff #1u%u ack #1u%u rst #1u%u syn #1u%u fin #1u%u");

notrace void probe_net_dev_xmit_extended(void *_data, struct sk_buff *skb)
{
	struct marker *marker;
	struct serialize_l214421224411111 data;
	struct iphdr *iph = ip_hdr(skb);
	struct tcphdr *th = tcp_hdr(skb);

	data.f1 = (unsigned long)skb;
	data.f2 = skb->protocol;

	if (ntohs(skb->protocol) == ETH_P_IP) {
		data.f3 = ip_hdr(skb)->protocol;
		data.f4 = iph->saddr;
		data.f5 = iph->daddr;
		data.f6 = iph->tot_len;
		data.f7 = iph->ihl;

		if (data.f3 == IPPROTO_TCP) {
			data.f8 = th->source;
			data.f9 = th->dest;
			data.f10 = th->seq;
			data.f11 = th->ack_seq;
			data.f12 = th->doff;
			data.f13 = th->ack;
			data.f14 = th->rst;
			data.f15 = th->syn;
			data.f16 = th->fin;
		}
	}

	marker = &GET_MARKER(net, dev_xmit_extended);
	ltt_specialized_trace(marker, marker->single.probe_private,
		&data, serialize_sizeof(data), sizeof(long));
}

void probe_tcpv4_rcv_extended(void *_data, struct sk_buff *skb);

DEFINE_MARKER_TP(net, tcpv4_rcv_extended, net_tcpv4_rcv,
	probe_tcpv4_rcv_extended, "skb 0x%lX saddr #n4u%lu daddr #n4u%lu "
	"tot_len #n2u%hu ihl #1u%u source #n2u%hu dest #n2u%hu seq #n4u%lu "
	"ack_seq #n4u%lu doff #1u%u ack #1u%u rst #1u%u syn #1u%u fin #1u%u");

notrace void probe_tcpv4_rcv_extended(void *_data, struct sk_buff *skb)
{
	struct marker *marker;
	struct serialize_l4421224411111 data;
	struct iphdr *iph = ip_hdr(skb);
	struct tcphdr *th = tcp_hdr(skb);

	data.f1 = (unsigned long)skb;
	data.f2 = iph->saddr;
	data.f3 = iph->daddr;
	data.f4 = iph->tot_len;
	data.f5 = iph->ihl;
	data.f6 = th->source;
	data.f7 = th->dest;
	data.f8 = th->seq;
	data.f9 = th->ack_seq;
	data.f10 = th->doff;
	data.f11 = th->ack;
	data.f12 = th->rst;
	data.f13 = th->syn;
	data.f14 = th->fin;

	marker = &GET_MARKER(net, tcpv4_rcv_extended);
	ltt_specialized_trace(marker, marker->single.probe_private,
		&data, serialize_sizeof(data), sizeof(long));
}

void probe_udpv4_rcv_extended(void *_data, struct sk_buff *skb);

DEFINE_MARKER_TP(net, udpv4_rcv_extended, net_udpv4_rcv,
	probe_udpv4_rcv_extended, "skb 0x%lX saddr #n4u%lu daddr #n4u%lu "
	"unicast #1u%u ulen #n2u%hu source #n2u%hu dest #n2u%hu "
	"data_start #8u%lx");

notrace void probe_udpv4_rcv_extended(void *_data, struct sk_buff *skb)
{
	struct marker *marker;
	struct serialize_l4412228 data;
	struct iphdr *iph = ip_hdr(skb);
	struct rtable *rt = skb_rtable(skb);
	struct udphdr *uh = udp_hdr(skb);

	data.f1 = (unsigned long)skb;
	data.f2 = iph->saddr;
	data.f3 = iph->daddr;
	data.f4 = rt->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST) ? 0 : 1;
	data.f5 = uh->len;
	data.f6 = uh->source;
	data.f7 = uh->dest;
	/* UDP header has not been pulled from skb->data, read the first 8
	 * bytes of UDP data if they are not in a fragment*/
	data.f8 = 0;
	if (skb_headlen(skb) >= sizeof(struct udphdr) + 8)
		data.f8 = *(unsigned long long *)(skb->data + sizeof(*uh));
	else if (skb_headlen(skb) >= sizeof(struct udphdr))
		memcpy(&data.f8, skb->data + sizeof(struct udphdr),
			skb_headlen(skb) - sizeof(struct udphdr));

	marker = &GET_MARKER(net, udpv4_rcv_extended);
	ltt_specialized_trace(marker, marker->single.probe_private,
		&data, serialize_sizeof(data), sizeof(unsigned long long));
}

MODULE_LICENSE("GPL and additional rights");
MODULE_AUTHOR("Benjamin Poirier");
MODULE_DESCRIPTION("Net Tracepoint Extended Probes");
