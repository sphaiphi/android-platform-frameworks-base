/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/app/IActivityController.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/app/IActivityController.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace android {
namespace app {
class BpActivityController : public ::ndk::BpCInterface<IActivityController> {
public:
  explicit BpActivityController(const ::ndk::SpAIBinder& binder);
  virtual ~BpActivityController();

  ::ndk::ScopedAStatus activityStarting(const ::aidl::android::content::Intent& in_intent, const std::string& in_pkg, bool* _aidl_return) override;
  ::ndk::ScopedAStatus activityResuming(const std::string& in_pkg, bool* _aidl_return) override;
  ::ndk::ScopedAStatus appCrashed(const std::string& in_processName, int32_t in_pid, const std::string& in_shortMsg, const std::string& in_longMsg, int64_t in_timeMillis, const std::string& in_stackTrace, bool* _aidl_return) override;
  ::ndk::ScopedAStatus appEarlyNotResponding(const std::string& in_processName, int32_t in_pid, const std::string& in_annotation, int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus appNotResponding(const std::string& in_processName, int32_t in_pid, const std::string& in_processStats, int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus systemNotResponding(const std::string& in_msg, int32_t* _aidl_return) override;
};
}  // namespace app
}  // namespace android
}  // namespace aidl
