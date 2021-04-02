/*
* All Rights Reserved
*
* APOIDEA CONFIDENTIAL
* Copyright 2020 Apoidea Technology All Rights Reserved.
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
* FILE NAME: amldec.h
*
* PURPOSE: header file of amlogic A311D hardware decoder library
*
* DEVELOPMENT HISTORY:
* Date        Name       Description
* ---------   ---------- -----------------------------------------------
* 2021-01-04  Jun Yu     Initial creating
************************************************************************/

#ifndef __AML_DEC_H_
#define __AML_DEC_H_

#include <inttypes.h>
#include "Mag_list.h"

__BEGIN_DECLS

#ifndef AMLDEC_IN
#define AMLDEC_IN
#endif

#ifndef AMLDEC_OUT
#define AMLDEC_OUT
#endif

#ifndef AMLDEC_INOUT
#define AMLDEC_INOUT
#endif

#define DEC_NUM_DATA_POINTERS 3

typedef void* AMLDEC_HANDLE_t;

typedef enum{
    kVdecBuffer_Unknown,
    kVdecBuffer_DMA,
    kVdecBuffer_MEM
} VdecBuffer_Type_t;

// vdec: format=NV12 and nplane=2 are default value
typedef enum {
    VDEC_FORMAT_NV12 = 0,  // YYYY.....UV.... (default value)
    VDEC_FORMAT_NV21,  // YYYY.....VU....
    VDEC_FORMAT_I420,  // YYYY.....U....V...  I420
    VDEC_FORMAT_YV12,  // YYYY.....V....U....
    VDEC_FORMAT_YUYV,  // YUYV.....
    VDEC_FORMAT_UYVY,  // UYVY.....
    VDEC_FORMAT_RGB,   // RGB.....
    VDEC_FORMAT_BGR,   // BGR.....
    VDEC_FORMAT_RGBA,  // RGBA.....
    VDEC_FORMAT_BGRA,  // BGRA.....
    VDEC_FORMAT_RGBX,  // BGRX..... X means A=0xFF
    VDEC_FORMAT_ARGB,  // ARGB.....
    VDEC_FORMAT_ABGR,  // ABGR.....
    VDEC_FORMAT_MAX,   // Use the default video format: NV12

    ADEC_FORMAT_PCM_S16LE,
    ADEC_FORMAT_PCM_S16BE,
    ADEC_FORMAT_PCM_U16LE,
    ADEC_FORMAT_PCM_U16BE,
    ADEC_FORMAT_PCM_ULAW,
    ADEC_FORMAT_PCM_ALAW,
    ADEC_FORMAT_ADPCM_G726,
    ADEC_FORMAT_AAC,

    ADEC_FORMAT_MAX

} DEC_FORMAT_t;

typedef enum {
    DEC_VCODEC_NONE = 0,
    DEC_VCODEC_VP8,
    DEC_VCODEC_H263,
    DEC_VCODEC_H264,
    DEC_VCODEC_H265,
    DEC_VCODEC_JPEG,
    DEC_VCODEC_VP9,
    DEC_VCODEC_MPEG2,
} DEC_CODEC_t;;

typedef struct _amlDecInFrame_t {
    DEC_CODEC_t codec;
    int is_key_frame;

    int64_t pts_us;  /*pts in us*/
    void    *data;
    int     size;
} AMLDEC_DATA_t;

typedef enum {
    DEC_DATA_GST,      /* accept gstreamer <GstSample *frame> */
    DEC_DATA_FFMPEG,   /* accept ffmpeg    <AVPacket* pkt> */
    DEC_DATA_SPEC      /* accept <AMLDEC_DATA_t *frame> */
} DEC_DATA_TYPE_t;

typedef enum AMLDEC_PARAMTYPE_t {
    DEC_TypeStartUnused            = 0x01000000,
    DEC_TypeVdecInputSize,         /**< ref: int (the input ES buffer size in KB)*/
    DEC_TypeVdecInputNbuf,         /**< ref: int (the number of the input ES buffer)*/
    DEC_TypeVdecOutputNbuf,        /**< ref: int (the number of the output ES buffer)*/
    DEC_TypeVdecQueueMaxLen,       /**< ref: int (the playing duration[in seconds]
                                                  of the decoded video frame queue)*/

    DEC_TypeMax                    = 0x7FFFFFFF
} AMLDEC_PARAMTYPE_t;

