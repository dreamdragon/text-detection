LOCAL_PATH := $(call my-dir)

ifeq "$(TESSERACT_PATH)" ""
  $(error You must set the TESSERACT_PATH variable to the Tesseract source directory.)
endif

ifeq "$(LEPTONICA_PATH)" ""
  $(error You must set the LEPTONICA_PATH variable to the Leptonica source directory.)
endif

include $(CLEAR_VARS)

include $(OPENCV_PACKAGE_DIR)/share/OpenCV/OpenCV.mk
include $(LOCAL_PATH)/com_googlecode_tesseract_android/Android.mk

LOCAL_MODULE    := run_detection
LOCAL_SRC_FILES := text_detect.cpp run_detection.cpp


include $(BUILD_SHARED_LIBRARY)  