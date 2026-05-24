/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IInputMonitorHost.aidl
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
class IInputMonitorHostDelegator;

class IInputMonitorHost : public ::ndk::ICInterface {
public:
  typedef IInputMonitorHostDelegator DefaultDelegator;
  static const char* descriptor;
  IInputMonitorHost();
  virtual ~IInputMonitorHost();

  static constexpr uint32_t TRANSACTION_pilferPointers = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_dispose = FIRST_CALL_TRANSACTION + 1;

  static std::shared_ptr<IInputMonitorHost> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IInputMonitorHost>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IInputMonitorHost>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IInputMonitorHost>& impl);
  static const std::shared_ptr<IInputMonitorHost>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus pilferPointers() = 0;
  virtual ::ndk::ScopedAStatus dispose() = 0;
private:
  static std::shared_ptr<IInputMonitorHost> default_impl;
};
class IInputMonitorHostDefault : public IInputMonitorHost {
public:
  ::ndk::ScopedAStatus pilferPointers() override;
  ::ndk::ScopedAStatus dispose() override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
