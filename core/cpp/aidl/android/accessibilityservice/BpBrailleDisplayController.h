/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=. --out=. --include=/home/roto/git/android_frameworks_base/core/java --include=/home/roto/git/android_frameworks_base/graphics/java /home/roto/git/android_frameworks_base/core/java/android/accessibilityservice/IBrailleDisplayController.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/accessibilityservice/IBrailleDisplayController.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace android {
namespace accessibilityservice {
class BpBrailleDisplayController : public ::ndk::BpCInterface<IBrailleDisplayController> {
public:
  explicit BpBrailleDisplayController(const ::ndk::SpAIBinder& binder);
  virtual ~BpBrailleDisplayController();

  ::ndk::ScopedAStatus onConnected(const std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayConnection>& in_connection, const std::vector<uint8_t>& in_hidDescriptor) override;
  ::ndk::ScopedAStatus onConnectionFailed(int32_t in_error) override;
  ::ndk::ScopedAStatus onInput(const std::vector<uint8_t>& in_input) override;
  ::ndk::ScopedAStatus onDisconnected() override;
};
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
