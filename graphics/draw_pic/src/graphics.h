#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

__BEGIN_DECLS

#ifndef GRAPH_IN
#define GRAPH_IN
#endif

#ifndef GRAPH_OUT
#define GRAPH_OUT
#endif

#ifndef GRAPH_INOUT
#define GRAPH_INOUT
#endif

typedef void* GRAPH_HANDLE_t;

typedef enum {
    GRAPHIC_FB,
    GRAPHIC_WAYLAND,
} GraphicType_t;

typedef enum {
    PIXEL_FMT_NV12,
    PIXEL_FMT_YUV420,
    PIXEL_FMT_RGB24,
    PIXEL_FMT_RGB32
} PixelFormat_t;

typedef struct _GraphSetting_t
{
    unsigned int width;       /*the width of the picture  [Must]*/
    unsigned int height;      /*the height of the picture [Must]*/
    PixelFormat_t format;     /*the format of the picture data [Must]*/

    GraphicType_t type;       /*the type of the graphic system*/
} GraphSetting_t;

GRAPH_HANDLE_t GraphInit(GRAPH_IN GraphSetting_t *config);

int GraphWrite(GRAPH_IN  GRAPH_HANDLE_t handle,
               GRAPH_IN  unsigned char *pic);

void GraphRelease(GRAPH_IN GRAPH_HANDLE_t *handle);

__END_DECLS

#endif /* __GRAPHICS_H_ */
