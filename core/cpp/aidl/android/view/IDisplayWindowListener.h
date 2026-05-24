/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayWindowListener.aidl
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
#include <android/content/res>
#include <android/graphics>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace view {
class IDisplayWindowListenerDelegator;

class IDisplayWindowListener : public ::ndk::ICInterface {
public:
  typedef IDisplayWindowListenerDelegator DefaultDelegator;
  static const char* descriptor;
  IDisplayWindowListener();
  virtual ~IDisplayWindowListener();

  static constexpr uint32_t TRANSACTION_onDisplayAdded = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onDisplayConfigurationChanged = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onDisplayRemoved = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onFixedRotationStarted = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_onFixedRotationFinished = FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_onKeepClearAreasChanged = FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_onDesktopModeEligibleChanged = FIRST_CALL_TRANSACTION + 6;

  static std::shared_ptr<IDisplayWindowListener> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IDisplayWindowListener>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IDisplayWindowListener>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IDisplayWindowListener>& impl);
  static const std::shared_ptr<IDisplayWindowListener>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus onDisplayAdded(int32_t in_displayId) = 0;
  virtual ::ndk::ScopedAStatus onDisplayConfigurationChanged(int32_t in_displayId, const ::aidl::android::content::res::Configuration& in_newConfig) = 0;
  virtual ::ndk::ScopedAStatus onDisplayRemoved(int32_t in_displayId) = 0;
  virtual ::ndk::ScopedAStatus onFixedRotationStarted(int32_t in_displayId, int32_t in_newRotation) = 0;
  virtual ::ndk::ScopedAStatus onFixedRotationFinished(int32_t in_displayId) = 0;
  virtual ::ndk::ScopedAStatus onKeepClearAreasChanged(int32_t in_displayId, const std::vector<::aidl::android::graphics::Rect>& in_restricted, const std::vector<::aidl::android::graphics::Rect>& in_unrestricted) = 0;
  virtual ::ndk::ScopedAStatus onDesktopModeEligibleChanged(int32_t in_displayId) = 0;
private:
  static std::shared_ptr<IDisplayWindowListener> default_impl;
};
class IDisplayWindowListenerDefault : public IDisplayWindowListener {
public:
  ::ndk::ScopedAStatus onDisplayAdded(int32_t in_displayId) override;
  ::ndk::ScopedAStatus onDisplayConfigurationChanged(int32_t in_displayId, const ::aidl::android::content::res::Configuration& in_newConfig) override;
  ::ndk::ScopedAStatus onDisplayRemoved(int32_t in_displayId) override;
  ::ndk::ScopedAStatus onFixedRotationStarted(int32_t in_displayId, int32_t in_newRotation) override;
  ::ndk::ScopedAStatus onFixedRotationFinished(int32_t in_displayId) override;
  ::ndk::ScopedAStatus onKeepClearAreasChanged(int32_t in_displayId, const std::vector<::aidl::android::graphics::Rect>& in_restricted, const std::vector<::aidl::android::graphics::Rect>& in_unrestricted) override;
  ::ndk::ScopedAStatus onDesktopModeEligibleChanged(int32_t in_displayId) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace view
}  // namespace android
}  // namespace aidl
