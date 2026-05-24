/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IInputFilterHost.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/view/IInputFilterHost.h"

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
class BnInputFilterHost : public ::ndk::BnCInterface<IInputFilterHost> {
public:
  BnInputFilterHost();
  virtual ~BnInputFilterHost();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IInputFilterHostDelegator : public BnInputFilterHost {
public:
  explicit IInputFilterHostDelegator(const std::shared_ptr<IInputFilterHost> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus sendInputEvent(const ::aidl::android::view::InputEvent& in_event, int32_t in_policyFlags) override {
    return _impl->sendInputEvent(in_event, in_policyFlags);
  }
protected:
private:
  std::shared_ptr<IInputFilterHost> _impl;
};

}  // namespace view
}  // namespace android
}  // namespace aidl
