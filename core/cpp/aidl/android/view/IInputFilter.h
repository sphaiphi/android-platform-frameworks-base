/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IInputFilter.aidl
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
#include <aidl/android/view/IInputFilterHost.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::view {
class IInputFilterHost;
}  // namespace aidl::android::view
namespace aidl {
namespace android {
namespace view {
class IInputFilterDelegator;

class IInputFilter : public ::ndk::ICInterface {
public:
  typedef IInputFilterDelegator DefaultDelegator;
  static const char* descriptor;
  IInputFilter();
  virtual ~IInputFilter();

  static constexpr uint32_t TRANSACTION_install = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_uninstall = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_filterInputEvent = FIRST_CALL_TRANSACTION + 2;

  static std::shared_ptr<IInputFilter> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IInputFilter>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IInputFilter>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IInputFilter>& impl);
  static const std::shared_ptr<IInputFilter>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus install(const std::shared_ptr<::aidl::android::view::IInputFilterHost>& in_host) = 0;
  virtual ::ndk::ScopedAStatus uninstall() = 0;
  virtual ::ndk::ScopedAStatus filterInputEvent(const ::aidl::android::view::InputEvent& in_event, int32_t in_policyFlags) = 0;
private:
  static std::shared_ptr<IInputFilter> default_impl;
};
class IInputFilterDefault : public IInputFilter {
public:
  ::ndk::ScopedAStatus install(const std::shared_ptr<::aidl::android::view::IInputFilterHost>& in_host) override;
  ::ndk::ScopedAStatus uninstall() override;
  ::ndk::ScopedAStatus filterInputEvent(const ::aidl::android::view::InputEvent& in_event, int32_t in_policyFlags) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
