/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=. --out=. --include=/home/roto/git/android_frameworks_base/core/java --include=/home/roto/git/android_frameworks_base/graphics/java /home/roto/git/android_frameworks_base/core/java/android/accessibilityservice/IAccessibilityServiceConnection.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <android/accessibilityservice>
#include <android/binder_interface_utils.h>
#include <android/content/pm>
#include <android/graphics>
#include <android/hardware/usb>
#include <android/os>
#include <android/view>
#include <android/view/accessibility>
#include <android/window>
#include <aidl/android/accessibilityservice/IBrailleDisplayController.h>
#include <aidl/android/view/accessibility/IAccessibilityInteractionConnectionCallback.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::accessibilityservice {
class IBrailleDisplayController;
}  // namespace aidl::android::accessibilityservice
namespace aidl::android::view::accessibility {
class IAccessibilityInteractionConnectionCallback;
}  // namespace aidl::android::view::accessibility
namespace aidl {
namespace android {
namespace accessibilityservice {
class IAccessibilityServiceConnectionDelegator;

class IAccessibilityServiceConnection : public ::ndk::ICInterface {
public:
  typedef IAccessibilityServiceConnectionDelegator DefaultDelegator;
  static const char* descriptor;
  IAccessibilityServiceConnection();
  virtual ~IAccessibilityServiceConnection();

  static constexpr uint32_t TRANSACTION_setServiceInfo = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_setAttributionTag = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_findAccessibilityNodeInfoByAccessibilityId = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_findAccessibilityNodeInfosByText = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_findAccessibilityNodeInfosByViewId = FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_findFocus = FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_focusSearch = FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_performAccessibilityAction = FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_getWindow = FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_getWindows = FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_getServiceInfo = FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_performGlobalAction = FIRST_CALL_TRANSACTION + 11;
  static constexpr uint32_t TRANSACTION_getSystemActions = FIRST_CALL_TRANSACTION + 12;
  static constexpr uint32_t TRANSACTION_disableSelf = FIRST_CALL_TRANSACTION + 13;
  static constexpr uint32_t TRANSACTION_setOnKeyEventResult = FIRST_CALL_TRANSACTION + 14;
  static constexpr uint32_t TRANSACTION_getMagnificationConfig = FIRST_CALL_TRANSACTION + 15;
  static constexpr uint32_t TRANSACTION_getMagnificationScale = FIRST_CALL_TRANSACTION + 16;
  static constexpr uint32_t TRANSACTION_getMagnificationCenterX = FIRST_CALL_TRANSACTION + 17;
  static constexpr uint32_t TRANSACTION_getMagnificationCenterY = FIRST_CALL_TRANSACTION + 18;
  static constexpr uint32_t TRANSACTION_getMagnificationRegion = FIRST_CALL_TRANSACTION + 19;
  static constexpr uint32_t TRANSACTION_getCurrentMagnificationRegion = FIRST_CALL_TRANSACTION + 20;
  static constexpr uint32_t TRANSACTION_resetMagnification = FIRST_CALL_TRANSACTION + 21;
  static constexpr uint32_t TRANSACTION_resetCurrentMagnification = FIRST_CALL_TRANSACTION + 22;
  static constexpr uint32_t TRANSACTION_setMagnificationConfig = FIRST_CALL_TRANSACTION + 23;
  static constexpr uint32_t TRANSACTION_setMagnificationCallbackEnabled = FIRST_CALL_TRANSACTION + 24;
  static constexpr uint32_t TRANSACTION_setSoftKeyboardShowMode = FIRST_CALL_TRANSACTION + 25;
  static constexpr uint32_t TRANSACTION_getSoftKeyboardShowMode = FIRST_CALL_TRANSACTION + 26;
  static constexpr uint32_t TRANSACTION_setSoftKeyboardCallbackEnabled = FIRST_CALL_TRANSACTION + 27;
  static constexpr uint32_t TRANSACTION_switchToInputMethod = FIRST_CALL_TRANSACTION + 28;
  static constexpr uint32_t TRANSACTION_setInputMethodEnabled = FIRST_CALL_TRANSACTION + 29;
  static constexpr uint32_t TRANSACTION_isAccessibilityButtonAvailable = FIRST_CALL_TRANSACTION + 30;
  static constexpr uint32_t TRANSACTION_sendGesture = FIRST_CALL_TRANSACTION + 31;
  static constexpr uint32_t TRANSACTION_dispatchGesture = FIRST_CALL_TRANSACTION + 32;
  static constexpr uint32_t TRANSACTION_isFingerprintGestureDetectionAvailable = FIRST_CALL_TRANSACTION + 33;
  static constexpr uint32_t TRANSACTION_getOverlayWindowToken = FIRST_CALL_TRANSACTION + 34;
  static constexpr uint32_t TRANSACTION_getWindowIdForLeashToken = FIRST_CALL_TRANSACTION + 35;
  static constexpr uint32_t TRANSACTION_takeScreenshot = FIRST_CALL_TRANSACTION + 36;
  static constexpr uint32_t TRANSACTION_takeScreenshotOfWindow = FIRST_CALL_TRANSACTION + 37;
  static constexpr uint32_t TRANSACTION_setGestureDetectionPassthroughRegion = FIRST_CALL_TRANSACTION + 38;
  static constexpr uint32_t TRANSACTION_setTouchExplorationPassthroughRegion = FIRST_CALL_TRANSACTION + 39;
  static constexpr uint32_t TRANSACTION_setFocusAppearance = FIRST_CALL_TRANSACTION + 40;
  static constexpr uint32_t TRANSACTION_setCacheEnabled = FIRST_CALL_TRANSACTION + 41;
  static constexpr uint32_t TRANSACTION_logTrace = FIRST_CALL_TRANSACTION + 42;
  static constexpr uint32_t TRANSACTION_setServiceDetectsGesturesEnabled = FIRST_CALL_TRANSACTION + 43;
  static constexpr uint32_t TRANSACTION_requestTouchExploration = FIRST_CALL_TRANSACTION + 44;
  static constexpr uint32_t TRANSACTION_requestDragging = FIRST_CALL_TRANSACTION + 45;
  static constexpr uint32_t TRANSACTION_requestDelegating = FIRST_CALL_TRANSACTION + 46;
  static constexpr uint32_t TRANSACTION_onDoubleTap = FIRST_CALL_TRANSACTION + 47;
  static constexpr uint32_t TRANSACTION_onDoubleTapAndHold = FIRST_CALL_TRANSACTION + 48;
  static constexpr uint32_t TRANSACTION_setAnimationScale = FIRST_CALL_TRANSACTION + 49;
  static constexpr uint32_t TRANSACTION_setInstalledAndEnabledServices = FIRST_CALL_TRANSACTION + 50;
  static constexpr uint32_t TRANSACTION_getInstalledAndEnabledServices = FIRST_CALL_TRANSACTION + 51;
  static constexpr uint32_t TRANSACTION_attachAccessibilityOverlayToDisplay = FIRST_CALL_TRANSACTION + 52;
  static constexpr uint32_t TRANSACTION_attachAccessibilityOverlayToWindow = FIRST_CALL_TRANSACTION + 53;
  static constexpr uint32_t TRANSACTION_connectBluetoothBrailleDisplay = FIRST_CALL_TRANSACTION + 54;
  static constexpr uint32_t TRANSACTION_connectUsbBrailleDisplay = FIRST_CALL_TRANSACTION + 55;
  static constexpr uint32_t TRANSACTION_setTestBrailleDisplayData = FIRST_CALL_TRANSACTION + 56;

