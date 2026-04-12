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

namespace aidl {
namespace android {
namespace view {
class BpDockedStackListener : public ::ndk::BpCInterface<IDockedStackListener> {
public:
  explicit BpDockedStackListener(const ::ndk::SpAIBinder& binder);
  virtual ~BpDockedStackListener();

  ::ndk::ScopedAStatus onDividerVisibilityChanged(bool in_visible) override;
  ::ndk::ScopedAStatus onDockedStackExistsChanged(bool in_exists) override;
  ::ndk::ScopedAStatus onDockedStackMinimizedChanged(bool in_minimized, int64_t in_animDuration, bool in_isHomeStackResizable) override;
  ::ndk::ScopedAStatus onAdjustedForImeChanged(bool in_adjustedForIme, int64_t in_animDuration) override;
  ::ndk::ScopedAStatus onDockSideChanged(int32_t in_newDockSide) override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
