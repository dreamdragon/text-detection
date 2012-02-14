LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(OPENCV_PATH)/share/OpenCV/OpenCV.mk

LOCAL_MODULE    := run_detection
LOCAL_SRC_FILES := text_detect.cpp run_detection.cpp

include $(BUILD_SHARED_LIBRARY)
