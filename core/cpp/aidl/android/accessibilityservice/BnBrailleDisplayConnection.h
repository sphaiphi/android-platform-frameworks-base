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
#include <cassert>

#ifndef __BIONIC__
#ifndef __assert2
#define __assert2(a,b,c,d) ((void)0)
#endif
#endif

namespace aidl {
namespace android {
namespace accessibilityservice {
class BnBrailleDisplayConnection : public ::ndk::BnCInterface<IBrailleDisplayConnection> {
public:
  BnBrailleDisplayConnection();
  virtual ~BnBrailleDisplayConnection();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IBrailleDisplayConnectionDelegator : public BnBrailleDisplayConnection {
public:
  explicit IBrailleDisplayConnectionDelegator(const std::shared_ptr<IBrailleDisplayConnection> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus disconnect() override {
    return _impl->disconnect();
  }
  ::ndk::ScopedAStatus write(const std::vector<uint8_t>& in_output) override {
    return _impl->write(in_output);
  }
protected:
private:
  std::shared_ptr<IBrailleDisplayConnection> _impl;
};

}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
