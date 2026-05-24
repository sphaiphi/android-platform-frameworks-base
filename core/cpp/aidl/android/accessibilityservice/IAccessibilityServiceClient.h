/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=. --out=. --include=/home/roto/git/android_frameworks_base/core/java --include=/home/roto/git/android_frameworks_base/graphics/java /home/roto/git/android_frameworks_base/core/java/android/accessibilityservice/IAccessibilityServiceClient.aidl
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
#include <android/accessibility>
#include <android/accessibilityservice>
#include <android/accessibilityservice/AccessibilityGestureEvent.h>
#include <android/binder_interface_utils.h>
#include <android/graphics>
#include <android/view>
#include <android/view/inputmethod>
#include <aidl/android/accessibilityservice/IAccessibilityServiceConnection.h>
#include <aidl/com/android/internal/inputmethod/IAccessibilityInputMethodSession.h>
#include <aidl/com/android/internal/inputmethod/IAccessibilityInputMethodSessionCallback.h>
#include <aidl/com/android/internal/inputmethod/IRemoteAccessibilityInputConnection.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::accessibilityservice {
class IAccessibilityServiceConnection;
}  // namespace aidl::android::accessibilityservice
namespace aidl::com::android::internal::inputmethod {
class IAccessibilityInputMethodSession;
class IAccessibilityInputMethodSessionCallback;
class IRemoteAccessibilityInputConnection;
}  // namespace aidl::com::android::internal::inputmethod
namespace aidl {
namespace android {
namespace accessibilityservice {
class IAccessibilityServiceClientDelegator;

class IAccessibilityServiceClient : public ::ndk::ICInterface {
public:
  typedef IAccessibilityServiceClientDelegator DefaultDelegator;
  static const char* descriptor;
  IAccessibilityServiceClient();
  virtual ~IAccessibilityServiceClient();

  static constexpr uint32_t TRANSACTION_init = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onAccessibilityEvent = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onInterrupt = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onGesture = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_clearAccessibilityCache = FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_onKeyEvent = FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_onMagnificationChanged = FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_onMotionEvent = FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_onTouchStateChanged = FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_onSoftKeyboardShowModeChanged = FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_onPerformGestureResult = FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_onFingerprintCapturingGesturesChanged = FIRST_CALL_TRANSACTION + 11;
  static constexpr uint32_t TRANSACTION_onFingerprintGesture = FIRST_CALL_TRANSACTION + 12;
  static constexpr uint32_t TRANSACTION_onAccessibilityButtonClicked = FIRST_CALL_TRANSACTION + 13;
  static constexpr uint32_t TRANSACTION_onAccessibilityButtonAvailabilityChanged = FIRST_CALL_TRANSACTION + 14;
  static constexpr uint32_t TRANSACTION_onSystemActionsChanged = FIRST_CALL_TRANSACTION + 15;
  static constexpr uint32_t TRANSACTION_createImeSession = FIRST_CALL_TRANSACTION + 16;
  static constexpr uint32_t TRANSACTION_setImeSessionEnabled = FIRST_CALL_TRANSACTION + 17;
  static constexpr uint32_t TRANSACTION_bindInput = FIRST_CALL_TRANSACTION + 18;
  static constexpr uint32_t TRANSACTION_unbindInput = FIRST_CALL_TRANSACTION + 19;
  static constexpr uint32_t TRANSACTION_startInput = FIRST_CALL_TRANSACTION + 20;

