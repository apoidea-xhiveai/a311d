/*
* All Rights Reserved
*
* APOIDEA CONFIDENTIAL
* Copyright 2017 Apoidea Technology All Rights Reserved.
* The source code contained or described herein and all documents related to
* the source code ("Material") are owned by Apoidea International Ltd or its
* suppliers or licensors. Title to the Material remains with Apoidea International Ltd
* or its suppliers and licensors. The Material contains trade secrets and
* proprietary and confidential information of Apoidea or its suppliers and
* licensors. The Material is protected by worldwide copyright and trade secret
* laws and treaty provisions. No part of the Material may be used, copied,
* reproduced, modified, published, uploaded, posted, transmitted, distributed,
* or disclosed in any way without Apoidea's prior express written permission.
*
* No license under any patent, copyright, trade secret or other intellectual
* property right is granted to or conferred upon you by disclosure or delivery
* of the Materials, either expressly, by implication, inducement, estoppel or
* otherwise. Any license under such intellectual property rights must be
* express and approved by Apoidea in writing.
*/

/***********************************************************************
* FILE NAME: Mag_list.h
*
* PURPOSE: list data structure implementation
*
* DEVELOPMENT HISTORY:
* Date        Name       Description
* ---------   ---------- -----------------------------------------------
* 2015-08-10  Jun Yu     Initial creating
************************************************************************/

#ifndef _MAG_LIST_H__
#define _MAG_LIST_H__

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define list_offsetof(TYPE, MEMBER) ( (uintptr_t)(&((TYPE *)0)->MEMBER) )

#define container_of(ptr, type, member) __extension__({			\
	const __typeof__( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (const char *)__mptr - list_offsetof(type, member) );})

#define list_entry(ptr, type, member) container_of(ptr, type, member)

typedef struct list_t{
    struct list_t *next;
    struct list_t *prev;
}List_t;

static inline void INIT_LIST(List_t *head){
    head->prev = head;
    head->next = head;
}

/** add a new entry to the list tail
 *
 * @param new
 *        new entry to be added
 * @param head
 *        list head
 */
static inline void list_add_tail(List_t *pnew, List_t *head){
    pnew->next = head;
    head->prev->next = pnew;
    pnew->prev = head->prev;
    head->prev = pnew;
}

/** add a new entry after the node
 *
 * @param new
 *        new entry to be added
 * @param head
 *        list head
 */
static inline void list_add(List_t *pnew, List_t *head){
    pnew->prev = head;
    head->next->prev = pnew;
    pnew->next = head->next;
    head->next = pnew;
}

static inline void list_del(List_t *node){
    node->prev->next = node->next;
    node->next->prev = node->prev;

    node->next = node;
    node->prev = node;
}

static inline int is_added_list(List_t *node){
    if ((node->next == node) && (node->prev == node))
        return 0;
    else
        return 1;
}

static inline int is_list_empty(List_t *listHead){
    if ((listHead->next == listHead) && (listHead->prev == listHead))
        return 1;
    else
        return 0;
}

#ifdef __cplusplus
}
#endif

#endif