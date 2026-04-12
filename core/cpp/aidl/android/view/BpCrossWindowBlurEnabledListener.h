/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/ICrossWindowBlurEnabledListener.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/view/ICrossWindowBlurEnabledListener.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace android {
namespace view {
class BpCrossWindowBlurEnabledListener : public ::ndk::BpCInterface<ICrossWindowBlurEnabledListener> {
public:
  explicit BpCrossWindowBlurEnabledListener(const ::ndk::SpAIBinder& binder);
  virtual ~BpCrossWindowBlurEnabledListener();

  ::ndk::ScopedAStatus onCrossWindowBlurEnabledChanged(bool in_enabled) override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