  static std::shared_ptr<IAccessibilityServiceClient> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IAccessibilityServiceClient>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IAccessibilityServiceClient>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IAccessibilityServiceClient>& impl);
  static const std::shared_ptr<IAccessibilityServiceClient>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus init(const std::shared_ptr<::aidl::android::accessibilityservice::IAccessibilityServiceConnection>& in_connection, int32_t in_connectionId, const ::ndk::SpAIBinder& in_windowToken) = 0;
  virtual ::ndk::ScopedAStatus onAccessibilityEvent(const ::aidl::android::view::accessibility::AccessibilityEvent& in_event, bool in_serviceWantsEvent) = 0;
  virtual ::ndk::ScopedAStatus onInterrupt() = 0;
  virtual ::ndk::ScopedAStatus onGesture(const ::aidl::android::accessibilityservice::AccessibilityGestureEvent& in_gestureEvent) = 0;
  virtual ::ndk::ScopedAStatus clearAccessibilityCache() = 0;
  virtual ::ndk::ScopedAStatus onKeyEvent(const ::aidl::android::view::KeyEvent& in_event, int32_t in_sequence) = 0;
  virtual ::ndk::ScopedAStatus onMagnificationChanged(int32_t in_displayId, const ::aidl::android::graphics::Region& in_region, const ::aidl::android::accessibilityservice::MagnificationConfig& in_config) = 0;
  virtual ::ndk::ScopedAStatus onMotionEvent(const ::aidl::android::view::MotionEvent& in_event) = 0;
  virtual ::ndk::ScopedAStatus onTouchStateChanged(int32_t in_displayId, int32_t in_state) = 0;
  virtual ::ndk::ScopedAStatus onSoftKeyboardShowModeChanged(int32_t in_showMode) = 0;
  virtual ::ndk::ScopedAStatus onPerformGestureResult(int32_t in_sequence, bool in_completedSuccessfully) = 0;
  virtual ::ndk::ScopedAStatus onFingerprintCapturingGesturesChanged(bool in_capturing) = 0;
  virtual ::ndk::ScopedAStatus onFingerprintGesture(int32_t in_gesture) = 0;
  virtual ::ndk::ScopedAStatus onAccessibilityButtonClicked(int32_t in_displayId) = 0;
  virtual ::ndk::ScopedAStatus onAccessibilityButtonAvailabilityChanged(bool in_available) = 0;
  virtual ::ndk::ScopedAStatus onSystemActionsChanged() = 0;
  virtual ::ndk::ScopedAStatus createImeSession(const std::shared_ptr<::aidl::com::android::internal::inputmethod::IAccessibilityInputMethodSessionCallback>& in_callback) = 0;
  virtual ::ndk::ScopedAStatus setImeSessionEnabled(const std::shared_ptr<::aidl::com::android::internal::inputmethod::IAccessibilityInputMethodSession>& in_session, bool in_enabled) = 0;
  virtual ::ndk::ScopedAStatus bindInput() = 0;
  virtual ::ndk::ScopedAStatus unbindInput() = 0;
  virtual ::ndk::ScopedAStatus startInput(const std::shared_ptr<::aidl::com::android::internal::inputmethod::IRemoteAccessibilityInputConnection>& in_connection, const ::aidl::android::view::inputmethod::EditorInfo& in_editorInfo, bool in_restarting) = 0;
private:
  static std::shared_ptr<IAccessibilityServiceClient> default_impl;
};
class IAccessibilityServiceClientDefault : public IAccessibilityServiceClient {
public:
  ::ndk::ScopedAStatus init(const std::shared_ptr<::aidl::android::accessibilityservice::IAccessibilityServiceConnection>& in_connection, int32_t in_connectionId, const ::ndk::SpAIBinder& in_windowToken) override;
  ::ndk::ScopedAStatus onAccessibilityEvent(const ::aidl::android::view::accessibility::AccessibilityEvent& in_event, bool in_serviceWantsEvent) override;
  ::ndk::ScopedAStatus onInterrupt() override;
  ::ndk::ScopedAStatus onGesture(const ::aidl::android::accessibilityservice::AccessibilityGestureEvent& in_gestureEvent) override;
  ::ndk::ScopedAStatus clearAccessibilityCache() override;
  ::ndk::ScopedAStatus onKeyEvent(const ::aidl::android::view::KeyEvent& in_event, int32_t in_sequence) override;
  ::ndk::ScopedAStatus onMagnificationChanged(int32_t in_displayId, const ::aidl::android::graphics::Region& in_region, const ::aidl::android::accessibilityservice::MagnificationConfig& in_config) override;
  ::ndk::ScopedAStatus onMotionEvent(const ::aidl::android::view::MotionEvent& in_event) override;
  ::ndk::ScopedAStatus onTouchStateChanged(int32_t in_displayId, int32_t in_state) override;
  ::ndk::ScopedAStatus onSoftKeyboardShowModeChanged(int32_t in_showMode) override;
  ::ndk::ScopedAStatus onPerformGestureResult(int32_t in_sequence, bool in_completedSuccessfully) override;
  ::ndk::ScopedAStatus onFingerprintCapturingGesturesChanged(bool in_capturing) override;
  ::ndk::ScopedAStatus onFingerprintGesture(int32_t in_gesture) override;
  ::ndk::ScopedAStatus onAccessibilityButtonClicked(int32_t in_displayId) override;
  ::ndk::ScopedAStatus onAccessibilityButtonAvailabilityChanged(bool in_available) override;
  ::ndk::ScopedAStatus onSystemActionsChanged() override;
  ::ndk::ScopedAStatus createImeSession(const std::shared_ptr<::aidl::com::android::internal::inputmethod::IAccessibilityInputMethodSessionCallback>& in_callback) override;
  ::ndk::ScopedAStatus setImeSessionEnabled(const std::shared_ptr<::aidl::com::android::internal::inputmethod::IAccessibilityInputMethodSession>& in_session, bool in_enabled) override;
  ::ndk::ScopedAStatus bindInput() override;
  ::ndk::ScopedAStatus unbindInput() override;
  ::ndk::ScopedAStatus startInput(const std::shared_ptr<::aidl::com::android::internal::inputmethod::IRemoteAccessibilityInputConnection>& in_connection, const ::aidl::android::view::inputmethod::EditorInfo& in_editorInfo, bool in_restarting) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
