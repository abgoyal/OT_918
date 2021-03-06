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
** $Id: //ALPS_SW/TRUNK/MAIN/alps/kernel/drivers/net/wireless/mt592x/link.h#1 $
*/

/*! \file   link.h
    \brief  Definition for simple doubly linked list operations.

    In this file we define the simple doubly linked list data structure and its
    operation MACROs and INLINE functions.
*/

/*******************************************************************************
* Copyright (c) 2007 MediaTek Inc.
*
* All rights reserved. Copying, compilation, modification, distribution
* or any other use whatsoever of this material is strictly prohibited
* except in accordance with a Software License Agreement with
* MediaTek Inc.
********************************************************************************
*/

/*******************************************************************************
* LEGAL DISCLAIMER
*
* BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND
* AGREES THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK
* SOFTWARE") RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE
* PROVIDED TO BUYER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY
* DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE
* ANY WARRANTY WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY
* WHICH MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK
* SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY
* WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE
* FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION OR TO
* CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
* BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
* LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL
* BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT
* ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY
* BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
* THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
* WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT
* OF LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING
* THEREOF AND RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN
* FRANCISCO, CA, UNDER THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE
* (ICC).
********************************************************************************
*/

/*
** $Log: link.h $
 *
 * 05 27 2010 renbang.jiang
 * [ALPS00007371][Need Patch] [Volunteer Patch] ALPS.10X.W10.11 Volunteer patch for WiFi Un-GPL license 
 * .
**  \main\maintrunk.MT5921\8 2008-10-16 15:57:11 GMT mtk01461
**  Update driver to fix lint warning
**  \main\maintrunk.MT5921\7 2008-08-10 18:47:53 GMT mtk01461
**  Update for Driver Review
**  \main\maintrunk.MT5921\6 2007-12-11 00:09:00 GMT mtk01461
**  Add macro for checking valid list
**  \main\maintrunk.MT5921\5 2007-11-13 14:27:01 GMT mtk01461
**  Add LINK_IS_INVALID macro
** Revision 1.1.1.1  2007/06/22 08:09:05  MTK01461
** no message
**
*/

#ifndef _LINK_H
#define _LINK_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "gl_typedef.h"


/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define INVALID_LINK_POISON1    ((VOID *) 0x00100101) // May cause page fault & unalignment issue (data abort)
#define INVALID_LINK_POISON2    ((VOID *) 0x00100201) // Used to verify that nonbody uses non-initialized link entries.


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
/* Simple Doubly Linked List Structures - Entry Part */
typedef struct _LINK_ENTRY_T {
    struct _LINK_ENTRY_T *prNext, *prPrev;
} LINK_ENTRY_T, *P_LINK_ENTRY_T;

/* Simple Doubly Linked List Structures - List Part */
typedef struct _LINK_T {
    P_LINK_ENTRY_T  prNext;
    P_LINK_ENTRY_T  prPrev;
    UINT_32 u4NumElem;
} LINK_T, *P_LINK_T;

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
#if 0 // No one use it, temporarily mark it for [Lint - Info 773]
#define LINK_ADDR(rLink)        { (P_LINK_ENTRY_T)(&(rLink)), (P_LINK_ENTRY_T)(&(rLink)), 0 }

#define LINK_DECLARATION(rLink) \
    struct _LINK_T rLink = LINK_ADDR(rLink)
#endif

#define LINK_INITIALIZE(prLink) \
    do { \
        ((P_LINK_T)(prLink))->prNext = (P_LINK_ENTRY_T)(prLink); \
        ((P_LINK_T)(prLink))->prPrev = (P_LINK_ENTRY_T)(prLink); \
        ((P_LINK_T)(prLink))->u4NumElem = 0; \
    } while (0)

#define LINK_ENTRY_INITIALIZE(prEntry) \
    do { \
        ((P_LINK_ENTRY_T)(prEntry))->prNext = (P_LINK_ENTRY_T)NULL; \
        ((P_LINK_ENTRY_T)(prEntry))->prPrev = (P_LINK_ENTRY_T)NULL; \
    } while (0)

