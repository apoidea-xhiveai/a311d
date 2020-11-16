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

#ifndef __LIBXHIVEPLAYER_H_
#define __LIBXHIVEPLAYER_H_

__BEGIN_DECLS

typedef enum {
    xHivePlayer_no_error        = 0,
    xHivePlayer_invalid_url     = -1,
    xHivePlayer_link_src_error  = -2,
    xHivePlayer_link_data_error = -3,
    xHivePlayer_source_error    = -4,
} ErrorCode_t;

enum {
    GST_VIDEO_DATA_FORMAT_NV12  = 0,
    GST_VIDEO_DATA_FORMAT_NV21  = 1,
    GST_VIDEO_DATA_FORMAT_I420  = 2,
    GST_VIDEO_DATA_FORMAT_YV12  = 3,
    GST_VIDEO_DATA_FORMAT_RGB24 = 4,
    GST_VIDEO_DATA_FORMAT_RGB32 = 5
};

/*
url:        the playback url link

channelid： the playback channel id

multi_proc: if it is multi-threads, it should be 0
            if it is multi-processes, it should be 1

cb_setting: The callback setting structure
*/
ErrorCode_t xhiveplayer_vcb(char *url,
                            int channelid,
                            int multi_proc,
                            void *cb_setting);
__END_DECLS

#endif /* __LIBXHIVEPLAYER_H_ */
