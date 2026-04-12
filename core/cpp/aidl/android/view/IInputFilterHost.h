/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IInputFilterHost.aidl
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
class IInputFilterHostDelegator;

class IInputFilterHost : public ::ndk::ICInterface {
public:
  typedef IInputFilterHostDelegator DefaultDelegator;
  static const char* descriptor;
  IInputFilterHost();
  virtual ~IInputFilterHost();

  static constexpr uint32_t TRANSACTION_sendInputEvent = FIRST_CALL_TRANSACTION + 0;

  static std::shared_ptr<IInputFilterHost> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IInputFilterHost>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IInputFilterHost>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IInputFilterHost>& impl);
  static const std::shared_ptr<IInputFilterHost>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus sendInputEvent(const ::aidl::android::view::InputEvent& in_event, int32_t in_policyFlags) = 0;
private:
  static std::shared_ptr<IInputFilterHost> default_impl;
};
class IInputFilterHostDefault : public IInputFilterHost {
public:
  ::ndk::ScopedAStatus sendInputEvent(const ::aidl::android::view::InputEvent& in_event, int32_t in_policyFlags) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
