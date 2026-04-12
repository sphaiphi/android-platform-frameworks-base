/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDecorViewGestureListener.aidl
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
class IDecorViewGestureListenerDelegator;

class IDecorViewGestureListener : public ::ndk::ICInterface {
public:
  typedef IDecorViewGestureListenerDelegator DefaultDelegator;
  static const char* descriptor;
  IDecorViewGestureListener();
  virtual ~IDecorViewGestureListener();

  static constexpr uint32_t TRANSACTION_onInterceptionChanged = FIRST_CALL_TRANSACTION + 0;

  static std::shared_ptr<IDecorViewGestureListener> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IDecorViewGestureListener>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IDecorViewGestureListener>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IDecorViewGestureListener>& impl);
  static const std::shared_ptr<IDecorViewGestureListener>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus onInterceptionChanged(const ::ndk::SpAIBinder& in_windowToken, bool in_intercepted) = 0;
private:
  static std::shared_ptr<IDecorViewGestureListener> default_impl;
};
class IDecorViewGestureListenerDefault : public IDecorViewGestureListener {
public:
  ::ndk::ScopedAStatus onInterceptionChanged(const ::ndk::SpAIBinder& in_windowToken, bool in_intercepted) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
