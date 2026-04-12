/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDockedStackListener.aidl
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
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace view {
class IDockedStackListenerDelegator;

class IDockedStackListener : public ::ndk::ICInterface {
public:
  typedef IDockedStackListenerDelegator DefaultDelegator;
  static const char* descriptor;
  IDockedStackListener();
  virtual ~IDockedStackListener();

  static constexpr uint32_t TRANSACTION_onDividerVisibilityChanged = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onDockedStackExistsChanged = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onDockedStackMinimizedChanged = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onAdjustedForImeChanged = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_onDockSideChanged = FIRST_CALL_TRANSACTION + 4;

  static std::shared_ptr<IDockedStackListener> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IDockedStackListener>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IDockedStackListener>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IDockedStackListener>& impl);
  static const std::shared_ptr<IDockedStackListener>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus onDividerVisibilityChanged(bool in_visible) = 0;
  virtual ::ndk::ScopedAStatus onDockedStackExistsChanged(bool in_exists) = 0;
  virtual ::ndk::ScopedAStatus onDockedStackMinimizedChanged(bool in_minimized, int64_t in_animDuration, bool in_isHomeStackResizable) = 0;
  virtual ::ndk::ScopedAStatus onAdjustedForImeChanged(bool in_adjustedForIme, int64_t in_animDuration) = 0;
  virtual ::ndk::ScopedAStatus onDockSideChanged(int32_t in_newDockSide) = 0;
private:
  static std::shared_ptr<IDockedStackListener> default_impl;
};
class IDockedStackListenerDefault : public IDockedStackListener {
public:
  ::ndk::ScopedAStatus onDividerVisibilityChanged(bool in_visible) override;
  ::ndk::ScopedAStatus onDockedStackExistsChanged(bool in_exists) override;
  ::ndk::ScopedAStatus onDockedStackMinimizedChanged(bool in_minimized, int64_t in_animDuration, bool in_isHomeStackResizable) override;
  ::ndk::ScopedAStatus onAdjustedForImeChanged(bool in_adjustedForIme, int64_t in_animDuration) override;
  ::ndk::ScopedAStatus onDockSideChanged(int32_t in_newDockSide) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
