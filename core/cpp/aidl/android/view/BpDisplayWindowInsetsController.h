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

namespace aidl {
namespace android {
namespace view {
class BpDisplayWindowInsetsController : public ::ndk::BpCInterface<IDisplayWindowInsetsController> {
public:
  explicit BpDisplayWindowInsetsController(const ::ndk::SpAIBinder& binder);
  virtual ~BpDisplayWindowInsetsController();

  ::ndk::ScopedAStatus topFocusedWindowChanged(const ::aidl::android::content::ComponentName& in_component, int32_t in_requestedVisibleTypes) override;
  ::ndk::ScopedAStatus insetsChanged(const ::aidl::android::view::InsetsState& in_insetsState) override;
  ::ndk::ScopedAStatus insetsControlChanged(const ::aidl::android::view::InsetsState& in_insetsState, const std::vector<::aidl::android::view::InsetsSourceControl>& in_activeControls) override;
  ::ndk::ScopedAStatus showInsets(int32_t in_types, bool in_fromIme, const std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token>& in_statsToken) override;
  ::ndk::ScopedAStatus hideInsets(int32_t in_types, bool in_fromIme, const std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token>& in_statsToken) override;
  ::ndk::ScopedAStatus setImeInputTargetRequestedVisibility(bool in_visible, const ::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token& in_statsToken) override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
