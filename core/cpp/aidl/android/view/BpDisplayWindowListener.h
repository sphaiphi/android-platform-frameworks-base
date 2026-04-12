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

namespace aidl {
namespace android {
namespace view {
class BpDisplayWindowListener : public ::ndk::BpCInterface<IDisplayWindowListener> {
public:
  explicit BpDisplayWindowListener(const ::ndk::SpAIBinder& binder);
  virtual ~BpDisplayWindowListener();

  ::ndk::ScopedAStatus onDisplayAdded(int32_t in_displayId) override;
  ::ndk::ScopedAStatus onDisplayConfigurationChanged(int32_t in_displayId, const ::aidl::android::content::res::Configuration& in_newConfig) override;
  ::ndk::ScopedAStatus onDisplayRemoved(int32_t in_displayId) override;
  ::ndk::ScopedAStatus onFixedRotationStarted(int32_t in_displayId, int32_t in_newRotation) override;
  ::ndk::ScopedAStatus onFixedRotationFinished(int32_t in_displayId) override;
  ::ndk::ScopedAStatus onKeepClearAreasChanged(int32_t in_displayId, const std::vector<::aidl::android::graphics::Rect>& in_restricted, const std::vector<::aidl::android::graphics::Rect>& in_unrestricted) override;
  ::ndk::ScopedAStatus onDesktopModeEligibleChanged(int32_t in_displayId) override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
