/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=. --out=. --include=/home/roto/git/android_frameworks_base/core/java --include=/home/roto/git/android_frameworks_base/graphics/java /home/roto/git/android_frameworks_base/core/java/android/accessibilityservice/IAccessibilityServiceClient.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/accessibilityservice/IAccessibilityServiceClient.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace android {
namespace accessibilityservice {
class BpAccessibilityServiceClient : public ::ndk::BpCInterface<IAccessibilityServiceClient> {
public:
  explicit BpAccessibilityServiceClient(const ::ndk::SpAIBinder& binder);
  virtual ~BpAccessibilityServiceClient();

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
};
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
