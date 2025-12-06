/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/cpp/ /home/roto/git/android-platform-frameworks-base/core/cpp/android/accessibilityservice/IAccessibilityInputMethodSession.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/accessibilityservice/IAccessibilityInputMethodSession.h"

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
class BnAccessibilityInputMethodSession : public ::ndk::BnCInterface<IAccessibilityInputMethodSession> {
public:
  BnAccessibilityInputMethodSession();
  virtual ~BnAccessibilityInputMethodSession();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IAccessibilityInputMethodSessionDelegator : public BnAccessibilityInputMethodSession {
public:
  explicit IAccessibilityInputMethodSessionDelegator(const std::shared_ptr<IAccessibilityInputMethodSession> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus finishInput() override {
    return _impl->finishInput();
  }
  ::ndk::ScopedAStatus updateSelection(int32_t in_oldSelStart, int32_t in_oldSelEnd, int32_t in_newSelStart, int32_t in_newSelEnd, int32_t in_candidatesStart, int32_t in_candidatesEnd) override {
    return _impl->updateSelection(in_oldSelStart, in_oldSelEnd, in_newSelStart, in_newSelEnd, in_candidatesStart, in_candidatesEnd);
  }
  ::ndk::ScopedAStatus invalidateInput(const ::aidl::android::view::inputmethod::EditorInfo& in_editorInfo, const std::shared_ptr<::aidl::android::accessibilityservice::IRemoteAccessibilityInputConnection>& in_connection, int32_t in_sessionId) override {
    return _impl->invalidateInput(in_editorInfo, in_connection, in_sessionId);
  }
protected:
private:
  std::shared_ptr<IAccessibilityInputMethodSession> _impl;
};

}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
