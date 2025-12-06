/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/cpp/ /home/roto/git/android-platform-frameworks-base/core/cpp/android/accessibilityservice/IAccessibilityInputMethodSession.aidl
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
#include <android/binder_interface_utils.h>
#include <android/view/inputmethod>
#include <aidl/android/accessibilityservice/IRemoteAccessibilityInputConnection.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::accessibilityservice {
class IRemoteAccessibilityInputConnection;
}  // namespace aidl::android::accessibilityservice
namespace aidl {
namespace android {
namespace accessibilityservice {
class IAccessibilityInputMethodSessionDelegator;

class IAccessibilityInputMethodSession : public ::ndk::ICInterface {
public:
  typedef IAccessibilityInputMethodSessionDelegator DefaultDelegator;
  static const char* descriptor;
  IAccessibilityInputMethodSession();
  virtual ~IAccessibilityInputMethodSession();

  static constexpr uint32_t TRANSACTION_finishInput = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_updateSelection = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_invalidateInput = FIRST_CALL_TRANSACTION + 2;

  static std::shared_ptr<IAccessibilityInputMethodSession> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IAccessibilityInputMethodSession>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IAccessibilityInputMethodSession>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IAccessibilityInputMethodSession>& impl);
  static const std::shared_ptr<IAccessibilityInputMethodSession>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus finishInput() = 0;
  virtual ::ndk::ScopedAStatus updateSelection(int32_t in_oldSelStart, int32_t in_oldSelEnd, int32_t in_newSelStart, int32_t in_newSelEnd, int32_t in_candidatesStart, int32_t in_candidatesEnd) = 0;
  virtual ::ndk::ScopedAStatus invalidateInput(const ::aidl::android::view::inputmethod::EditorInfo& in_editorInfo, const std::shared_ptr<::aidl::android::accessibilityservice::IRemoteAccessibilityInputConnection>& in_connection, int32_t in_sessionId) = 0;
private:
  static std::shared_ptr<IAccessibilityInputMethodSession> default_impl;
};
class IAccessibilityInputMethodSessionDefault : public IAccessibilityInputMethodSession {
public:
  ::ndk::ScopedAStatus finishInput() override;
  ::ndk::ScopedAStatus updateSelection(int32_t in_oldSelStart, int32_t in_oldSelEnd, int32_t in_newSelStart, int32_t in_newSelEnd, int32_t in_candidatesStart, int32_t in_candidatesEnd) override;
  ::ndk::ScopedAStatus invalidateInput(const ::aidl::android::view::inputmethod::EditorInfo& in_editorInfo, const std::shared_ptr<::aidl::android::accessibilityservice::IRemoteAccessibilityInputConnection>& in_connection, int32_t in_sessionId) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
