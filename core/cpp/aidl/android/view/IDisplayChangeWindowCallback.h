/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayChangeWindowCallback.aidl
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
#include <android/view>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace view {
class IDisplayChangeWindowCallbackDelegator;

class IDisplayChangeWindowCallback : public ::ndk::ICInterface {
public:
  typedef IDisplayChangeWindowCallbackDelegator DefaultDelegator;
  static const char* descriptor;
  IDisplayChangeWindowCallback();
  virtual ~IDisplayChangeWindowCallback();

  static constexpr uint32_t TRANSACTION_continueDisplayChange = FIRST_CALL_TRANSACTION + 0;

  static std::shared_ptr<IDisplayChangeWindowCallback> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IDisplayChangeWindowCallback>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IDisplayChangeWindowCallback>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IDisplayChangeWindowCallback>& impl);
  static const std::shared_ptr<IDisplayChangeWindowCallback>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus continueDisplayChange(const ::aidl::android::window::WindowContainerTransaction& in_t) = 0;
private:
  static std::shared_ptr<IDisplayChangeWindowCallback> default_impl;
};
class IDisplayChangeWindowCallbackDefault : public IDisplayChangeWindowCallback {
public:
  ::ndk::ScopedAStatus continueDisplayChange(const ::aidl::android::window::WindowContainerTransaction& in_t) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
