REAL_LOCAL_PATH := $(call my-dir)
LOCAL_PATH :=
LEPTONICA_JNI_PATH := $(LOCAL_PATH)/com_googlecode_leptonica_android
include $(CLEAR_VARS)

LOCAL_MODULE := liblept

# leptonica (minus freetype)

BLACKLIST_SRC_FILES := \
  %endiantest.c \
  %freetype.c \
  %xtractprotos.c

LOCAL_SRC_FILES := \
  $(filter-out $(BLACKLIST_SRC_FILES),$(wildcard $(LEPTONICA_PATH)/src/*.c))

LOCAL_CFLAGS := \
  -DHAVE_CONFIG_H

LOCAL_C_INCLUDES := \
  $(LIBJPEG_PATH)

LOCAL_LDLIBS := \
  -lz

# missing stdio functions

ifneq ($(TARGET_SIMULATOR),true)
LOCAL_SRC_FILES += \
  $(LEPTONICA_JNI_PATH)/stdio/open_memstream.c \
  $(LEPTONICA_JNI_PATH)/stdio/fopencookie.c \
  $(LEPTONICA_JNI_PATH)/stdio/fmemopen.c
LOCAL_C_INCLUDES += \
  $(LEPTONICA_JNI_PATH)/stdio
endif

# jni

LOCAL_SRC_FILES += \
  $(LEPTONICA_JNI_PATH)/box.cpp \
  $(LEPTONICA_JNI_PATH)/pix.cpp \
  $(LEPTONICA_JNI_PATH)/pixa.cpp \
  $(LEPTONICA_JNI_PATH)/utilities.cpp \
  $(LEPTONICA_JNI_PATH)/readfile.cpp \
  $(LEPTONICA_JNI_PATH)/writefile.cpp \
  $(LEPTONICA_JNI_PATH)/jni.cpp
  
LOCAL_C_INCLUDES += \
  $(REAL_LOCAL_PATH) \
  ~/tesseract-android-tools/tesseract-android-tools/jni/com_googlecode_leptonica_android/ \
  $(LEPTONICA_PATH)/src \
  ~/tesseract-android-tools/tesseract-android-tools/external/leptonica-1.68/src/allheaders.h

LOCAL_LDLIBS += \
  -ljnigraphics \
  -llog

# common

LOCAL_SHARED_LIBRARIES:= libjpeg
LOCAL_PRELINK_MODULE:= false

include $(BUILD_SHARED_LIBRARY)
