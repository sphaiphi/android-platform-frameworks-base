/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IGraphicsStatsCallback.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/view/IGraphicsStatsCallback.h"

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
class BnGraphicsStatsCallback : public ::ndk::BnCInterface<IGraphicsStatsCallback> {
public:
  BnGraphicsStatsCallback();
  virtual ~BnGraphicsStatsCallback();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IGraphicsStatsCallbackDelegator : public BnGraphicsStatsCallback {
public:
  explicit IGraphicsStatsCallbackDelegator(const std::shared_ptr<IGraphicsStatsCallback> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus onRotateGraphicsStatsBuffer() override {
    return _impl->onRotateGraphicsStatsBuffer();
  }
protected:
private:
  std::shared_ptr<IGraphicsStatsCallback> _impl;
};

}  // namespace view
}  // namespace android
}  // namespace aidl
