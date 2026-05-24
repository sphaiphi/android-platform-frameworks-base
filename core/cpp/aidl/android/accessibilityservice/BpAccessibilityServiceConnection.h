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

namespace aidl {
namespace android {
namespace accessibilityservice {
class BpAccessibilityServiceConnection : public ::ndk::BpCInterface<IAccessibilityServiceConnection> {
public:
  explicit BpAccessibilityServiceConnection(const ::ndk::SpAIBinder& binder);
  virtual ~BpAccessibilityServiceConnection();

  ::ndk::ScopedAStatus setServiceInfo(const ::aidl::android::accessibilityservice::AccessibilityServiceInfo& in_info) override;
  ::ndk::ScopedAStatus setAttributionTag(const std::string& in_attributionTag) override;
  ::ndk::ScopedAStatus findAccessibilityNodeInfoByAccessibilityId(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int32_t in_flags, int64_t in_threadId, const ::aidl::android::os::Bundle& in_arguments, std::vector<std::string>* _aidl_return) override;
  ::ndk::ScopedAStatus findAccessibilityNodeInfosByText(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, const std::string& in_text, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, std::vector<std::string>* _aidl_return) override;
  ::ndk::ScopedAStatus findAccessibilityNodeInfosByViewId(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, const std::string& in_viewId, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, std::vector<std::string>* _aidl_return) override;
  ::ndk::ScopedAStatus findFocus(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, int32_t in_focusType, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, std::vector<std::string>* _aidl_return) override;
  ::ndk::ScopedAStatus focusSearch(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, int32_t in_direction, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, std::vector<std::string>* _aidl_return) override;
  ::ndk::ScopedAStatus performAccessibilityAction(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, int32_t in_action, const ::aidl::android::os::Bundle& in_arguments, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, bool* _aidl_return) override;
  ::ndk::ScopedAStatus getWindow(int32_t in_windowId, ::aidl::android::view::accessibility::AccessibilityWindowInfo* _aidl_return) override;
  ::ndk::ScopedAStatus getWindows(::aidl::android::view::accessibility::AccessibilityWindowInfo::AccessibilityWindowInfo.WindowListSparseArray* _aidl_return) override;
  ::ndk::ScopedAStatus getServiceInfo(::aidl::android::accessibilityservice::AccessibilityServiceInfo* _aidl_return) override;
  ::ndk::ScopedAStatus performGlobalAction(int32_t in_action, bool* _aidl_return) override;
  ::ndk::ScopedAStatus getSystemActions(std::vector<::aidl::android::view::accessibility::AccessibilityNodeInfo::AccessibilityNodeInfo.AccessibilityAction>* _aidl_return) override;
  ::ndk::ScopedAStatus disableSelf() override;
  ::ndk::ScopedAStatus setOnKeyEventResult(bool in_handled, int32_t in_sequence) override;
  ::ndk::ScopedAStatus getMagnificationConfig(int32_t in_displayId, ::aidl::android::accessibilityservice::MagnificationConfig* _aidl_return) override;
  ::ndk::ScopedAStatus getMagnificationScale(int32_t in_displayId, float* _aidl_return) override;
  ::ndk::ScopedAStatus getMagnificationCenterX(int32_t in_displayId, float* _aidl_return) override;
  ::ndk::ScopedAStatus getMagnificationCenterY(int32_t in_displayId, float* _aidl_return) override;
  ::ndk::ScopedAStatus getMagnificationRegion(int32_t in_displayId, ::aidl::android::graphics::Region* _aidl_return) override;
  ::ndk::ScopedAStatus getCurrentMagnificationRegion(int32_t in_displayId, ::aidl::android::graphics::Region* _aidl_return) override;
  ::ndk::ScopedAStatus resetMagnification(int32_t in_displayId, bool in_animate, bool* _aidl_return) override;
  ::ndk::ScopedAStatus resetCurrentMagnification(int32_t in_displayId, bool in_animate, bool* _aidl_return) override;
  ::ndk::ScopedAStatus setMagnificationConfig(int32_t in_displayId, const ::aidl::android::accessibilityservice::MagnificationConfig& in_config, bool in_animate, bool* _aidl_return) override;
  ::ndk::ScopedAStatus setMagnificationCallbackEnabled(int32_t in_displayId, bool in_enabled) override;
  ::ndk::ScopedAStatus setSoftKeyboardShowMode(int32_t in_showMode, bool* _aidl_return) override;
  ::ndk::ScopedAStatus getSoftKeyboardShowMode(int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus setSoftKeyboardCallbackEnabled(bool in_enabled) override;
  ::ndk::ScopedAStatus switchToInputMethod(const std::string& in_imeId, bool* _aidl_return) override;
  ::ndk::ScopedAStatus setInputMethodEnabled(const std::string& in_imeId, bool in_enabled, int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus isAccessibilityButtonAvailable(bool* _aidl_return) override;
  ::ndk::ScopedAStatus sendGesture(int32_t in_sequence, const ::aidl::android::content::pm::ParceledListSlice& in_gestureSteps) override;
  ::ndk::ScopedAStatus dispatchGesture(int32_t in_sequence, const ::aidl::android::content::pm::ParceledListSlice& in_gestureSteps, int32_t in_displayId) override;
  ::ndk::ScopedAStatus isFingerprintGestureDetectionAvailable(bool* _aidl_return) override;
  ::ndk::ScopedAStatus getOverlayWindowToken(int32_t in_displayid, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus getWindowIdForLeashToken(const ::ndk::SpAIBinder& in_token, int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus takeScreenshot(int32_t in_displayId, const ::aidl::android::os::RemoteCallback& in_callback) override;
  ::ndk::ScopedAStatus takeScreenshotOfWindow(int32_t in_accessibilityWindowId, int32_t in_interactionId, const ::aidl::android::window::ScreenCapture::ScreenCapture.ScreenCaptureListener& in_listener, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback) override;
  ::ndk::ScopedAStatus setGestureDetectionPassthroughRegion(int32_t in_displayId, const ::aidl::android::graphics::Region& in_region) override;
  ::ndk::ScopedAStatus setTouchExplorationPassthroughRegion(int32_t in_displayId, const ::aidl::android::graphics::Region& in_region) override;
  ::ndk::ScopedAStatus setFocusAppearance(int32_t in_strokeWidth, int32_t in_color) override;
  ::ndk::ScopedAStatus setCacheEnabled(bool in_enabled) override;
  ::ndk::ScopedAStatus logTrace(int64_t in_timestamp, const std::string& in_where, int64_t in_loggingTypes, const std::string& in_callingParams, int32_t in_processId, int64_t in_threadId, int32_t in_callingUid, const ::aidl::android::os::Bundle& in_serializedCallingStackInBundle) override;
  ::ndk::ScopedAStatus setServiceDetectsGesturesEnabled(int32_t in_displayId, bool in_mode) override;
  ::ndk::ScopedAStatus requestTouchExploration(int32_t in_displayId) override;
  ::ndk::ScopedAStatus requestDragging(int32_t in_displayId, int32_t in_pointerId) override;
  ::ndk::ScopedAStatus requestDelegating(int32_t in_displayId) override;
  ::ndk::ScopedAStatus onDoubleTap(int32_t in_displayId) override;
  ::ndk::ScopedAStatus onDoubleTapAndHold(int32_t in_displayId) override;
  ::ndk::ScopedAStatus setAnimationScale(float in_scale) override;
  ::ndk::ScopedAStatus setInstalledAndEnabledServices(const std::vector<::aidl::android::accessibilityservice::AccessibilityServiceInfo>& in_infos) override;
  ::ndk::ScopedAStatus getInstalledAndEnabledServices(std::vector<::aidl::android::accessibilityservice::AccessibilityServiceInfo>* _aidl_return) override;
  ::ndk::ScopedAStatus attachAccessibilityOverlayToDisplay(int32_t in_interactionId, int32_t in_displayId, const ::aidl::android::view::SurfaceControl& in_sc, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback) override;
  ::ndk::ScopedAStatus attachAccessibilityOverlayToWindow(int32_t in_interactionId, int32_t in_accessibilityWindowId, const ::aidl::android::view::SurfaceControl& in_sc, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback) override;
  ::ndk::ScopedAStatus connectBluetoothBrailleDisplay(const std::string& in_bluetoothAddress, const std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayController>& in_controller) override;
  ::ndk::ScopedAStatus connectUsbBrailleDisplay(const ::aidl::android::hardware::usb::UsbDevice& in_usbDevice, const std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayController>& in_controller) override;
  ::ndk::ScopedAStatus setTestBrailleDisplayData(const std::vector<::aidl::android::os::Bundle>& in_brailleDisplays) override;
};
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
