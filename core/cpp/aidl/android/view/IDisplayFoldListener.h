/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayFoldListener.aidl
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
namespace view {
class IDisplayFoldListenerDelegator;

class IDisplayFoldListener : public ::ndk::ICInterface {
public:
  typedef IDisplayFoldListenerDelegator DefaultDelegator;
  static const char* descriptor;
  IDisplayFoldListener();
  virtual ~IDisplayFoldListener();

  static constexpr uint32_t TRANSACTION_onDisplayFoldChanged = FIRST_CALL_TRANSACTION + 0;

  static std::shared_ptr<IDisplayFoldListener> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IDisplayFoldListener>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IDisplayFoldListener>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IDisplayFoldListener>& impl);
  static const std::shared_ptr<IDisplayFoldListener>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus onDisplayFoldChanged(int32_t in_displayId, bool in_folded) = 0;
private:
  static std::shared_ptr<IDisplayFoldListener> default_impl;
};
class IDisplayFoldListenerDefault : public IDisplayFoldListener {
public:
  ::ndk::ScopedAStatus onDisplayFoldChanged(int32_t in_displayId, bool in_folded) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
