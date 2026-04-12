LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libandroid_framework_core
LOCAL_CPP_EXTENSION := .cpp

# AIDL include paths
LOCAL_AIDL_INCLUDES := $(LOCAL_PATH)/../java

# Sources and AIDL files
LOCAL_SRC_FILES := \
    ../java/android/app/IActivityManager.aidl \
    ../java/android/app/IActivityTaskManager.aidl \
    ../java/android/app/IActivityClientController.aidl \
    ../java/android/app/IApplicationThread.aidl \
    ../java/android/app/IInstrumentationWatcher.aidl \
    ../java/android/app/IServiceConnection.aidl \
    ../java/android/app/ITaskStackListener.aidl \
    ../java/android/app/IUidObserver.aidl \
    ../java/android/hardware/display/IDisplayManager.aidl \
    ../java/android/hardware/input/IInputManager.aidl \
    ../java/android/view/IWindowSession.aidl \
    ../java/android/view/IWindowManager.aidl

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

# Enable C++23 (or latest supported by NDK) and safety flags
LOCAL_CPPFLAGS += -std=c++23 -Wall -Wextra -Werror -Wpedantic

LOCAL_SHARED_LIBRARIES := libbinder_ndk
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
