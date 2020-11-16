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

#ifndef _CALLBACK_H_
#define _CALLBACK_H_

__BEGIN_DECLS

typedef enum
{
    /*encoding format*/
    EP_FORMAT_JPEG        = 0,      /* JPEG format*/
    EP_FORMAT_H264        = 1,      /* H264 format*/
    EP_FORMAT_H265        = 2,      /* H265 format*/

    /*decoding format*/
    EP_FORMAT_YVU420SP    = 100,      /* YVU420SP format*/

    EP_FORMAT_BGR_PACKAGE = 101,      /* BGR Package format*/
    EP_FORMAT_RGB_PACKAGE = 102,      /* RGB Package format*/
    EP_FORMAT_BGR_PLANAR  = 103,      /* BGR Planar format*/
    EP_FORMAT_RGB_PLANAR  = 104,      /* BGR Planar format*/

    /* audio */
    EP_FORMAT_PCM         = 200,
}ENUM_EPFrameFormat;

typedef enum
{
    EP_AUDIO = 0,    /*audio*/
    EP_VIDEO = 1,    /*video*/
}ENUM_EPFrameType;

typedef struct
{
    ENUM_EPFrameFormat   eFrameFormat;          /*Frame data format*/
    unsigned long long   uFrameTimeStamp;       /*Frame time stamp*/
    unsigned int         uFrameWidth;           /*Frame width*/
    unsigned int         uFrameHeight;          /*Frame height*/
    unsigned int         uFrameStride;          /*Frame stride*/
    unsigned char*       pszFrameData;          /*Frame data buffer*/
    unsigned long long   uFramePhyAddr;         /*Frame data phy address*/
    unsigned int         uFrameSize;            /*Frame size*/
    int                  nFramePrivateID;
    int                  nFrameID;
    int                  nFps;
}ST_EPVideoFrameInfoData; /*Video data structure*/

typedef struct
{
    ENUM_EPFrameFormat   eFrameFormat;          /*Frame data format*/
    unsigned long long   uFrameTimeStamp;       /*Frame time stamp*/
    unsigned char*       pszFrameData;          /*Frame data buffer*/
    unsigned long long   uFramePhyAddr;         /*Frame data phy address*/
    unsigned int         uFrameSize;            /*Frame size*/
    int                  nFramePrivateID;
}ST_EPAudioFrameInfoData; /*Audio data structure*/

typedef enum
{
    EP_EVENT_CALLBACK = 0,  /*Event callback*/
    EP_DATA_CALLBACK  = 1,  /*Data callback*/
}ENUM_EPCallbackType;

typedef struct
{
    int    nEventStatus;         /*Channel status*/
    char*  pstEventText;         /*Event content*/
}ST_EPEventInfoData; /*Event data structure*/

typedef struct
{
    int                               nChnID;                /*Channel ID*/
    ENUM_EPFrameType                  eFrameType;            /*Frame Type*/
    union
    {
        ST_EPVideoFrameInfoData       stVideoFrame;         /*Video data*/
        ST_EPAudioFrameInfoData       stAudioFrame;         /*Audio data*/
    };

}ST_EPFrameInfoData; /*Frame data structure*/

typedef struct
{
    int                                nChnID;                 /*Channel ID*/
    ENUM_EPCallbackType                eCallbackType;          /*Callback Type:0-Event 1-Data*/
    ST_EPEventInfoData                 stCallbackEventInfo;    /*Event callback content*/
    ST_EPFrameInfoData                 stCallbackFrameInfo[2]; /*Data callback content[0]:original data,[1]:resize data*/
}ST_EPCallbackData; /*callback data structure*/

typedef struct ST_InputDataInfo_s {
    void *cb_aifncb;         /*callback function*/
    void *cb_priv;            /*pointer of class member*/
    int  rsz_width;           /* video image resize width, IN */
    int  rsz_height;          /* video image resize height, IN */
    int  format;              /*the converted data format for AI algorithm*/
} ST_InputDataInfo_t;

typedef int (* fDecoderCB)(void *p_pOwner, ST_EPCallbackData p_stCallback);

__END_DECLS

#endif /* _CALLBACK_H_ */
