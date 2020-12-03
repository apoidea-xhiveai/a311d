#include "graphics.h"

GRAPH_HANDLE_t hgraph;
GraphSetting_t graph_config;

graph_config.width  = <图片的宽度>;
graph_config.height = <图片的高度>;
graph_config.format = <PixelFormat_t>;
graph_config.type   = GRAPHIC_WAYLAND;

hgraph = GraphInit(&graph_config); //在开始画图前初始化

while (一帧一帧图片数据输入) {
    // pic: the buffer of the picture data
    if (GraphWrite(hgraph, pic) != 0) {
        printf("failed to write out picture to wayland!\n");
        sleep(5);
    }
}

GraphRelease(hgraph);  //所有图片处理完成后，释放graphics handler
