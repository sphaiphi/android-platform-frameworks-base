/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/app/IActivityController.aidl
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
#include <android/content>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace app {
class IActivityControllerDelegator;

class IActivityController : public ::ndk::ICInterface {
public:
  typedef IActivityControllerDelegator DefaultDelegator;
  static const char* descriptor;
  IActivityController();
  virtual ~IActivityController();

  static constexpr uint32_t TRANSACTION_activityStarting = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_activityResuming = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_appCrashed = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_appEarlyNotResponding = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_appNotResponding = FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_systemNotResponding = FIRST_CALL_TRANSACTION + 5;

  static std::shared_ptr<IActivityController> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IActivityController>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IActivityController>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IActivityController>& impl);
  static const std::shared_ptr<IActivityController>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus activityStarting(const ::aidl::android::content::Intent& in_intent, const std::string& in_pkg, bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus activityResuming(const std::string& in_pkg, bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus appCrashed(const std::string& in_processName, int32_t in_pid, const std::string& in_shortMsg, const std::string& in_longMsg, int64_t in_timeMillis, const std::string& in_stackTrace, bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus appEarlyNotResponding(const std::string& in_processName, int32_t in_pid, const std::string& in_annotation, int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus appNotResponding(const std::string& in_processName, int32_t in_pid, const std::string& in_processStats, int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus systemNotResponding(const std::string& in_msg, int32_t* _aidl_return) = 0;
private:
  static std::shared_ptr<IActivityController> default_impl;
};
class IActivityControllerDefault : public IActivityController {
public:
  ::ndk::ScopedAStatus activityStarting(const ::aidl::android::content::Intent& in_intent, const std::string& in_pkg, bool* _aidl_return) override;
  ::ndk::ScopedAStatus activityResuming(const std::string& in_pkg, bool* _aidl_return) override;
  ::ndk::ScopedAStatus appCrashed(const std::string& in_processName, int32_t in_pid, const std::string& in_shortMsg, const std::string& in_longMsg, int64_t in_timeMillis, const std::string& in_stackTrace, bool* _aidl_return) override;
  ::ndk::ScopedAStatus appEarlyNotResponding(const std::string& in_processName, int32_t in_pid, const std::string& in_annotation, int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus appNotResponding(const std::string& in_processName, int32_t in_pid, const std::string& in_processStats, int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus systemNotResponding(const std::string& in_msg, int32_t* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace app
}  // namespace android
}  // namespace aidl