typedef struct _DecConfig_t {
    DEC_FORMAT_t format;

    int play_id;
    int src_width;   /*original video width*/
    int src_height;  /*original video height*/

    int dest_width;  /*resized video width (no resize: = src_width)*/
    int dest_height; /*resized video height (no resize: = src_height)*/

    VdecBuffer_Type_t tbuf;

    void *opaque;    /*for some private data of the user*/
} DEC_CONFIG_t;

typedef struct _DecFrame_t {
    List_t node;

    int64_t pts_us;
    void    *data;
    int     size;
    VdecBuffer_Type_t data_type;

    DEC_FORMAT_t fmt;
    int          width;
    int          height;

    void *buf[DEC_NUM_DATA_POINTERS];
    int  linesize[DEC_NUM_DATA_POINTERS];
    int  nplanes;

    void *opaque;  /*for some private data of the user*/
} DEC_FRAME_t;

/*
* To generate the hardware video/audio decoder handler
*/
/*
Video:
  <only decoding without resizing and color space conversion>
     format:      VDEC_FORMAT_NV12
     src_width:   original picture width
     src_height:  original picture height
     dest_width:  0
     dest_height: 0
  <do resizing & color space conversion(optional)>
     format:      set the DEC_FORMAT_t (default: VDEC_FORMAT_NV12)
     src_width:   original picture width
     src_height:  original picture width
     dest_width:  defined
     dest_height: defined

  <only color space conversion>
     format:      set the DEC_FORMAT_t other than VDEC_FORMAT_NV12
     src_width:   original picture width
     src_height:  original picture width
     dest_width:  0
     dest_height: 0
*/
AMLDEC_HANDLE_t amlDecInit(AMLDEC_IN DEC_CONFIG_t *config);

/*
* To start the decoder
*/
int amlDecStart(AMLDEC_IN  AMLDEC_HANDLE_t handle);

/*
* To stop the decoder
*/
int amlDecStop(AMLDEC_IN  AMLDEC_HANDLE_t handle);

/*
* To set the video/audio decoder parameters before the decoder running up
*/
int amlDecSetParam(AMLDEC_IN AMLDEC_HANDLE_t     handle,
                   AMLDEC_IN AMLDEC_PARAMTYPE_t  nParamType,
                   AMLDEC_IN void *pParamStructure);

/*
* Send out parsed video/audio data to the hardware deocder
*   void *data:  one of below 3 types
*                 GstSample *data
*                 AVPacket  *data
*                 AMLDEC_DATA_t *data
*
*   DEC_DATA_TYPE_t type:  spcify the input data type
*
* return:
*     GST_FLOW_OK, GST_FLOW_ERROR, GST_FLOW_FLUSHING
*
*/
int amlDecSendData(AMLDEC_IN  AMLDEC_HANDLE_t handle,
                   AMLDEC_IN  void  *data,
                   AMLDEC_IN  DEC_DATA_TYPE_t type);

/*
* Get one decoded frame from the hardware decoder
*   DEC_FRAME_t **frame:
*               return the pointer to the decoded frame.
*               Note:
*               1) After it is used up, need to call amlDecReleaseFrame() to release it
*               2) Should release it as soon as possible, otherwise, it might cause the
*                  decoder not working as too much data accumulated.
*
*/
int amlDecReceiveFrame(AMLDEC_IN  AMLDEC_HANDLE_t handle,
                       AMLDEC_OUT DEC_FRAME_t **frame);

/*
* Release the frame
*   DEC_FRAME_t *frame: point to the decoded frame
*
*/
int amlDecReleaseFrame(AMLDEC_IN  AMLDEC_HANDLE_t handle,
                       AMLDEC_OUT DEC_FRAME_t *frame);

/*
* To release the decoder handler
*/
void amlDecRelease(AMLDEC_IN  AMLDEC_HANDLE_t handle);



/*
*  copy the dma buffer data to user space buffer
*/
int amlDecDma2User(AMLDEC_IN  AMLDEC_HANDLE_t handle,
                   AMLDEC_IN  DEC_FRAME_t *frame,
                   AMLDEC_OUT void *usrbuf);

__END_DECLS

#endif /* __AML_DEC_H_ */