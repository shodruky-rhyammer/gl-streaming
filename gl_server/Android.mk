LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)  
LOCAL_LDLIBS := -lEGL -lGLESv2 -lpthread
LOCAL_SRC_FILES := fifo.c \
glcontrol.c \
glserver.c \
main.c \
server.c \
include $(BUILD_SHARED_LIBRARY)  
