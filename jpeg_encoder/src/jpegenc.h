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


#ifndef __JPEG_ENCODER_H_
#define __JPEG_ENCODER_H_

__BEGIN_DECLS

#ifndef JPEGEN_IN
#define JPEGEN_IN
#endif

#ifndef JPEGEN_OUT
#define JPEGEN_OUT
#endif

#ifndef JPEGEN_INOUT
#define JPEGEN_INOUT
#endif

#define ENV_JPEG_ENCODER_DEBUG "JPEG_ENCODE_DEBUG"

typedef void* JPEGEN_HANDLE_t;

typedef enum{
    FMT_YUV422_SINGLE = 0,  /*Input|Output*/
    FMT_YUV444_SINGLE,      /*Input|Output*/
    FMT_NV21,
    FMT_NV12,               /*default input format*/
    FMT_YUV420,             /*default output format, Input|Output*/
    FMT_YUV444_PLANE,       /*Input*/
    FMT_RGB888,
    FMT_RGB888_PLANE,
    FMT_RGB565,
    FMT_RGBA8888,
    MAX_FRAME_FMT
} jpegenc_frame_fmt;

typedef struct _JpegEncodeParam_t {
    int quality;
    int iformat;  /*jpegenc_frame_fmt*/
    int oformat;  /*jpegenc_frame_fmt*/
    int timeout;
    int block_mode;
} JpegEncodeParam_t;

typedef struct _JpegEnSetting_t {
    int width;
    int height;
    int scale;
    int channel_id;

    int multi_proc;  /*1: multiple processes, 0: multiple threads*/

    /*if *enParam is NULL, to use default values*/
    JpegEncodeParam_t *enParam;
} JpegEnSetting_t;


/*
* Initialize the jpeg encoder
*/
JPEGEN_HANDLE_t amlJpegEncodeInit(JPEGEN_IN JpegEnSetting_t *config);

/*
* Encode the YUV format picture into the jpeg format picture
*
* JPEGEN_HANDLE_t handle:    the jpeg encoder handler
* unsigned char *src_pic:    YUV format picture data
* int src_width:             the width of the picture
* int src_height:            the height of the picture
* unsigned char  *dest_jpeg: encoded jpeg picture data
* int *dest_jpeg_sz:         the size of the jpeg picture
*/
int amlJpegEncodeProc(JPEGEN_IN  JPEGEN_HANDLE_t handle,
                      JPEGEN_IN  unsigned char *src_pic,
                      JPEGEN_IN  int src_width,
                      JPEGEN_IN  int src_height,
                      JPEGEN_OUT unsigned char  *dest_jpeg,
                      JPEGEN_OUT int *dest_jpeg_sz);

/*
* Encode the original and resized yuv picture into the jpeg picture
* It is normally for the thumbnail request!
*
* JPEGEN_HANDLE_t handle:    the jpeg encoder handler
* unsigned char *src_pic:    original YUV picture data
* unsigned char *scl_pic:    resized YUV picture data
* unsigned char *dest_src_jpeg: encoded original jpeg picture data
* int *dest_src_jpeg_sz:        the size of the original jpeg picture
* unsigned char *dest_scl_jpeg: encoded resized jpeg picture data
* int *dest_scl_jpeg_sz:        the size of the resized jpeg picture
*/
int amlJpegEncodeBothProc(JPEGEN_IN  JPEGEN_HANDLE_t handle,
                          JPEGEN_IN  unsigned char *src_pic,
                          JPEGEN_IN  unsigned char *scl_pic,
                          JPEGEN_OUT unsigned char  *dest_src_jpeg,
                          JPEGEN_OUT int *dest_src_jpeg_sz,
                          JPEGEN_OUT unsigned char  *dest_scl_jpeg,
                          JPEGEN_OUT int *dest_scl_jpeg_sz);

/*
* Release the jpeg encoder
*/
void amlJpegEncodeRelease(JPEGEN_IN  JPEGEN_HANDLE_t handle);

__END_DECLS

#endif /* __JPEG_ENCODER_H_ */
