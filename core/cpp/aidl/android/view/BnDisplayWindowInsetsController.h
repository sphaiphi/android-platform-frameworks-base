/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayWindowInsetsController.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/view/IDisplayWindowInsetsController.h"

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
class BnDisplayWindowInsetsController : public ::ndk::BnCInterface<IDisplayWindowInsetsController> {
public:
  BnDisplayWindowInsetsController();
  virtual ~BnDisplayWindowInsetsController();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IDisplayWindowInsetsControllerDelegator : public BnDisplayWindowInsetsController {
public:
  explicit IDisplayWindowInsetsControllerDelegator(const std::shared_ptr<IDisplayWindowInsetsController> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus topFocusedWindowChanged(const ::aidl::android::content::ComponentName& in_component, int32_t in_requestedVisibleTypes) override {
    return _impl->topFocusedWindowChanged(in_component, in_requestedVisibleTypes);
  }
  ::ndk::ScopedAStatus insetsChanged(const ::aidl::android::view::InsetsState& in_insetsState) override {
    return _impl->insetsChanged(in_insetsState);
  }
  ::ndk::ScopedAStatus insetsControlChanged(const ::aidl::android::view::InsetsState& in_insetsState, const std::vector<::aidl::android::view::InsetsSourceControl>& in_activeControls) override {
    return _impl->insetsControlChanged(in_insetsState, in_activeControls);
  }
  ::ndk::ScopedAStatus showInsets(int32_t in_types, bool in_fromIme, const std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token>& in_statsToken) override {
    return _impl->showInsets(in_types, in_fromIme, in_statsToken);
  }
  ::ndk::ScopedAStatus hideInsets(int32_t in_types, bool in_fromIme, const std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token>& in_statsToken) override {
    return _impl->hideInsets(in_types, in_fromIme, in_statsToken);
  }
  ::ndk::ScopedAStatus setImeInputTargetRequestedVisibility(bool in_visible, const ::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token& in_statsToken) override {
    return _impl->setImeInputTargetRequestedVisibility(in_visible, in_statsToken);
  }
protected:
private:
  std::shared_ptr<IDisplayWindowInsetsController> _impl;
};

}  // namespace view
}  // namespace android
}  // namespace aidl
