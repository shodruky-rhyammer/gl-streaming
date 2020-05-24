LOCAL_PATH := $(call my-dir)
HERE_PATH := $(LOCAL_PATH)

include $(LOCAL_PATH)/../../gl_server/Android.mk

LOCAL_PATH := $(HERE_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE    := glstreamserver
LOCAL_LDLIBS    := -lEGL -lGLESv2 -llog -landroid
LOCAL_SRC_FILES := glstreaming_jni.cpp
LOCAL_STATIC_LIBRARIES := libgl_server
ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_CFLAGS += -ffast-math -mtune=atom -mssse3 -mfpmath=sse
endif
include $(BUILD_SHARED_LIBRARY)

