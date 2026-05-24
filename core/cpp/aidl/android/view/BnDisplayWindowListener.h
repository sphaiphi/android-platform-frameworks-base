/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayWindowListener.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/view/IDisplayWindowListener.h"

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
class BnDisplayWindowListener : public ::ndk::BnCInterface<IDisplayWindowListener> {
public:
  BnDisplayWindowListener();
  virtual ~BnDisplayWindowListener();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IDisplayWindowListenerDelegator : public BnDisplayWindowListener {
public:
  explicit IDisplayWindowListenerDelegator(const std::shared_ptr<IDisplayWindowListener> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus onDisplayAdded(int32_t in_displayId) override {
    return _impl->onDisplayAdded(in_displayId);
  }
  ::ndk::ScopedAStatus onDisplayConfigurationChanged(int32_t in_displayId, const ::aidl::android::content::res::Configuration& in_newConfig) override {
    return _impl->onDisplayConfigurationChanged(in_displayId, in_newConfig);
  }
  ::ndk::ScopedAStatus onDisplayRemoved(int32_t in_displayId) override {
    return _impl->onDisplayRemoved(in_displayId);
  }
  ::ndk::ScopedAStatus onFixedRotationStarted(int32_t in_displayId, int32_t in_newRotation) override {
    return _impl->onFixedRotationStarted(in_displayId, in_newRotation);
  }
  ::ndk::ScopedAStatus onFixedRotationFinished(int32_t in_displayId) override {
    return _impl->onFixedRotationFinished(in_displayId);
  }
  ::ndk::ScopedAStatus onKeepClearAreasChanged(int32_t in_displayId, const std::vector<::aidl::android::graphics::Rect>& in_restricted, const std::vector<::aidl::android::graphics::Rect>& in_unrestricted) override {
    return _impl->onKeepClearAreasChanged(in_displayId, in_restricted, in_unrestricted);
  }
  ::ndk::ScopedAStatus onDesktopModeEligibleChanged(int32_t in_displayId) override {
    return _impl->onDesktopModeEligibleChanged(in_displayId);
  }
protected:
private:
  std::shared_ptr<IDisplayWindowListener> _impl;
};

}  // namespace view
}  // namespace android
}  // namespace aidl
