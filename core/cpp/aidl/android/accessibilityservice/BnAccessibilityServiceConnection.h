/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=. --out=. --include=/home/roto/git/android_frameworks_base/core/java --include=/home/roto/git/android_frameworks_base/graphics/java /home/roto/git/android_frameworks_base/core/java/android/accessibilityservice/IAccessibilityServiceConnection.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/accessibilityservice/IAccessibilityServiceConnection.h"

#include <android/binder_ibinder.h>
#include <cassert>

#ifndef __BIONIC__
#ifndef __assert2
#define __assert2(a,b,c,d) ((void)0)
#endif
#endif

namespace aidl {
namespace android {
namespace accessibilityservice {
class BnAccessibilityServiceConnection : public ::ndk::BnCInterface<IAccessibilityServiceConnection> {
public:
  BnAccessibilityServiceConnection();
  virtual ~BnAccessibilityServiceConnection();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IAccessibilityServiceConnectionDelegator : public BnAccessibilityServiceConnection {
public:
  explicit IAccessibilityServiceConnectionDelegator(const std::shared_ptr<IAccessibilityServiceConnection> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus setServiceInfo(const ::aidl::android::accessibilityservice::AccessibilityServiceInfo& in_info) override {
    return _impl->setServiceInfo(in_info);
  }
  ::ndk::ScopedAStatus setAttributionTag(const std::string& in_attributionTag) override {
    return _impl->setAttributionTag(in_attributionTag);
  }
  ::ndk::ScopedAStatus findAccessibilityNodeInfoByAccessibilityId(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int32_t in_flags, int64_t in_threadId, const ::aidl::android::os::Bundle& in_arguments, std::vector<std::string>* _aidl_return) override {
    return _impl->findAccessibilityNodeInfoByAccessibilityId(in_accessibilityWindowId, in_accessibilityNodeId, in_interactionId, in_callback, in_flags, in_threadId, in_arguments, _aidl_return);
  }
  ::ndk::ScopedAStatus findAccessibilityNodeInfosByText(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, const std::string& in_text, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, std::vector<std::string>* _aidl_return) override {
    return _impl->findAccessibilityNodeInfosByText(in_accessibilityWindowId, in_accessibilityNodeId, in_text, in_interactionId, in_callback, in_threadId, _aidl_return);
  }
  ::ndk::ScopedAStatus findAccessibilityNodeInfosByViewId(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, const std::string& in_viewId, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, std::vector<std::string>* _aidl_return) override {
    return _impl->findAccessibilityNodeInfosByViewId(in_accessibilityWindowId, in_accessibilityNodeId, in_viewId, in_interactionId, in_callback, in_threadId, _aidl_return);
  }
  ::ndk::ScopedAStatus findFocus(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, int32_t in_focusType, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, std::vector<std::string>* _aidl_return) override {
    return _impl->findFocus(in_accessibilityWindowId, in_accessibilityNodeId, in_focusType, in_interactionId, in_callback, in_threadId, _aidl_return);
  }
  ::ndk::ScopedAStatus focusSearch(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, int32_t in_direction, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, std::vector<std::string>* _aidl_return) override {
    return _impl->focusSearch(in_accessibilityWindowId, in_accessibilityNodeId, in_direction, in_interactionId, in_callback, in_threadId, _aidl_return);
  }
  ::ndk::ScopedAStatus performAccessibilityAction(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, int32_t in_action, const ::aidl::android::os::Bundle& in_arguments, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, bool* _aidl_return) override {
    return _impl->performAccessibilityAction(in_accessibilityWindowId, in_accessibilityNodeId, in_action, in_arguments, in_interactionId, in_callback, in_threadId, _aidl_return);
  }
  ::ndk::ScopedAStatus getWindow(int32_t in_windowId, ::aidl::android::view::accessibility::AccessibilityWindowInfo* _aidl_return) override {
    return _impl->getWindow(in_windowId, _aidl_return);
  }
  ::ndk::ScopedAStatus getWindows(::aidl::android::view::accessibility::AccessibilityWindowInfo::AccessibilityWindowInfo.WindowListSparseArray* _aidl_return) override {
    return _impl->getWindows(_aidl_return);
  }
  ::ndk::ScopedAStatus getServiceInfo(::aidl::android::accessibilityservice::AccessibilityServiceInfo* _aidl_return) override {
    return _impl->getServiceInfo(_aidl_return);
  }
  ::ndk::ScopedAStatus performGlobalAction(int32_t in_action, bool* _aidl_return) override {
    return _impl->performGlobalAction(in_action, _aidl_return);
  }
  ::ndk::ScopedAStatus getSystemActions(std::vector<::aidl::android::view::accessibility::AccessibilityNodeInfo::AccessibilityNodeInfo.AccessibilityAction>* _aidl_return) override {
    return _impl->getSystemActions(_aidl_return);
  }
  ::ndk::ScopedAStatus disableSelf() override {
    return _impl->disableSelf();
  }
  ::ndk::ScopedAStatus setOnKeyEventResult(bool in_handled, int32_t in_sequence) override {
    return _impl->setOnKeyEventResult(in_handled, in_sequence);
  }
  ::ndk::ScopedAStatus getMagnificationConfig(int32_t in_displayId, ::aidl::android::accessibilityservice::MagnificationConfig* _aidl_return) override {
    return _impl->getMagnificationConfig(in_displayId, _aidl_return);
  }
  ::ndk::ScopedAStatus getMagnificationScale(int32_t in_displayId, float* _aidl_return) override {
    return _impl->getMagnificationScale(in_displayId, _aidl_return);
  }
  ::ndk::ScopedAStatus getMagnificationCenterX(int32_t in_displayId, float* _aidl_return) override {
    return _impl->getMagnificationCenterX(in_displayId, _aidl_return);
  }
  ::ndk::ScopedAStatus getMagnificationCenterY(int32_t in_displayId, float* _aidl_return) override {
    return _impl->getMagnificationCenterY(in_displayId, _aidl_return);
  }
  ::ndk::ScopedAStatus getMagnificationRegion(int32_t in_displayId, ::aidl::android::graphics::Region* _aidl_return) override {
    return _impl->getMagnificationRegion(in_displayId, _aidl_return);
  }
  ::ndk::ScopedAStatus getCurrentMagnificationRegion(int32_t in_displayId, ::aidl::android::graphics::Region* _aidl_return) override {
    return _impl->getCurrentMagnificationRegion(in_displayId, _aidl_return);
  }
  ::ndk::ScopedAStatus resetMagnification(int32_t in_displayId, bool in_animate, bool* _aidl_return) override {
    return _impl->resetMagnification(in_displayId, in_animate, _aidl_return);
  }
  ::ndk::ScopedAStatus resetCurrentMagnification(int32_t in_displayId, bool in_animate, bool* _aidl_return) override {
    return _impl->resetCurrentMagnification(in_displayId, in_animate, _aidl_return);
  }
  ::ndk::ScopedAStatus setMagnificationConfig(int32_t in_displayId, const ::aidl::android::accessibilityservice::MagnificationConfig& in_config, bool in_animate, bool* _aidl_return) override {
    return _impl->setMagnificationConfig(in_displayId, in_config, in_animate, _aidl_return);
  }
  ::ndk::ScopedAStatus setMagnificationCallbackEnabled(int32_t in_displayId, bool in_enabled) override {
    return _impl->setMagnificationCallbackEnabled(in_displayId, in_enabled);
  }
  ::ndk::ScopedAStatus setSoftKeyboardShowMode(int32_t in_showMode, bool* _aidl_return) override {
    return _impl->setSoftKeyboardShowMode(in_showMode, _aidl_return);
  }
  ::ndk::ScopedAStatus getSoftKeyboardShowMode(int32_t* _aidl_return) override {
    return _impl->getSoftKeyboardShowMode(_aidl_return);
  }
  ::ndk::ScopedAStatus setSoftKeyboardCallbackEnabled(bool in_enabled) override {
    return _impl->setSoftKeyboardCallbackEnabled(in_enabled);
  }
  ::ndk::ScopedAStatus switchToInputMethod(const std::string& in_imeId, bool* _aidl_return) override {
    return _impl->switchToInputMethod(in_imeId, _aidl_return);
  }
  ::ndk::ScopedAStatus setInputMethodEnabled(const std::string& in_imeId, bool in_enabled, int32_t* _aidl_return) override {
    return _impl->setInputMethodEnabled(in_imeId, in_enabled, _aidl_return);
  }
  ::ndk::ScopedAStatus isAccessibilityButtonAvailable(bool* _aidl_return) override {
    return _impl->isAccessibilityButtonAvailable(_aidl_return);
  }
  ::ndk::ScopedAStatus sendGesture(int32_t in_sequence, const ::aidl::android::content::pm::ParceledListSlice& in_gestureSteps) override {
    return _impl->sendGesture(in_sequence, in_gestureSteps);
  }
  ::ndk::ScopedAStatus dispatchGesture(int32_t in_sequence, const ::aidl::android::content::pm::ParceledListSlice& in_gestureSteps, int32_t in_displayId) override {
    return _impl->dispatchGesture(in_sequence, in_gestureSteps, in_displayId);
  }
  ::ndk::ScopedAStatus isFingerprintGestureDetectionAvailable(bool* _aidl_return) override {
    return _impl->isFingerprintGestureDetectionAvailable(_aidl_return);
  }
  ::ndk::ScopedAStatus getOverlayWindowToken(int32_t in_displayid, ::ndk::SpAIBinder* _aidl_return) override {
    return _impl->getOverlayWindowToken(in_displayid, _aidl_return);
  }
  ::ndk::ScopedAStatus getWindowIdForLeashToken(const ::ndk::SpAIBinder& in_token, int32_t* _aidl_return) override {
    return _impl->getWindowIdForLeashToken(in_token, _aidl_return);
  }
  ::ndk::ScopedAStatus takeScreenshot(int32_t in_displayId, const ::aidl::android::os::RemoteCallback& in_callback) override {
    return _impl->takeScreenshot(in_displayId, in_callback);
  }
  ::ndk::ScopedAStatus takeScreenshotOfWindow(int32_t in_accessibilityWindowId, int32_t in_interactionId, const ::aidl::android::window::ScreenCapture::ScreenCapture.ScreenCaptureListener& in_listener, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback) override {
    return _impl->takeScreenshotOfWindow(in_accessibilityWindowId, in_interactionId, in_listener, in_callback);
  }
  ::ndk::ScopedAStatus setGestureDetectionPassthroughRegion(int32_t in_displayId, const ::aidl::android::graphics::Region& in_region) override {
    return _impl->setGestureDetectionPassthroughRegion(in_displayId, in_region);
  }
  ::ndk::ScopedAStatus setTouchExplorationPassthroughRegion(int32_t in_displayId, const ::aidl::android::graphics::Region& in_region) override {
    return _impl->setTouchExplorationPassthroughRegion(in_displayId, in_region);
  }
  ::ndk::ScopedAStatus setFocusAppearance(int32_t in_strokeWidth, int32_t in_color) override {
    return _impl->setFocusAppearance(in_strokeWidth, in_color);
  }
  ::ndk::ScopedAStatus setCacheEnabled(bool in_enabled) override {
    return _impl->setCacheEnabled(in_enabled);
  }
  ::ndk::ScopedAStatus logTrace(int64_t in_timestamp, const std::string& in_where, int64_t in_loggingTypes, const std::string& in_callingParams, int32_t in_processId, int64_t in_threadId, int32_t in_callingUid, const ::aidl::android::os::Bundle& in_serializedCallingStackInBundle) override {
    return _impl->logTrace(in_timestamp, in_where, in_loggingTypes, in_callingParams, in_processId, in_threadId, in_callingUid, in_serializedCallingStackInBundle);
  }
  ::ndk::ScopedAStatus setServiceDetectsGesturesEnabled(int32_t in_displayId, bool in_mode) override {
    return _impl->setServiceDetectsGesturesEnabled(in_displayId, in_mode);
  }
  ::ndk::ScopedAStatus requestTouchExploration(int32_t in_displayId) override {
    return _impl->requestTouchExploration(in_displayId);
  }
  ::ndk::ScopedAStatus requestDragging(int32_t in_displayId, int32_t in_pointerId) override {
    return _impl->requestDragging(in_displayId, in_pointerId);
  }
  ::ndk::ScopedAStatus requestDelegating(int32_t in_displayId) override {
    return _impl->requestDelegating(in_displayId);
  }
  ::ndk::ScopedAStatus onDoubleTap(int32_t in_displayId) override {
    return _impl->onDoubleTap(in_displayId);
  }
  ::ndk::ScopedAStatus onDoubleTapAndHold(int32_t in_displayId) override {
    return _impl->onDoubleTapAndHold(in_displayId);
  }
  ::ndk::ScopedAStatus setAnimationScale(float in_scale) override {
    return _impl->setAnimationScale(in_scale);
  }
  ::ndk::ScopedAStatus setInstalledAndEnabledServices(const std::vector<::aidl::android::accessibilityservice::AccessibilityServiceInfo>& in_infos) override {
    return _impl->setInstalledAndEnabledServices(in_infos);
  }
  ::ndk::ScopedAStatus getInstalledAndEnabledServices(std::vector<::aidl::android::accessibilityservice::AccessibilityServiceInfo>* _aidl_return) override {
    return _impl->getInstalledAndEnabledServices(_aidl_return);
  }
  ::ndk::ScopedAStatus attachAccessibilityOverlayToDisplay(int32_t in_interactionId, int32_t in_displayId, const ::aidl::android::view::SurfaceControl& in_sc, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback) override {
    return _impl->attachAccessibilityOverlayToDisplay(in_interactionId, in_displayId, in_sc, in_callback);
  }
  ::ndk::ScopedAStatus attachAccessibilityOverlayToWindow(int32_t in_interactionId, int32_t in_accessibilityWindowId, const ::aidl::android::view::SurfaceControl& in_sc, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback) override {
    return _impl->attachAccessibilityOverlayToWindow(in_interactionId, in_accessibilityWindowId, in_sc, in_callback);
  }
  ::ndk::ScopedAStatus connectBluetoothBrailleDisplay(const std::string& in_bluetoothAddress, const std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayController>& in_controller) override {
    return _impl->connectBluetoothBrailleDisplay(in_bluetoothAddress, in_controller);
  }
  ::ndk::ScopedAStatus connectUsbBrailleDisplay(const ::aidl::android::hardware::usb::UsbDevice& in_usbDevice, const std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayController>& in_controller) override {
    return _impl->connectUsbBrailleDisplay(in_usbDevice, in_controller);
  }
  ::ndk::ScopedAStatus setTestBrailleDisplayData(const std::vector<::aidl::android::os::Bundle>& in_brailleDisplays) override {
    return _impl->setTestBrailleDisplayData(in_brailleDisplays);
  }
protected:
private:
  std::shared_ptr<IAccessibilityServiceConnection> _impl;
};

}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
