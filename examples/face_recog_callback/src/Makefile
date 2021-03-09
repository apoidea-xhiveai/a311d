#
# All Rights Reserved
#
# APOIDEA CONFIDENTIAL
# Copyright 2019 Apoidea Technology All Rights Reserved.
# The source code contained or described herein and all documents related to
# the source code ("Material") are owned by Apoidea International Ltd or its
# suppliers or licensors. Title to the Material remains with Apoidea International Ltd
# or its suppliers and licensors. The Material contains trade secrets and
# proprietary and confidential information of Apoidea or its suppliers and
# licensors. The Material is protected by worldwide copyright and trade secret
# laws and treaty provisions. No part of the Material may be used, copied,
# reproduced, modified, published, uploaded, posted, transmitted, distributed,
# or disclosed in any way without Apoidea's prior express written permission.
#
# No license under any patent, copyright, trade secret or other intellectual
# property right is granted to or conferred upon you by disclosure or delivery
# of the Materials, either expressly, by implication, inducement, estoppel or
# otherwise. Any license under such intellectual property rights must be
# express and approved by Apoidea in writing.
#

## cd a311d/toolchains/gcc-linaro-6.3.1-2017.02-x86_64_aarch64-linux-gnu/bin
## pwd
## export PATH=$PATH:<pwd result path>
CC := aarch64-linux-gnu-gcc
MODULE := test_face_recog_callback

BIN_NAME := $(MODULE)

BIN_SRCS := main.c

LOCAL_CFLAGS := -Werror
LOCAL_CFLAGS += -Wno-unused-parameter -Wno-missing-field-initializers

LOCAL_LDFLAGS := -Wl,--hash-style=gnu -L../lib \
                 -lagilelog  -lamldec  -lbmdbclient  -lexpat  \
                 -lglib-2.0  -lgstreamer-1.0 -lMagFramework  -lxhiveai \
		         -lai_hal    -lasound  -ldfb_ui -lfdk-aac  -lgobject-2.0  \
		         -ljpegenc  -lspeexdsp -ldbus-1 -ldbus-glib-1 -ldirect-1.7 \
		         -ldirectfb-1.7 -lfusion-1.7 -lgmodule-2.0 \
		         -laml_ipc_sdk -lamlpic -lpcre -lgio-2.0 -lffi \
		         -lz -lfreetype -ljpeg -lpng16 -ldrm -lgbm -lGLESv2 \
		         -lgdc -lge2d -lion -lmount -luuid -lblkid

BIN_OBJS=$(patsubst %.c, %.o, $(BIN_SRCS))

.PHONY: all clean

all: $(BIN_NAME)

%.o: %.c
	@echo "[compiling.. $(notdir $<)]"
	$(CC) $(LOCAL_CFLAGS) -c -o $@ $<

$(BIN_NAME): $(BIN_OBJS)
	@echo "[creating.. $(notdir $@)]"
	$(CC) $(LOCAL_LDFLAGS) -o $@ $^

clean:
	@echo "[clean.. $(MODULE)]"
	rm -rf *.o $(BIN_NAME)
