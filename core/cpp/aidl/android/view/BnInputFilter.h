/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IInputFilter.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/view/IInputFilter.h"

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
class BnInputFilter : public ::ndk::BnCInterface<IInputFilter> {
public:
  BnInputFilter();
  virtual ~BnInputFilter();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IInputFilterDelegator : public BnInputFilter {
public:
  explicit IInputFilterDelegator(const std::shared_ptr<IInputFilter> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus install(const std::shared_ptr<::aidl::android::view::IInputFilterHost>& in_host) override {
    return _impl->install(in_host);
  }
  ::ndk::ScopedAStatus uninstall() override {
    return _impl->uninstall();
  }
  ::ndk::ScopedAStatus filterInputEvent(const ::aidl::android::view::InputEvent& in_event, int32_t in_policyFlags) override {
    return _impl->filterInputEvent(in_event, in_policyFlags);
  }
protected:
private:
  std::shared_ptr<IInputFilter> _impl;
};

}  // namespace view
}  // namespace android
}  // namespace aidl
