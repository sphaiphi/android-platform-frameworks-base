/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayChangeWindowController.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/view/IDisplayChangeWindowController.h"

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
class BnDisplayChangeWindowController : public ::ndk::BnCInterface<IDisplayChangeWindowController> {
public:
  BnDisplayChangeWindowController();
  virtual ~BnDisplayChangeWindowController();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IDisplayChangeWindowControllerDelegator : public BnDisplayChangeWindowController {
public:
  explicit IDisplayChangeWindowControllerDelegator(const std::shared_ptr<IDisplayChangeWindowController> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus onDisplayChange(int32_t in_displayId, int32_t in_fromRotation, int32_t in_toRotation, const ::aidl::android::window::DisplayAreaInfo& in_newDisplayAreaInfo, const std::shared_ptr<::aidl::android::view::IDisplayChangeWindowCallback>& in_callback) override {
    return _impl->onDisplayChange(in_displayId, in_fromRotation, in_toRotation, in_newDisplayAreaInfo, in_callback);
  }
protected:
private:
  std::shared_ptr<IDisplayChangeWindowController> _impl;
};

}  // namespace view
}  // namespace android
}  // namespace aidl
