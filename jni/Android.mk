LOCAL_PATH := $(call my-dir)
 
TESSERACT_PATH := $(LOCAL_PATH)/com_googlecode_tesseract_android/src
LEPTONICA_PATH := $(LOCAL_PATH)/com_googlecode_leptonica_android/src

include $(call all-subdir-makefiles) 

#include $(LEPTONICA_PATH)/../Android.mk
#include $(TESSERACT_PATH)/../Android.mk


include $(CLEAR_VARS)

OPENCV_CAMERA_MODULES := off 
include $(OPENCV_PACKAGE_DIR)/share/OpenCV/OpenCV.mk


LOCAL_MODULE    := run_detection
LOCAL_SRC_FILES := ../text_detect.cpp ../android.cpp
#LOCAL_SRC_FILES := ../android.cpp
LOCAL_LDLIBS    += -landroid
LOCAL_SHARED_LIBRARIES := liblept libtess

include $(BUILD_SHARED_LIBRARY)





