# Android.mk for accessibilityservice module
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := accessibilityservice
LOCAL_LICENSE_KINDS := SPDX-license-identifier-Apache-2.0
LOCAL_LICENSE_CONDITIONS := notice
LOCAL_NOTICE_FILE := $(LOCAL_PATH)/../../../../NOTICE

# C++23 and Modules support (Note: ndk-build support for modules is toolchain dependent)
LOCAL_CPP_FEATURES := rtti exceptions modules
LOCAL_CPP_STD := c++23

# Module Interface and Partitions
LOCAL_SRC_FILES := \
    accessibilityservice.cppm \
    accessibilityservice-types.cppm \
    accessibilityservice-internal.cppm \
    accessibilityservice-button_controller.cppm \
    accessibilityservice-fingerprint_gesture_controller.cppm \
    accessibilityservice-touch_interaction_controller.cppm \
    accessibilityservice-magnification_controller.cppm \
    accessibilityservice-braille_display.cppm \
    accessibilityservice-input_method_session.cppm \
    accessibilityservice-input_method_session_wrapper.cppm \
    util/accessibilityservice-utils.cppm

# Implementation Files
LOCAL_SRC_FILES += \
    accessibilityservice.cpp \
    accessibilityservice-gesturedescription.cpp \
    accessibilityservice-input_method_session_wrapper.cpp

# Dependencies
LOCAL_SHARED_LIBRARIES := \
    libbinder_ndk \
    libutils \
    liblog

# External module dependencies
# Assumes ndk_executor is defined in its own Android.mk or accessible via include path
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../common

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

include $(BUILD_SHARED_LIBRARY)
