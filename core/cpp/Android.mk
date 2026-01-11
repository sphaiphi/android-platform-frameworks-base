LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libandroid_framework_core
LOCAL_CPP_EXTENSION := .cpp

# Sources will be added here
LOCAL_SRC_FILES := 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

# Enable C++23 (or latest supported by NDK) and safety flags
LOCAL_CPPFLAGS += -std=c++23 -Wall -Wextra -Werror -Wpedantic

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
