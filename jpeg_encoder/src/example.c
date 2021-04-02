#include "jpegenc.h"

JPEGEN_HANDLE_t jpegEnHandle;

JpegEnSetting_t config;

config.width      = <The width of input YUV picture>
config.height     = <The height of input YUV picture>
config.channel_id = <The jpeg encoding channel id: 1, 2, 3, 4>
config.scale      = 0
config.multi_proc = <There is only 1 hardware jpeg encoder, it requires the data protection for muliple channels encoding case>
                    <Multiple threads：0>
                    <Multiple processes：1>
config.enParam    = NULL <To use the defaults：iformat(FMT_NV12),oformat(FMT_YUV420),quality(80),timeout(-1 nerver timeout),block_mode(0)>
                    JpegEncodeParam_t
                        quality: 1-100(best quality but largest size) (default: 80)
                        iformat: Input picture format(default: FMT_NV12)
                        oformat: Output picture format(default: FMT_YUV420)
                        timeout: timeout in seconds(default: -1 never timeout)
                        block_mode：always be 0
                        Note: better to use all default values except the quality value adjusted

jpegEnHandle = amlJpegEncodeInit(&config);

while (input YUV video frames) {
    //Refer to jpegenc.h for detail informations
    amlJpegEncodeProc();
}

amlJpegEncodeRelease(jpegEnHandle);
