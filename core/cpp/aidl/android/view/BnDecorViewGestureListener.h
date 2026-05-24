/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDecorViewGestureListener.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/view/IDecorViewGestureListener.h"

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
class BnDecorViewGestureListener : public ::ndk::BnCInterface<IDecorViewGestureListener> {
public:
  BnDecorViewGestureListener();
  virtual ~BnDecorViewGestureListener();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IDecorViewGestureListenerDelegator : public BnDecorViewGestureListener {
public:
  explicit IDecorViewGestureListenerDelegator(const std::shared_ptr<IDecorViewGestureListener> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus onInterceptionChanged(const ::ndk::SpAIBinder& in_windowToken, bool in_intercepted) override {
    return _impl->onInterceptionChanged(in_windowToken, in_intercepted);
  }
protected:
private:
  std::shared_ptr<IDecorViewGestureListener> _impl;
};

}  // namespace view
}  // namespace android
}  // namespace aidl
