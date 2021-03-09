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
* FILE NAME: xhiveai.h
*
* PURPOSE: header file of xhiveai platform library
*
* DEVELOPMENT HISTORY:
* Date        Name       Description
* ---------   ---------- -----------------------------------------------
* 2021-01-13  Jun Yu     Initial creating
************************************************************************/

#ifndef __XHIVEAI_H_
#define __XHIVEAI_H_

#include "xhiveai_callback.h"
#include "xhiveai_common.h"

__BEGIN_DECLS

#ifndef XHIVEAI_IN
#define XHIVEAI_IN
#endif

#ifndef XHIVEAI_OUT
#define XHIVEAI_OUT
#endif

#ifndef XHIVEAI_INOUT
#define XHIVEAI_INOUT
#endif

typedef enum xHiveAiDataSource_t {
    XHAI_DS_Unknown,
    XHAI_DS_Url,
    XHAI_DS_UsbCamera,
    XHAI_DS_MipiCamera
} xHiveAiDataSource_t;

typedef struct xHiveAiSetting_t {
    xHiveAiDataSource_t dst;
    char *url;
    char *alias;       /*the alias name to be displayed on the window*/

    char *pl_name;     /*the pipeline config name*/

    void *app_data;    /*the app data used by the caller*/
} xHiveAiSetting_t;

typedef struct xHiveAiCbConfig_t {
    xHiveAiPicFmt_t pic_type;  /*XHAI_PIC_jpeg(default)*/
    int pic_width;             /*0(default): original picture size*/
    int pic_height;            /*0(default): original picture size*/
} xHiveAiCbConfig_t;

typedef struct xHiveAiHandle_t {
    xHiveAiSetting_t setting;

    int  play_id;
    void *pipeline;
    void *runtime;

    XHAI_ERRORS (*init)(XHIVEAI_IN struct xHiveAiHandle_t *self);
    XHAI_ERRORS (*run)(XHIVEAI_IN struct xHiveAiHandle_t *self);
    XHAI_ERRORS (*stop)(XHIVEAI_IN struct xHiveAiHandle_t *self);
    XHAI_ERRORS (*pause)(XHIVEAI_IN struct xHiveAiHandle_t *self);
    XHAI_ERRORS (*resume)(XHIVEAI_IN struct xHiveAiHandle_t *self);
    /*upgrade the AI algorithm library*/
    XHAI_ERRORS (*upgrade)(XHIVEAI_IN struct xHiveAiHandle_t *self);

    /*wait until the multimedia processing is complete*/
    XHAI_ERRORS (*waitOnProcess)(XHIVEAI_IN struct xHiveAiHandle_t *self);

    XHAI_ERRORS (*setConfig)(XHIVEAI_IN struct xHiveAiHandle_t *self,
                             XHIVEAI_IN xHiveAiConfig_t nConfType,
                             XHIVEAI_IN void *pConfigStructure);

    XHAI_ERRORS (*getConfig)(XHIVEAI_IN struct xHiveAiHandle_t *self,
                             XHIVEAI_IN xHiveAiConfig_t nConfType,
                             XHIVEAI_INOUT void *pConfigStructure);

    XHAI_ERRORS (*setParameter)(XHIVEAI_IN struct xHiveAiHandle_t *self,
                                XHIVEAI_IN xHiveAiParam_t nParamType,
                                XHIVEAI_IN void *pParamStructure);

    XHAI_ERRORS (*getParameter)(XHIVEAI_IN struct xHiveAiHandle_t *self,
                                XHIVEAI_IN xHiveAiParam_t nParamType,
                                XHIVEAI_INOUT void *pParamStructure);

    XHAI_ERRORS (*registerCallback)(XHIVEAI_IN struct xHiveAiHandle_t *self,
                                    XHIVEAI_IN xHiveAiCbConfig_t *pSetting,
                                    XHIVEAI_IN xHiveAiCallback_t *pCallBacks);
} xHiveAiHandle_t;

typedef xHiveAiHandle_t* xHiveAiHandler;

xHiveAiHandler xhiveai_create(xHiveAiSetting_t *setting);
void xhiveai_destroy(xHiveAiHandler *pHandle);

__END_DECLS

#endif /* __XHIVEAI_H_ */