/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayWindowInsetsController.aidl
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
#include <android/content>
#include <android/view>
#include <android/view/inputmethod>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace view {
class IDisplayWindowInsetsControllerDelegator;

class IDisplayWindowInsetsController : public ::ndk::ICInterface {
public:
  typedef IDisplayWindowInsetsControllerDelegator DefaultDelegator;
  static const char* descriptor;
  IDisplayWindowInsetsController();
  virtual ~IDisplayWindowInsetsController();

  static constexpr uint32_t TRANSACTION_topFocusedWindowChanged = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_insetsChanged = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_insetsControlChanged = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_showInsets = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_hideInsets = FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_setImeInputTargetRequestedVisibility = FIRST_CALL_TRANSACTION + 5;

  static std::shared_ptr<IDisplayWindowInsetsController> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IDisplayWindowInsetsController>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IDisplayWindowInsetsController>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IDisplayWindowInsetsController>& impl);
  static const std::shared_ptr<IDisplayWindowInsetsController>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus topFocusedWindowChanged(const ::aidl::android::content::ComponentName& in_component, int32_t in_requestedVisibleTypes) = 0;
  virtual ::ndk::ScopedAStatus insetsChanged(const ::aidl::android::view::InsetsState& in_insetsState) = 0;
  virtual ::ndk::ScopedAStatus insetsControlChanged(const ::aidl::android::view::InsetsState& in_insetsState, const std::vector<::aidl::android::view::InsetsSourceControl>& in_activeControls) = 0;
  virtual ::ndk::ScopedAStatus showInsets(int32_t in_types, bool in_fromIme, const std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token>& in_statsToken) = 0;
  virtual ::ndk::ScopedAStatus hideInsets(int32_t in_types, bool in_fromIme, const std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token>& in_statsToken) = 0;
  virtual ::ndk::ScopedAStatus setImeInputTargetRequestedVisibility(bool in_visible, const ::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token& in_statsToken) = 0;
private:
  static std::shared_ptr<IDisplayWindowInsetsController> default_impl;
};
class IDisplayWindowInsetsControllerDefault : public IDisplayWindowInsetsController {
public:
  ::ndk::ScopedAStatus topFocusedWindowChanged(const ::aidl::android::content::ComponentName& in_component, int32_t in_requestedVisibleTypes) override;
  ::ndk::ScopedAStatus insetsChanged(const ::aidl::android::view::InsetsState& in_insetsState) override;
  ::ndk::ScopedAStatus insetsControlChanged(const ::aidl::android::view::InsetsState& in_insetsState, const std::vector<::aidl::android::view::InsetsSourceControl>& in_activeControls) override;
  ::ndk::ScopedAStatus showInsets(int32_t in_types, bool in_fromIme, const std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token>& in_statsToken) override;
  ::ndk::ScopedAStatus hideInsets(int32_t in_types, bool in_fromIme, const std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token>& in_statsToken) override;
  ::ndk::ScopedAStatus setImeInputTargetRequestedVisibility(bool in_visible, const ::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token& in_statsToken) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
