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
#include <cassert>

#ifndef __BIONIC__
#ifndef __assert2
#define __assert2(a,b,c,d) ((void)0)
#endif
#endif

namespace aidl {
namespace android {
namespace accessibilityservice {
class BnBrailleDisplayController : public ::ndk::BnCInterface<IBrailleDisplayController> {
public:
  BnBrailleDisplayController();
  virtual ~BnBrailleDisplayController();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IBrailleDisplayControllerDelegator : public BnBrailleDisplayController {
public:
  explicit IBrailleDisplayControllerDelegator(const std::shared_ptr<IBrailleDisplayController> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus onConnected(const std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayConnection>& in_connection, const std::vector<uint8_t>& in_hidDescriptor) override {
    return _impl->onConnected(in_connection, in_hidDescriptor);
  }
  ::ndk::ScopedAStatus onConnectionFailed(int32_t in_error) override {
    return _impl->onConnectionFailed(in_error);
  }
  ::ndk::ScopedAStatus onInput(const std::vector<uint8_t>& in_input) override {
    return _impl->onInput(in_input);
  }
  ::ndk::ScopedAStatus onDisconnected() override {
    return _impl->onDisconnected();
  }
protected:
private:
  std::shared_ptr<IBrailleDisplayController> _impl;
};

}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
