#
# All Rights Reserved
#
# APOIDEA CONFIDENTIAL
# Copyright 2017 Apoidea Technology All Rights Reserved.
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
CC := aarch64-linux-gnu-gcc

FLAGS = -Wl,--hash-style=gnu -ldrm
FLAGS += $(CFLAGS) -Werror -Wall -O0 -g
FLAGS += -D_FILE_OFFSET_BITS=64

all:
	$(CC) -o modeset modeset.c $(FLAGS)

clean:
	rm -rf *.o modeset
