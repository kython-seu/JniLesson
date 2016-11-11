LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_MODULE := jnilib
LOCAL_SRC_FILES := jniBase.c
include $(BUILD_SHARED_LIBRARY)