  static std::shared_ptr<IAccessibilityServiceConnection> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IAccessibilityServiceConnection>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IAccessibilityServiceConnection>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IAccessibilityServiceConnection>& impl);
  static const std::shared_ptr<IAccessibilityServiceConnection>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus setServiceInfo(const ::aidl::android::accessibilityservice::AccessibilityServiceInfo& in_info) = 0;
  virtual ::ndk::ScopedAStatus setAttributionTag(const std::string& in_attributionTag) = 0;
  virtual ::ndk::ScopedAStatus findAccessibilityNodeInfoByAccessibilityId(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int32_t in_flags, int64_t in_threadId, const ::aidl::android::os::Bundle& in_arguments, std::vector<std::string>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus findAccessibilityNodeInfosByText(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, const std::string& in_text, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, std::vector<std::string>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus findAccessibilityNodeInfosByViewId(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, const std::string& in_viewId, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, std::vector<std::string>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus findFocus(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, int32_t in_focusType, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, std::vector<std::string>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus focusSearch(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, int32_t in_direction, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, std::vector<std::string>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus performAccessibilityAction(int32_t in_accessibilityWindowId, int64_t in_accessibilityNodeId, int32_t in_action, const ::aidl::android::os::Bundle& in_arguments, int32_t in_interactionId, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback, int64_t in_threadId, bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getWindow(int32_t in_windowId, ::aidl::android::view::accessibility::AccessibilityWindowInfo* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getWindows(::aidl::android::view::accessibility::AccessibilityWindowInfo::AccessibilityWindowInfo.WindowListSparseArray* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getServiceInfo(::aidl::android::accessibilityservice::AccessibilityServiceInfo* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus performGlobalAction(int32_t in_action, bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getSystemActions(std::vector<::aidl::android::view::accessibility::AccessibilityNodeInfo::AccessibilityNodeInfo.AccessibilityAction>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus disableSelf() = 0;
  virtual ::ndk::ScopedAStatus setOnKeyEventResult(bool in_handled, int32_t in_sequence) = 0;
  virtual ::ndk::ScopedAStatus getMagnificationConfig(int32_t in_displayId, ::aidl::android::accessibilityservice::MagnificationConfig* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getMagnificationScale(int32_t in_displayId, float* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getMagnificationCenterX(int32_t in_displayId, float* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getMagnificationCenterY(int32_t in_displayId, float* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getMagnificationRegion(int32_t in_displayId, ::aidl::android::graphics::Region* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getCurrentMagnificationRegion(int32_t in_displayId, ::aidl::android::graphics::Region* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus resetMagnification(int32_t in_displayId, bool in_animate, bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus resetCurrentMagnification(int32_t in_displayId, bool in_animate, bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus setMagnificationConfig(int32_t in_displayId, const ::aidl::android::accessibilityservice::MagnificationConfig& in_config, bool in_animate, bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus setMagnificationCallbackEnabled(int32_t in_displayId, bool in_enabled) = 0;
  virtual ::ndk::ScopedAStatus setSoftKeyboardShowMode(int32_t in_showMode, bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getSoftKeyboardShowMode(int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus setSoftKeyboardCallbackEnabled(bool in_enabled) = 0;
  virtual ::ndk::ScopedAStatus switchToInputMethod(const std::string& in_imeId, bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus setInputMethodEnabled(const std::string& in_imeId, bool in_enabled, int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus isAccessibilityButtonAvailable(bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus sendGesture(int32_t in_sequence, const ::aidl::android::content::pm::ParceledListSlice& in_gestureSteps) = 0;
  virtual ::ndk::ScopedAStatus dispatchGesture(int32_t in_sequence, const ::aidl::android::content::pm::ParceledListSlice& in_gestureSteps, int32_t in_displayId) = 0;
  virtual ::ndk::ScopedAStatus isFingerprintGestureDetectionAvailable(bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getOverlayWindowToken(int32_t in_displayid, ::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getWindowIdForLeashToken(const ::ndk::SpAIBinder& in_token, int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus takeScreenshot(int32_t in_displayId, const ::aidl::android::os::RemoteCallback& in_callback) = 0;
  virtual ::ndk::ScopedAStatus takeScreenshotOfWindow(int32_t in_accessibilityWindowId, int32_t in_interactionId, const ::aidl::android::window::ScreenCapture::ScreenCapture.ScreenCaptureListener& in_listener, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback) = 0;
  virtual ::ndk::ScopedAStatus setGestureDetectionPassthroughRegion(int32_t in_displayId, const ::aidl::android::graphics::Region& in_region) = 0;
  virtual ::ndk::ScopedAStatus setTouchExplorationPassthroughRegion(int32_t in_displayId, const ::aidl::android::graphics::Region& in_region) = 0;
  virtual ::ndk::ScopedAStatus setFocusAppearance(int32_t in_strokeWidth, int32_t in_color) = 0;
  virtual ::ndk::ScopedAStatus setCacheEnabled(bool in_enabled) = 0;
  virtual ::ndk::ScopedAStatus logTrace(int64_t in_timestamp, const std::string& in_where, int64_t in_loggingTypes, const std::string& in_callingParams, int32_t in_processId, int64_t in_threadId, int32_t in_callingUid, const ::aidl::android::os::Bundle& in_serializedCallingStackInBundle) = 0;
  virtual ::ndk::ScopedAStatus setServiceDetectsGesturesEnabled(int32_t in_displayId, bool in_mode) = 0;
  virtual ::ndk::ScopedAStatus requestTouchExploration(int32_t in_displayId) = 0;
  virtual ::ndk::ScopedAStatus requestDragging(int32_t in_displayId, int32_t in_pointerId) = 0;
  virtual ::ndk::ScopedAStatus requestDelegating(int32_t in_displayId) = 0;
  virtual ::ndk::ScopedAStatus onDoubleTap(int32_t in_displayId) = 0;
  virtual ::ndk::ScopedAStatus onDoubleTapAndHold(int32_t in_displayId) = 0;
  virtual ::ndk::ScopedAStatus setAnimationScale(float in_scale) = 0;
  virtual ::ndk::ScopedAStatus setInstalledAndEnabledServices(const std::vector<::aidl::android::accessibilityservice::AccessibilityServiceInfo>& in_infos) = 0;
  virtual ::ndk::ScopedAStatus getInstalledAndEnabledServices(std::vector<::aidl::android::accessibilityservice::AccessibilityServiceInfo>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus attachAccessibilityOverlayToDisplay(int32_t in_interactionId, int32_t in_displayId, const ::aidl::android::view::SurfaceControl& in_sc, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback) = 0;
  virtual ::ndk::ScopedAStatus attachAccessibilityOverlayToWindow(int32_t in_interactionId, int32_t in_accessibilityWindowId, const ::aidl::android::view::SurfaceControl& in_sc, const std::shared_ptr<::aidl::android::view::accessibility::IAccessibilityInteractionConnectionCallback>& in_callback) = 0;
  virtual ::ndk::ScopedAStatus connectBluetoothBrailleDisplay(const std::string& in_bluetoothAddress, const std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayController>& in_controller) = 0;
  virtual ::ndk::ScopedAStatus connectUsbBrailleDisplay(const ::aidl::android::hardware::usb::UsbDevice& in_usbDevice, const std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayController>& in_controller) = 0;
  virtual ::ndk::ScopedAStatus setTestBrailleDisplayData(const std::vector<::aidl::android::os::Bundle>& in_brailleDisplays) = 0;
private:
  static std::shared_ptr<IAccessibilityServiceConnection> default_impl;
};
class IAccessibilityServiceConnectionDefault : public IAccessibilityServiceConnection {
public:
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
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
