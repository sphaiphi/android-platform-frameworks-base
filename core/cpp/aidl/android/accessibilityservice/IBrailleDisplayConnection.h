/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=. --out=. --include=/home/roto/git/android_frameworks_base/core/java --include=/home/roto/git/android_frameworks_base/graphics/java /home/roto/git/android_frameworks_base/core/java/android/accessibilityservice/IBrailleDisplayConnection.aidl
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
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace accessibilityservice {
class IBrailleDisplayConnectionDelegator;

class IBrailleDisplayConnection : public ::ndk::ICInterface {
public:
  typedef IBrailleDisplayConnectionDelegator DefaultDelegator;
  static const char* descriptor;
  IBrailleDisplayConnection();
  virtual ~IBrailleDisplayConnection();

  static constexpr uint32_t TRANSACTION_disconnect = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_write = FIRST_CALL_TRANSACTION + 1;

  static std::shared_ptr<IBrailleDisplayConnection> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IBrailleDisplayConnection>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IBrailleDisplayConnection>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IBrailleDisplayConnection>& impl);
  static const std::shared_ptr<IBrailleDisplayConnection>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus disconnect() = 0;
  virtual ::ndk::ScopedAStatus write(const std::vector<uint8_t>& in_output) = 0;
private:
  static std::shared_ptr<IBrailleDisplayConnection> default_impl;
};
class IBrailleDisplayConnectionDefault : public IBrailleDisplayConnection {
public:
  ::ndk::ScopedAStatus disconnect() override;
  ::ndk::ScopedAStatus write(const std::vector<uint8_t>& in_output) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
