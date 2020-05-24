LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := gl_server
LOCAL_SRC_FILES := ../common/fifo.c   \
				   ../common/server.c \
				   glcontrol.c        \
				   glserver.c         \
				   main.c
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/../common
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)
# Move to define in C code.
# LOCAL_CFLAGS += -DGL_SERVER
ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_CFLAGS += -ffast-math -mtune=atom -mssse3 -mfpmath=sse
endif
include $(BUILD_STATIC_LIBRARY)

