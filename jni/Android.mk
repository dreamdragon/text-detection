LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OPENCV_CAMERA_MODULES := off
include $(OPENCV_PACKAGE_DIR)/share/OpenCV/OpenCV.mk

LOCAL_MODULE    := run_detection
LOCAL_SRC_FILES := text_detect.cpp android.cpp
LOCAL_LDLIBS    += -landroid -llog -ldl

include $(BUILD_SHARED_LIBRARY)





