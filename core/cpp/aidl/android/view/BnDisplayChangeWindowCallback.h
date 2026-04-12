/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayChangeWindowCallback.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/view/IDisplayChangeWindowCallback.h"

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
class BnDisplayChangeWindowCallback : public ::ndk::BnCInterface<IDisplayChangeWindowCallback> {
public:
  BnDisplayChangeWindowCallback();
  virtual ~BnDisplayChangeWindowCallback();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IDisplayChangeWindowCallbackDelegator : public BnDisplayChangeWindowCallback {
public:
  explicit IDisplayChangeWindowCallbackDelegator(const std::shared_ptr<IDisplayChangeWindowCallback> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus continueDisplayChange(const ::aidl::android::window::WindowContainerTransaction& in_t) override {
    return _impl->continueDisplayChange(in_t);
  }
protected:
private:
  std::shared_ptr<IDisplayChangeWindowCallback> _impl;
};

}  // namespace view
}  // namespace android
}  // namespace aidl
