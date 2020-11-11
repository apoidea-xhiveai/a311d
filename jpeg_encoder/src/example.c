#include "jpegenc.h"

JPEGEN_HANDLE_t jpegEnHandle;

JpegEnSetting_t config;

config.width      = <输入YUV图片的宽度>
config.height     = <输入YUV图片的高度>
config.channel_id = <对于多路jpeg encoder的应用，输入该路的index作为标识>
config.scale      = <如果有对YUV图片resize的需要，输入resize的比例。例如 scale=2， 那么resize之后的宽和高均为原始图片的1/2>
                    <如果不需要resize，设置为0>
config.multi_proc = <因为Soc中只有一个硬件jpeg encoder，如果有多路jpeg encoder的需求时，需要设置这个参数，来保证同步访问时候的数据保护>
                    <如果是一个进程内的多线程应用来实现， 那么设置为：0>
                    <如果是多个进程的应用来实现， 那么设置为：1>
config.enParam    = NULL <使用默认值：iformat(FMT_NV12),oformat(FMT_YUV420),quality(25),timeout(-1 nerver timeout),block_mode(0)>
                    自定义结构 JpegEncodeParam_t
                                quality: 数字越大质量越高 (default: 25)
                                iformat: 输入图片的格式(default: FMT_NV12)
                                oformat: 输出图片的格式(default: FMT_YUV420)
                                timeout: 编码是否等待超时(default: -1 永远不超时)
                                block_mode：块编码模式(default: 0)
                                除qulity可以根据需要调整外，其他参数最好使用默认值。

jpegEnHandle = amlJpegEncodeInit(&config); //在开始编码前初始化

while (一帧一帧图片数据输入) {
    //参照jpegenc.h的注释来调用处理函数
    amlJpegEncodeProc();    OR
    amlJpegEncodeBothProc();
}

amlJpegEncodeRelease(jpegEnHandle);  //所有图片处理完成后，释放jpeg encoder
