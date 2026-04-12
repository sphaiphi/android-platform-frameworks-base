/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IGraphicsStats.aidl
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
#include <aidl/android/view/IGraphicsStatsCallback.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::view {
class IGraphicsStatsCallback;
}  // namespace aidl::android::view
namespace aidl {
namespace android {
namespace view {
class IGraphicsStatsDelegator;

class IGraphicsStats : public ::ndk::ICInterface {
public:
  typedef IGraphicsStatsDelegator DefaultDelegator;
  static const char* descriptor;
  IGraphicsStats();
  virtual ~IGraphicsStats();

  static constexpr uint32_t TRANSACTION_requestBufferForProcess = FIRST_CALL_TRANSACTION + 0;

  static std::shared_ptr<IGraphicsStats> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IGraphicsStats>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IGraphicsStats>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IGraphicsStats>& impl);
  static const std::shared_ptr<IGraphicsStats>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus requestBufferForProcess(const std::string& in_packageName, const std::shared_ptr<::aidl::android::view::IGraphicsStatsCallback>& in_callback, ::ndk::ScopedFileDescriptor* _aidl_return) = 0;
private:
  static std::shared_ptr<IGraphicsStats> default_impl;
};
class IGraphicsStatsDefault : public IGraphicsStats {
public:
  ::ndk::ScopedAStatus requestBufferForProcess(const std::string& in_packageName, const std::shared_ptr<::aidl::android::view::IGraphicsStatsCallback>& in_callback, ::ndk::ScopedFileDescriptor* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
