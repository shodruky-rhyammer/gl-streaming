LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)  
LOCAL_MODULE := libglserver
LOCAL_LDLIBS := -lEGL -lGLESv2 -llog
# -lpthread
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_SRC_FILES := fifo.c \
				   glcontrol.c \
				   glserver.c \
				   main.c \
				   server.c \
include $(BUILD_SHARED_LIBRARY)  
