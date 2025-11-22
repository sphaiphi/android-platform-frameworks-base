/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=. --out=. --include=/home/roto/git/android_frameworks_base/core/java --include=/home/roto/git/android_frameworks_base/graphics/java /home/roto/git/android_frameworks_base/core/java/android/accessibilityservice/IBrailleDisplayConnection.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include "aidl/android/accessibilityservice/IBrailleDisplayConnection.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace android {
namespace accessibilityservice {
class BpBrailleDisplayConnection : public ::ndk::BpCInterface<IBrailleDisplayConnection> {
public:
  explicit BpBrailleDisplayConnection(const ::ndk::SpAIBinder& binder);
  virtual ~BpBrailleDisplayConnection();

  ::ndk::ScopedAStatus disconnect() override;
  ::ndk::ScopedAStatus write(const std::vector<uint8_t>& in_output) override;
};
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
