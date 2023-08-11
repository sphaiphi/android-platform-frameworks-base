#ifndef AIDL_GENERATED_ANDROID_APP_I_USER_SWITCH_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_APP_I_USER_SWITCH_OBSERVER_H_

#include <android/os/IRemoteCallback.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

class IUserSwitchObserver : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(UserSwitchObserver)
  virtual ::android::binder::Status onUserSwitching(int32_t newUserId, const ::android::sp<::android::os::IRemoteCallback>& reply) = 0;
  virtual ::android::binder::Status onUserSwitchComplete(int32_t newUserId) = 0;
  virtual ::android::binder::Status onForegroundProfileSwitch(int32_t newProfileId) = 0;
  virtual ::android::binder::Status onLockedBootComplete(int32_t newUserId) = 0;
};  // class IUserSwitchObserver

class IUserSwitchObserverDefault : public IUserSwitchObserver {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onUserSwitching(int32_t newUserId, const ::android::sp<::android::os::IRemoteCallback>& reply) override;
  ::android::binder::Status onUserSwitchComplete(int32_t newUserId) override;
  ::android::binder::Status onForegroundProfileSwitch(int32_t newProfileId) override;
  ::android::binder::Status onLockedBootComplete(int32_t newUserId) override;

};

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_I_USER_SWITCH_OBSERVER_H_
