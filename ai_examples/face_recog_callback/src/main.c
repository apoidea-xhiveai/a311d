#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xhiveai.h"

/*
 void *pAppData: setting.app_data
*/
static int CallbackEventHandler( void *pAppData,
                                 xHiveAiEventType_t eEvent,
                                 void *pEventData ) {
    switch (eEvent) {
        case XHAI_EVENT_FaceRecog:
        {
            xHiveAiCB_FaceRecog_t *data = (xHiveAiCB_FaceRecog_t *)pEventData;
            xHiveAiRectangle_t *rect;
            int i = 0;

            // data->pic: the jpeg video data
            // data->pic_size: the size of the jpeg video data

            if (data->face_rect) {
                while(data->face_rect[i].x != -1 &&
                      data->face_rect[i].y != -1 &&
                      data->face_rect[i].width != -1 &&
                      data->face_rect[i].height != -1) {
                    printf("[face_recog][%s]: %dx%d %d:%d id:%s, name:%s, score:%d\n",
                             data->time,
                             data->face_rect[i].x,
                             data->face_rect[i].y,
                             data->face_rect[i].width,
                             data->face_rect[i].height,
                             data->person_id[i],
                             data->person_name[i],
                             data->person_score[i]);
                    i++;
                }
            } else {
                printf("[face_recog]: No person found!\n");
            }
        }
            break;

        default:
            printf("Unsupported event: %d!\n", eEvent);
            break;
    }
}

int main(int argc, const char *argv[]) {
    xHiveAiSetting_t setting;
    xHiveAiHandler handle;
    xHiveAiCbConfig_t cb_config;
    xHiveAiCallback_t callback;

    char pl[32] = "face_recog_callback";
    char alias[32] = "test video 1";

    if (argc < 2) {
        printf("%s <url>\n", argv[0]);
        return -1;
    }

    setting.dst      = XHAI_DS_Url;     // use URL type video stream
    setting.url      = strdup(argv[1]); // http/rtsp ...
    /*must be "face_recog_callback"*/
    setting.pl_name  = pl;
    /*give the short description to the video stream*/
    setting.alias    = alias;
    /*the application private data that would be returned as <void *pAppData> in CallbackEventHandler()*/
    setting.app_data = NULL;

    handle = xhiveai_create(&setting);
    printf("xhiveai_create() -- OK!\n");

    if (handle->init(handle) != XHAI_OK) {
        printf("failed to init\n", argv[1]);
        return -1;
    }
    printf("init() -- OK!\n");

    callback.EventHandler = CallbackEventHandler;

    cb_config.pic_type  = XHAI_PIC_jpeg;

    /*use video original size*/
    cb_config.pic_width = 0;
    cb_config.pic_height = 0;

    /*register the application callbacks for recieving the AI results*/
    handle->registerCallback(handle,
                             &cb_config,
                             &callback);

    if (handle->run(handle) != XHAI_OK) {
        printf("failed to run\n", argv[1]);
        return -1;
    }
    printf("run() -- OK!\n");

    /*endless waiting until the playing is complete*/
    handle->waitOnProcess(handle);

    printf("Complete!!!\n");
}




