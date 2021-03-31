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
* FILE NAME: xhiveai_callback.h
*
* PURPOSE: header file of xhiveai callbacks's related definitions
*
* DEVELOPMENT HISTORY:
* Date        Name       Description
* ---------   ---------- -----------------------------------------------
* 2021-02-26  Jun Yu     Initial creating
************************************************************************/

#ifndef __XHIVEAI_CALLBACK_H_
#define __XHIVEAI_CALLBACK_H_

#include "xhiveai_common.h"

__BEGIN_DECLS

typedef enum xHiveAiEventType_t
{
    /*must in the sequence of AI_PARSED_TYPE_t in ai_hal.h*/
    XHAI_EVENT_FaceDetect = 0,  /**< reference:  xHiveAiCB_FaceDetect_t */
    XHAI_EVENT_FaceRecog,       /**< reference:  xHiveAiCB_FaceRecog_t */
    XHAI_EVENT_CarplateRecog,   /**< reference:  xHiveAiCB_CarplateRecog_t */

    XHAI_EVENT_Video = 0xFFFF,  /**< reference:  xHiveAiCB_Video_t */

    XHAI_EVENT_Max
} xHiveAiEventType_t;

typedef struct xHiveAiCallback_t
{
   int (*EventHandler)( void *pAppData,
                        xHiveAiEventType_t eEvent,
                        void *pEventData );
} xHiveAiCallback_t;

typedef struct xHiveAiRectangle_t {
    int x;      /*X coordinate of top-left point*/
    int y;      /*Y coordinate of top-left point*/
    int width;  /*The width of the rectangle*/
    int height; /*The height of the rectangle*/
} xHiveAiRectangle_t;

typedef struct xHiveAiCB_Video_t {
    char url[MAX_CONFIG_VALUE_LEN];    /*the stream playing URL*/
    char alias[MAX_CONFIG_VALUE_LEN];  /*the alias name of the URL*/

    unsigned char *pic; /*the jpeg format picture*/
    int   pic_size;     /*the size of the jpeg format picture*/

    char time[32];      /*the time of face detected picture
                          format: "year-month-day hour:minute:second"*/
} xHiveAiCB_Video_t;

typedef struct xHiveAiCB_FaceDetect_t {
    char url[MAX_CONFIG_VALUE_LEN];    /*the stream playing URL*/
    char alias[MAX_CONFIG_VALUE_LEN];  /*the alias name of the URL*/

    unsigned char *pic; /*the jpeg format picture*/
    int   pic_size;     /*the size of the jpeg format picture*/

    char time[32];      /*the time of face detected picture
                          format: "year-month-day hour:minute:second"*/

    xHiveAiRectangle_t *face_rect; /*the end of rectangles array is
                                     (x: -1, y: -1, width: -1, height: -1)*/
} xHiveAiCB_FaceDetect_t;

typedef struct xHiveAiCB_FaceRecog_t {
    char url[MAX_CONFIG_VALUE_LEN];    /*the stream playing URL*/
    char alias[MAX_CONFIG_VALUE_LEN];  /*the alias name of the URL*/

    unsigned char *pic; /*the jpeg format picture*/
    int   pic_size;     /*the size of the jpeg format picture*/

    char time[32];      /*the time of face detected picture
                          format: "year-month-day hour:minute:second"*/

    xHiveAiRectangle_t *face_rect; /*The faces position in the picture.
                                     the end of rectangles array is
                                     (x: -1, y: -1, width: -1, height: -1)*/

    char **person_id;    /*the recognized people id against the picture library.
                           the end of person_id array is NULL*/

    char **person_name;  /*the recognized people id against the picture library.
                           the end of person_id array is NULL*/

    int *person_score; /*the AI score of the recognized people against the picture library.
                         the end of person_score array is -1*/
} xHiveAiCB_FaceRecog_t;

typedef struct xHiveAiCB_CarplateRecog_t {
    char url[MAX_CONFIG_VALUE_LEN];    /*the stream playing URL*/
    char alias[MAX_CONFIG_VALUE_LEN];  /*the alias name of the URL*/

    unsigned char *pic; /*the jpeg format picture*/
    int   pic_size;     /*the size of the jpeg format picture*/

    char time[32];      /*the time of face detected picture
                          format: "year-month-day hour:minute:second"*/

    xHiveAiRectangle_t *face_rect; /*The faces position in the picture.
                                     the end of rectangles array is
                                     (x: -1, y: -1, width: -1, height: -1)*/

    char **carplate_id;  /*the recognized car plate id.
                           the end of carplate_id array is NULL*/
} xHiveAiCB_CarplateRecog_t;

__END_DECLS

#endif /* __XHIVEAI_CALLBACK_H_ */