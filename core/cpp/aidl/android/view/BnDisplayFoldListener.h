/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayFoldListener.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/view/IDisplayFoldListener.h"

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
class BnDisplayFoldListener : public ::ndk::BnCInterface<IDisplayFoldListener> {
public:
  BnDisplayFoldListener();
  virtual ~BnDisplayFoldListener();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IDisplayFoldListenerDelegator : public BnDisplayFoldListener {
public:
  explicit IDisplayFoldListenerDelegator(const std::shared_ptr<IDisplayFoldListener> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus onDisplayFoldChanged(int32_t in_displayId, bool in_folded) override {
    return _impl->onDisplayFoldChanged(in_displayId, in_folded);
  }
protected:
private:
  std::shared_ptr<IDisplayFoldListener> _impl;
};

}  // namespace view
}  // namespace android
}  // namespace aidl