#define LINK_ENTRY_INVALID(prEntry) \
    do { \
        ((P_LINK_ENTRY_T)(prEntry))->prNext = (P_LINK_ENTRY_T)INVALID_LINK_POISON1; \
        ((P_LINK_ENTRY_T)(prEntry))->prPrev = (P_LINK_ENTRY_T)INVALID_LINK_POISON2; \
    } while (0)

#define LINK_IS_EMPTY(prLink)           (((P_LINK_T)(prLink))->prNext == (P_LINK_ENTRY_T)(prLink))

/* NOTE: We should do memory zero before any LINK been initiated, so we can check
 * if it is valid before parsing the LINK.
 */
#define LINK_IS_INVALID(prLink)         (((P_LINK_T)(prLink))->prNext == (P_LINK_ENTRY_T)NULL)

#define LINK_IS_VALID(prLink)           (((P_LINK_T)(prLink))->prNext != (P_LINK_ENTRY_T)NULL)


#define LINK_ENTRY(ptr, type, member)   ENTRY_OF(ptr, type, member)

/* Insert an entry into a link list's head */
#define LINK_INSERT_HEAD(prLink, prEntry) \
        { \
            linkAdd(prEntry, prLink); \
            ((prLink)->u4NumElem)++; \
        }


/* Append an entry into a link list's tail */
#define LINK_INSERT_TAIL(prLink, prEntry) \
        { \
            linkAddTail(prEntry, prLink); \
            ((prLink)->u4NumElem)++; \
        }


/* Get first entry from a link list */
/* NOTE: We assume the link entry located at the beginning of "prEntry Type",
 * so that we can cast the link entry to other data type without doubts.
 * And this macro also decrease the total entry count at the same time.
 */
#define LINK_REMOVE_HEAD(prLink, prEntry, _P_TYPE) \
        { \
            ASSERT(prLink); \
            if (LINK_IS_EMPTY(prLink)) { \
                prEntry = (_P_TYPE)NULL; \
            } \
            else { \
                prEntry = (_P_TYPE)(((P_LINK_T)(prLink))->prNext); \
                linkDel((P_LINK_ENTRY_T)prEntry); \
                ((prLink)->u4NumElem)--; \
            } \
        }

/* Assume the link entry located at the beginning of prEntry Type.
 * And also decrease the total entry count.
 */
#define LINK_REMOVE_KNOWN_ENTRY(prLink, prEntry) \
        { \
            ASSERT(prLink); \
            ASSERT(prEntry); \
            linkDel((P_LINK_ENTRY_T)prEntry); \
            ((prLink)->u4NumElem)--; \
        }

/* Iterate over a link list */
#define LINK_FOR_EACH(prEntry, prLink) \
    for (prEntry = (prLink)->prNext; \
         prEntry != (P_LINK_ENTRY_T)(prLink); \
         prEntry = (P_LINK_ENTRY_T)prEntry->prNext)

/* Iterate over a link list backwards */
#define LINK_FOR_EACH_PREV(prEntry, prLink) \
    for (prEntry = (prLink)->prPrev; \
         prEntry != (P_LINK_ENTRY_T)(prLink); \
         prEntry = (P_LINK_ENTRY_T)prEntry->prPrev)

/* Iterate over a link list safe against removal of link entry */
#define LINK_FOR_EACH_SAFE(prEntry, prNext, prLink) \
    for (prEntry = (prLink)->prNext, prNext = prEntry->prNext; \
         prEntry != (P_LINK_ENTRY_T)(prLink); \
         prEntry = prNext, prNext = prEntry->prNext)

/* Iterate over a link list of given type */
#define LINK_FOR_EACH_ENTRY(prObj, prLink, rMember, _TYPE) \
    for (prObj = LINK_ENTRY((prLink)->prNext, _TYPE, rMember); \
         &prObj->rMember != (P_LINK_ENTRY_T)(prLink); \
         prObj = LINK_ENTRY(prObj->rMember.prNext, _TYPE, rMember))

/* Iterate backwards over a link list of given type */
#define LINK_FOR_EACH_ENTRY_PREV(prObj, prLink, rMember, _TYPE) \
    for (prObj = LINK_ENTRY((prLink)->prPrev, _TYPE, rMember);  \
         &prObj->rMember != (P_LINK_ENTRY_T)(prLink); \
         prObj = LINK_ENTRY(prObj->rMember.prPrev, _TYPE, rMember))

