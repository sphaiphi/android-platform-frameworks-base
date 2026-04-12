/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IGraphicsStats.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/view/IGraphicsStats.h"

#include <android/binder_ibinder.h>
#include <cassert>

#ifndef __BIONIC__
#ifndef __assert2
#define __assert2(a,b,c,d) ((void)0)
#endif
#endif

namespace aidl {
namespace android {
namespace view {
class BnGraphicsStats : public ::ndk::BnCInterface<IGraphicsStats> {
public:
  BnGraphicsStats();
  virtual ~BnGraphicsStats();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IGraphicsStatsDelegator : public BnGraphicsStats {
public:
  explicit IGraphicsStatsDelegator(const std::shared_ptr<IGraphicsStats> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus requestBufferForProcess(const std::string& in_packageName, const std::shared_ptr<::aidl::android::view::IGraphicsStatsCallback>& in_callback, ::ndk::ScopedFileDescriptor* _aidl_return) override {
    return _impl->requestBufferForProcess(in_packageName, in_callback, _aidl_return);
  }
protected:
private:
  std::shared_ptr<IGraphicsStats> _impl;
};

}  // namespace view
}  // namespace android
}  // namespace aidl
