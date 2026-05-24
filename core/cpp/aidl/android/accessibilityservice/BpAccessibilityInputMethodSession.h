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

namespace aidl {
namespace android {
namespace accessibilityservice {
class BpAccessibilityInputMethodSession : public ::ndk::BpCInterface<IAccessibilityInputMethodSession> {
public:
  explicit BpAccessibilityInputMethodSession(const ::ndk::SpAIBinder& binder);
  virtual ~BpAccessibilityInputMethodSession();

  ::ndk::ScopedAStatus finishInput() override;
  ::ndk::ScopedAStatus updateSelection(int32_t in_oldSelStart, int32_t in_oldSelEnd, int32_t in_newSelStart, int32_t in_newSelEnd, int32_t in_candidatesStart, int32_t in_candidatesEnd) override;
  ::ndk::ScopedAStatus invalidateInput(const ::aidl::android::view::inputmethod::EditorInfo& in_editorInfo, const std::shared_ptr<::aidl::android::accessibilityservice::IRemoteAccessibilityInputConnection>& in_connection, int32_t in_sessionId) override;
};
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
