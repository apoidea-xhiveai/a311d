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
    PIC_OP_FORMAT_CONVERT,
    PIC_OP_SCALE
} PicOperation_t;

typedef enum {
    PIC_FORMAT_NV12,
    PIC_FORMAT_NV21,
    PIC_FORMAT_I420,
    PIC_FORMAT_YV12,
    PIC_FORMAT_RGB24,
    PIC_FORMAT_RGB32,
} PicFormat_t;

typedef struct _PicFormatConvert_t {
    PicFormat_t src_format;
    PicFormat_t dest_format;

    unsigned int width;
    unsigned int height;
} PicFormatConvert_t;

typedef struct _PicScale_t {
    PicFormat_t format;

    unsigned int src_width;
    unsigned int src_height;

    unsigned int dest_width;
    unsigned int dest_height;
} PicScale_t;

typedef struct _PicSetting_t {
    union {
        PicFormatConvert_t fmt_con;
        PicScale_t         pic_scl;
    } config_t;

    PicOperation_t op;
} PicSetting_t;

/*
* To generate the picture processing handler
*   PicFormatConvert_t fmt_con: for color space conversion
*   PicScale_t         pic_scl: for resizing the picture
*/
AMLPIC_HANDLE_t amlPicInit(AMLPIC_IN PicSetting_t *config);

/*
* To do the configured picture processing
*   unsigned char *src_pic:    the raw picture data
*   unsigned char  **dest_pic: proceeded picture data
*   unsigned int *dest_pic_sz: the size of the proceeded picture data
*/
int amlPicProc(AMLPIC_IN  AMLPIC_HANDLE_t handle,
               AMLPIC_IN  unsigned char *src_pic,
               AMLPIC_OUT unsigned char  **dest_pic,
               AMLPIC_OUT unsigned int *dest_pic_sz);

/*
* To release the picture processing handler
*/
void amlPicRelease(AMLPIC_IN  AMLPIC_HANDLE_t handle);

__END_DECLS

#endif /* __AML_PIC_H_ */