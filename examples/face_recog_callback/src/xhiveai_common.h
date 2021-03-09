/*
* All Rights Reserved
*
* APOIDEA CONFIDENTIAL
* Copyright 2016 Apoidea Technology All Rights Reserved.
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
* FILE NAME: xhiveai_common.h
*
* PURPOSE: Header file of xhiveai common definitions
*
* DEVELOPMENT HISTORY:
* Date             Name                       Description
* ---------     ----------    ------------------------------------------
* 2020-01-08      Yu Jun                    Initial Create
************************************************************************/

#ifndef __XHIVEAI_COMMON_H_
#define __XHIVEAI_COMMON_H_

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <errno.h>

__BEGIN_DECLS

/*the start frames are stored (N, N+1, ....)
  default number: 0
*/
#define ENV_XHIVEAI_FRAMES_OFFSET "XHIVEAI_FRAMES_OFFSET"

/*how many frames are stored (1, 2, ....)
  default number: 10
*/
#define ENV_XHIVEAI_FRAMES "XHIVEAI_FRAMES"

/*enable to capture the decoded video frames (0/1)
  /var/xhiveai_vdec#N.yuv

  default: 0
*/
#define ENV_XHIVEAI_VDEC   "XHIVEAI_VDEC"

/*enable to capture the display video frames (0/1)
  /var/xhiveai_disp#N.rgb

  default: 0
*/
#define ENV_XHIVEAI_DISP   "XHIVEAI_DISP"

/*enable to capture the AI video frames (0/1)
  /var/xhiveai_ai#N.rgb

  default: 0
*/
#define ENV_XHIVEAI_AI   "XHIVEAI_AI"

/*enable to capture the Pic Proc video frames (0/1)
  /var/xhiveai_pp#N.rgb

  default: 0
*/
#define ENV_XHIVEAI_PP   "XHIVEAI_PP"

typedef void* XHAI_COMPHANDLE;

typedef enum {
    XHAI_OK                  = 0,    // Everything's swell.
    XHAI_NO_ERROR            = 0,    // No errors.

    XHAI_UNKNOWN_ERROR       = 0x80000000,
    XHAI_NO_MEMORY           = -ENOMEM,
    XHAI_INVALID_OPERATION   = -ENOSYS,
    XHAI_BAD_VALUE           = -EINVAL,
    XHAI_BAD_TYPE            = 0x80000001,
    XHAI_NAME_NOT_FOUND      = -ENOENT,
    XHAI_PERMISSION_DENIED   = -EPERM,
    XHAI_NO_INIT             = -ENODEV,
    XHAI_ALREADY_EXISTS      = -EEXIST,
    XHAI_DEAD_OBJECT         = -EPIPE,

    XHAI_BAD_INDEX           = -EOVERFLOW,
    XHAI_NOT_ENOUGH_DATA     = -ENODATA,
    XHAI_WOULD_BLOCK         = -EWOULDBLOCK,
    XHAI_TIMED_OUT           = -ETIMEDOUT,
    XHAI_UNKNOWN_TRANSACTION = -EBADMSG,

    XHAI_PARSE_ERROR         = 0x80000002,
    XHAI_INVALID_URL         = 0x80000003,
    XHAI_PIPELINE_ERROR      = 0x80000004,
    XHAI_LINK_ERROR          = 0x80000005,
    XHAI_NOT_IMPLEMENTED     = 0x80000006,
} XHAI_ERRORS;

typedef enum xHiveAiConfig_t {

    XHIVEAI_ConfigStartUnused          = 0x01000000,
    XHIVEAI_ConfigVideoInfo,             /**< reference:  */

    XHIVEAI_ConfigMax                  = 0x7FFFFFFF
} xHiveAiConfig_t;

typedef enum xHiveAiParam_t {

    XHIVEAI_ParamStartUnused          = 0x01000000,
    XHIVEAI_ParamVideoInfo,             /**< reference:  */

    XHIVEAI_ParamMax                  = 0x7FFFFFFF
} xHiveAiParam_t;

typedef enum xHiveAiPicFmt_t {
    XHAI_PIC_jpeg = 0,
    XHAI_PIC_nv12,
    XHAI_PIC_rgb,
    XHAI_PIC_bgra,  /*for dfb using*/
} xHiveAiPicFmt_t;

/*************************
* Config & Parameter definitions
**************************/

/* setconfig before the component is in EXECUTING state
   getconfig anytime
*/
typedef enum XHAI_CONFIGTYPE_t {

    XHAI_ConfigTypeStartUnused            = 0x01000000,
    XHAI_ConfigTypeKeyValue,             /**< reference: XHAI_CONFIG_KEY_VALUE_t */
    XHAI_ConfigPlayChannelId,            /**< reference: int */
    XHAI_ConfigAppData,                  /**< reference: XHAI_CONFIG_APPDATA_t */
    XHAI_ConfigCallback,                 /**< reference: XHAI_CONFIG_CALLBACK_t */

    XHAI_ConfigTypeMax                    = 0x7FFFFFFF
} XHAI_CONFIGTYPE_t;

/* setparam/getparam in the runtime */
typedef enum XHAI_PARAMTYPE_t {

    XHAI_ParamTypeStartUnused            = 0x01000000,
    XHAI_ParamTypeKeyValue,             /**< reference: XHAI_PARAM_KEY_VALUE_t */
    XHAI_ParamTypeStreamInfo,           /**< reference: XHAI_PARAM_STREAM_INFO_t */

    XHAI_ParamTypeMax                    = 0x7FFFFFFF
} XHAI_PARAMTYPE_t;

#define MAX_CONFIG_KEY_LEN    32
#define MAX_CONFIG_VALUE_LEN  128
#define MAX_PARAM_KEY_LEN     32
#define MAX_PARAM_VALUE_LEN   128

typedef struct {
    int  inport_index;
    char key[MAX_CONFIG_KEY_LEN];
    char value[MAX_CONFIG_VALUE_LEN];
} XHAI_CONFIG_KEY_VALUE_t;

typedef struct {
    int  inport_index;
    void *appdata;
} XHAI_CONFIG_APPDATA_t;

typedef struct {
    int  inport_index;
    void *callback;
} XHAI_CONFIG_CALLBACK_t;

typedef struct {
    int  inport_index;
    char key[MAX_PARAM_KEY_LEN];
    char value[MAX_PARAM_VALUE_LEN];
} XHAI_PARAM_KEY_VALUE_t;

/*
   input video/audio stream information
*/
typedef struct {
    int channel;  /*playing channel id*/

    int inport_index;

    /*original video info*/
    int orig_width;
    int orig_height;
    int orig_vfmt;

    /*decoded[converted] video info (may or may not equal to original video info)*/
    int width;
    int height;
    int vfmt;   /*video DEC_FORMAT_t defined in amldec.h*/

    int tbuf;   /*the type of decoded buffer: DMA/MEM*/
} XHAI_PARAM_STREAM_INFO_t;

__END_DECLS

#endif /* __XHIVEAI_COMMON_H_ */