Here is the detailed parameter description.
./test_h264encode  srcfile  outfile  width  height  gop  framerate  bitrate  num  fmt

Parameter	Description
srcfile	        source yuv data url
outfile	        encoded h264 stream url 
width	        source yuv width
height	        source yuv height
gop	        I frame refresh interval(N=0: only one I frame; N>0: one I frame per N frames)
framerate	framerate(fps)
bitrate	        bitrate(bps)
num	        encode frame count
fmt	        source yuv format( 0:nv12 1:nv21 2:yv12 3:rgb888 4:bgr888 )