/* Iterate over a link list of given type safe against removal of link entry */
#define LINK_FOR_EACH_ENTRY_SAFE(prObj, prNextObj, prLink, rMember, _TYPE) \
    for (prObj = LINK_ENTRY((prLink)->prNext, _TYPE, rMember),  \
         prNextObj = LINK_ENTRY(prObj->rMember.prNext, _TYPE, rMember); \
         &prObj->rMember != (P_LINK_ENTRY_T)(prLink); \
         prObj = prNextObj, \
         prNextObj = LINK_ENTRY(prNextObj->rMember.prNext, _TYPE, rMember))

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
/*----------------------------------------------------------------------------*/
/*!
* \brief This function is only for internal link list manipulation.
*
* \param[in] prNew  Pointer of new link head
* \param[in] prPrev Pointer of previous link head
* \param[in] prNext Pointer of next link head
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
__linkAdd (
    IN P_LINK_ENTRY_T prNew,
    IN P_LINK_ENTRY_T prPrev,
    IN P_LINK_ENTRY_T prNext
    )
{
    prNext->prPrev = prNew;
    prNew->prNext = prNext;
    prNew->prPrev = prPrev;
    prPrev->prNext = prNew;

    return;
} /* end of __linkAdd() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will add a new entry after the specified link head.
*
* \param[in] prNew  New entry to be added
* \param[in] prHead Specified link head to add it after
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
linkAdd (
    IN P_LINK_ENTRY_T prNew,
    IN P_LINK_T prLink
    )
{
    __linkAdd(prNew, (P_LINK_ENTRY_T)prLink, prLink->prNext);

    return;
} /* end of linkAdd() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will add a new entry before the specified link head.
*
* \param[in] prNew  New entry to be added
* \param[in] prHead Specified link head to add it before
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
linkAddTail (
    IN P_LINK_ENTRY_T prNew,
    IN P_LINK_T prLink
    )
{
    __linkAdd(prNew, prLink->prPrev, (P_LINK_ENTRY_T)prLink);

    return;
} /* end of linkAddTail() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function is only for internal link list manipulation.
*
* \param[in] prPrev Pointer of previous link head
* \param[in] prNext Pointer of next link head
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
__linkDel (
    IN P_LINK_ENTRY_T prPrev,
    IN P_LINK_ENTRY_T prNext
    )
{
    prNext->prPrev = prPrev;
    prPrev->prNext = prNext;

    return;
} /* end of __linkDel() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will delete a specified entry from link list.
*        NOTE: the entry is in an initial state.
*
* \param prEntry    Specified link head(entry)
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
linkDel (
    IN P_LINK_ENTRY_T prEntry
    )
{
    __linkDel(prEntry->prPrev, prEntry->prNext);

    LINK_ENTRY_INITIALIZE(prEntry);

    return;
} /* end of linkDel() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will delete a specified entry from link list and then add it
*        after the specified link head.
*
* \param[in] prEntry        Specified link head(entry)
* \param[in] prOtherHead    Another link head to add it after
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
linkMove (
    IN P_LINK_ENTRY_T prEntry,
    IN P_LINK_T prLink
    )
{
    __linkDel(prEntry->prPrev, prEntry->prNext);
    linkAdd(prEntry, prLink);

    return;
} /* end of linkMove() */


/*----------------------------------------------------------------------------*/
/*!
* \brief This function will delete a specified entry from link list and then add it
*        before the specified link head.
*
* \param[in] prEntry        Specified link head(entry)
* \param[in] prOtherHead    Another link head to add it before
*
* \return (none)
*/
/*----------------------------------------------------------------------------*/
__KAL_INLINE__ VOID
linkMoveTail (
    IN P_LINK_ENTRY_T prEntry,
    IN P_LINK_T prLink
    )
{
    __linkDel(prEntry->prPrev, prEntry->prNext);
    linkAddTail(prEntry, prLink);

    return;
} /* end of linkMoveTail() */

#endif /* _LINK_H */

