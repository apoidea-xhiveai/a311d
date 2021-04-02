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
* FILE NAME: amlpic.h
*
* PURPOSE: header file of amlogic A311D picture processing library
*
* DEVELOPMENT HISTORY:
* Date        Name       Description
* ---------   ---------- -----------------------------------------------
* 2020-03-02  Jun Yu     Initial creating
* 2020-12-30  Jun Yu     Upgrade to version 202011 by using ipc-sdk
************************************************************************/

#ifndef __AML_PIC_H_
#define __AML_PIC_H_

__BEGIN_DECLS

#ifdef MODULE_TAG
#undef MODULE_TAG
#endif
#define MODULE_TAG "aml_pic"

#ifndef AMLPIC_IN
#define AMLPIC_IN
#endif

#ifndef AMLPIC_OUT
#define AMLPIC_OUT
#endif

#ifndef AMLPIC_INOUT
#define AMLPIC_INOUT
#endif

typedef void* AMLPIC_HANDLE_t;

typedef enum {
    /*input user space buffer and output user space buffer. Slowest conversion*/
    PIC_CONVERT_user2user,
    /*input dma buffer and output user space buffer. Slow conversion*/
    PIC_CONVERT_dma2user,
    /*input dma buffer and output dma buffer. Fastest conversion*/
    PIC_CONVERT_dma2dma
} PicCovertType_t;

// PIC_FORMAT_I420 the color displayed to green
typedef enum {
    PIC_FORMAT_NV12 = 0,  // YYYY.....UV....
    PIC_FORMAT_NV21,  // YYYY.....VU....
    PIC_FORMAT_I420,  // YYYY.....U....V...  I420
    PIC_FORMAT_YV12,  // YYYY.....V....U....
    PIC_FORMAT_YUYV,  // YUYV.....
    PIC_FORMAT_UYVY,  // UYVY.....
    PIC_FORMAT_RGB,   // RGB.....
    PIC_FORMAT_BGR,   // BGR.....
    PIC_FORMAT_RGBA,  // RGBA.....
    PIC_FORMAT_BGRA,  // BGRA.....
    PIC_FORMAT_RGBX,  // BGRX..... X means A=0xFF
    PIC_FORMAT_ARGB,  // ARGB.....
    PIC_FORMAT_ABGR,  // ABGR.....

    PIC_FORMAT_MAX
} PicFormat_t;

typedef struct _PicParam_t {
    PicFormat_t format;

    unsigned int width;
    unsigned int height;
} PicParam_t;

typedef struct _PicSetting_t {
    PicParam_t src;
    PicParam_t dest;

    PicCovertType_t op;
    int play_id;
} PicSetting_t;

/*
* To generate the picture processing handler
*   PicFormatConvert_t fmt_con: for color space conversion
*   PicScale_t         pic_scl: for resizing the picture
*/
AMLPIC_HANDLE_t amlPicInit(AMLPIC_IN PicSetting_t *config);

/*
* To do the configured picture processing
*   void *src_pic:   the source picture data
*                      user space buffer: unsigned char *
*                      dma buffer: struct AmlIPCFrame * OR struct AmlIPCVideoFrame *
*   void *dest_pic:  the converted picture data
*                      the caller need to maintain the buffer(malloc/free etc)
*                      user space buffer: unsigned char *
*                      dma buffer: struct AmlIPCFrame * OR struct AmlIPCVideoFrame *
*   unsigned int  *dest_pic_sz: the size of the converted picture data(user 2user mode)
*/
int amlPicProc(AMLPIC_IN  AMLPIC_HANDLE_t handle,
               AMLPIC_IN  void  *src_pic,
               AMLPIC_OUT void  *dest_pic,
               AMLPIC_OUT unsigned int   *dest_pic_sz);

/*
* To release the picture processing handler
*/
void amlPicRelease(AMLPIC_IN  AMLPIC_HANDLE_t handle);

PicFormat_t amlPicFmtMapping(AMLPIC_IN PicFormat_t fmt);

void amlPicRgba2Argb(AMLPIC_IN unsigned char *pic, int size);

void amlPicRgbx2Xrgb(AMLPIC_IN unsigned char *pic, int size);

__END_DECLS

#endif /* __AML_PIC_H_ */