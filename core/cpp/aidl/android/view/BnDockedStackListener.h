/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDockedStackListener.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/view/IDockedStackListener.h"

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
class BnDockedStackListener : public ::ndk::BnCInterface<IDockedStackListener> {
public:
  BnDockedStackListener();
  virtual ~BnDockedStackListener();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IDockedStackListenerDelegator : public BnDockedStackListener {
public:
  explicit IDockedStackListenerDelegator(const std::shared_ptr<IDockedStackListener> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus onDividerVisibilityChanged(bool in_visible) override {
    return _impl->onDividerVisibilityChanged(in_visible);
  }
  ::ndk::ScopedAStatus onDockedStackExistsChanged(bool in_exists) override {
    return _impl->onDockedStackExistsChanged(in_exists);
  }
  ::ndk::ScopedAStatus onDockedStackMinimizedChanged(bool in_minimized, int64_t in_animDuration, bool in_isHomeStackResizable) override {
    return _impl->onDockedStackMinimizedChanged(in_minimized, in_animDuration, in_isHomeStackResizable);
  }
  ::ndk::ScopedAStatus onAdjustedForImeChanged(bool in_adjustedForIme, int64_t in_animDuration) override {
    return _impl->onAdjustedForImeChanged(in_adjustedForIme, in_animDuration);
  }
  ::ndk::ScopedAStatus onDockSideChanged(int32_t in_newDockSide) override {
    return _impl->onDockSideChanged(in_newDockSide);
  }
protected:
private:
  std::shared_ptr<IDockedStackListener> _impl;
};

}  // namespace view
}  // namespace android
}  // namespace aidl
