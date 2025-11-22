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
#include <cassert>

#ifndef __BIONIC__
#ifndef __assert2
#define __assert2(a,b,c,d) ((void)0)
#endif
#endif

namespace aidl {
namespace android {
namespace accessibilityservice {
class BnAccessibilityServiceClient : public ::ndk::BnCInterface<IAccessibilityServiceClient> {
public:
  BnAccessibilityServiceClient();
  virtual ~BnAccessibilityServiceClient();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IAccessibilityServiceClientDelegator : public BnAccessibilityServiceClient {
public:
  explicit IAccessibilityServiceClientDelegator(const std::shared_ptr<IAccessibilityServiceClient> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus init(const std::shared_ptr<::aidl::android::accessibilityservice::IAccessibilityServiceConnection>& in_connection, int32_t in_connectionId, const ::ndk::SpAIBinder& in_windowToken) override {
    return _impl->init(in_connection, in_connectionId, in_windowToken);
  }
  ::ndk::ScopedAStatus onAccessibilityEvent(const ::aidl::android::view::accessibility::AccessibilityEvent& in_event, bool in_serviceWantsEvent) override {
    return _impl->onAccessibilityEvent(in_event, in_serviceWantsEvent);
  }
  ::ndk::ScopedAStatus onInterrupt() override {
    return _impl->onInterrupt();
  }
  ::ndk::ScopedAStatus onGesture(const ::aidl::android::accessibilityservice::AccessibilityGestureEvent& in_gestureEvent) override {
    return _impl->onGesture(in_gestureEvent);
  }
  ::ndk::ScopedAStatus clearAccessibilityCache() override {
    return _impl->clearAccessibilityCache();
  }
  ::ndk::ScopedAStatus onKeyEvent(const ::aidl::android::view::KeyEvent& in_event, int32_t in_sequence) override {
    return _impl->onKeyEvent(in_event, in_sequence);
  }
  ::ndk::ScopedAStatus onMagnificationChanged(int32_t in_displayId, const ::aidl::android::graphics::Region& in_region, const ::aidl::android::accessibilityservice::MagnificationConfig& in_config) override {
    return _impl->onMagnificationChanged(in_displayId, in_region, in_config);
  }
  ::ndk::ScopedAStatus onMotionEvent(const ::aidl::android::view::MotionEvent& in_event) override {
    return _impl->onMotionEvent(in_event);
  }
  ::ndk::ScopedAStatus onTouchStateChanged(int32_t in_displayId, int32_t in_state) override {
    return _impl->onTouchStateChanged(in_displayId, in_state);
  }
  ::ndk::ScopedAStatus onSoftKeyboardShowModeChanged(int32_t in_showMode) override {
    return _impl->onSoftKeyboardShowModeChanged(in_showMode);
  }
  ::ndk::ScopedAStatus onPerformGestureResult(int32_t in_sequence, bool in_completedSuccessfully) override {
    return _impl->onPerformGestureResult(in_sequence, in_completedSuccessfully);
  }
  ::ndk::ScopedAStatus onFingerprintCapturingGesturesChanged(bool in_capturing) override {
    return _impl->onFingerprintCapturingGesturesChanged(in_capturing);
  }
  ::ndk::ScopedAStatus onFingerprintGesture(int32_t in_gesture) override {
    return _impl->onFingerprintGesture(in_gesture);
  }
  ::ndk::ScopedAStatus onAccessibilityButtonClicked(int32_t in_displayId) override {
    return _impl->onAccessibilityButtonClicked(in_displayId);
  }
  ::ndk::ScopedAStatus onAccessibilityButtonAvailabilityChanged(bool in_available) override {
    return _impl->onAccessibilityButtonAvailabilityChanged(in_available);
  }
  ::ndk::ScopedAStatus onSystemActionsChanged() override {
    return _impl->onSystemActionsChanged();
  }
  ::ndk::ScopedAStatus createImeSession(const std::shared_ptr<::aidl::com::android::internal::inputmethod::IAccessibilityInputMethodSessionCallback>& in_callback) override {
    return _impl->createImeSession(in_callback);
  }
  ::ndk::ScopedAStatus setImeSessionEnabled(const std::shared_ptr<::aidl::com::android::internal::inputmethod::IAccessibilityInputMethodSession>& in_session, bool in_enabled) override {
    return _impl->setImeSessionEnabled(in_session, in_enabled);
  }
  ::ndk::ScopedAStatus bindInput() override {
    return _impl->bindInput();
  }
  ::ndk::ScopedAStatus unbindInput() override {
    return _impl->unbindInput();
  }
  ::ndk::ScopedAStatus startInput(const std::shared_ptr<::aidl::com::android::internal::inputmethod::IRemoteAccessibilityInputConnection>& in_connection, const ::aidl::android::view::inputmethod::EditorInfo& in_editorInfo, bool in_restarting) override {
    return _impl->startInput(in_connection, in_editorInfo, in_restarting);
  }
protected:
private:
  std::shared_ptr<IAccessibilityServiceClient> _impl;
};

}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
