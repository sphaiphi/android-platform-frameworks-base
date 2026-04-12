/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayChangeWindowController.aidl
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
#include <android/window>
#include <aidl/android/view/IDisplayChangeWindowCallback.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::view {
class IDisplayChangeWindowCallback;
}  // namespace aidl::android::view
namespace aidl {
namespace android {
namespace view {
class IDisplayChangeWindowControllerDelegator;

class IDisplayChangeWindowController : public ::ndk::ICInterface {
public:
  typedef IDisplayChangeWindowControllerDelegator DefaultDelegator;
  static const char* descriptor;
  IDisplayChangeWindowController();
  virtual ~IDisplayChangeWindowController();

  static constexpr uint32_t TRANSACTION_onDisplayChange = FIRST_CALL_TRANSACTION + 0;

  static std::shared_ptr<IDisplayChangeWindowController> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IDisplayChangeWindowController>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IDisplayChangeWindowController>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IDisplayChangeWindowController>& impl);
  static const std::shared_ptr<IDisplayChangeWindowController>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus onDisplayChange(int32_t in_displayId, int32_t in_fromRotation, int32_t in_toRotation, const ::aidl::android::window::DisplayAreaInfo& in_newDisplayAreaInfo, const std::shared_ptr<::aidl::android::view::IDisplayChangeWindowCallback>& in_callback) = 0;
private:
  static std::shared_ptr<IDisplayChangeWindowController> default_impl;
};
class IDisplayChangeWindowControllerDefault : public IDisplayChangeWindowController {
public:
  ::ndk::ScopedAStatus onDisplayChange(int32_t in_displayId, int32_t in_fromRotation, int32_t in_toRotation, const ::aidl::android::window::DisplayAreaInfo& in_newDisplayAreaInfo, const std::shared_ptr<::aidl::android::view::IDisplayChangeWindowCallback>& in_callback) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
