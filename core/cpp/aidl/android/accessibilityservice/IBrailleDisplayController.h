/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=. --out=. --include=/home/roto/git/android_frameworks_base/core/java --include=/home/roto/git/android_frameworks_base/graphics/java /home/roto/git/android_frameworks_base/core/java/android/accessibilityservice/IBrailleDisplayController.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <android/binder_interface_utils.h>
#include <aidl/android/accessibilityservice/IBrailleDisplayConnection.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::accessibilityservice {
class IBrailleDisplayConnection;
}  // namespace aidl::android::accessibilityservice
namespace aidl {
namespace android {
namespace accessibilityservice {
class IBrailleDisplayControllerDelegator;

class IBrailleDisplayController : public ::ndk::ICInterface {
public:
  typedef IBrailleDisplayControllerDelegator DefaultDelegator;
  static const char* descriptor;
  IBrailleDisplayController();
  virtual ~IBrailleDisplayController();

  static constexpr uint32_t TRANSACTION_onConnected = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onConnectionFailed = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onInput = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onDisconnected = FIRST_CALL_TRANSACTION + 3;

  static std::shared_ptr<IBrailleDisplayController> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IBrailleDisplayController>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IBrailleDisplayController>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IBrailleDisplayController>& impl);
  static const std::shared_ptr<IBrailleDisplayController>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus onConnected(const std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayConnection>& in_connection, const std::vector<uint8_t>& in_hidDescriptor) = 0;
  virtual ::ndk::ScopedAStatus onConnectionFailed(int32_t in_error) = 0;
  virtual ::ndk::ScopedAStatus onInput(const std::vector<uint8_t>& in_input) = 0;
  virtual ::ndk::ScopedAStatus onDisconnected() = 0;
private:
  static std::shared_ptr<IBrailleDisplayController> default_impl;
};
class IBrailleDisplayControllerDefault : public IBrailleDisplayController {
public:
  ::ndk::ScopedAStatus onConnected(const std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayConnection>& in_connection, const std::vector<uint8_t>& in_hidDescriptor) override;
  ::ndk::ScopedAStatus onConnectionFailed(int32_t in_error) override;
  ::ndk::ScopedAStatus onInput(const std::vector<uint8_t>& in_input) override;
  ::ndk::ScopedAStatus onDisconnected() override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
