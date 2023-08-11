#ifndef AIDL_GENERATED_ANDROID_APP_BP_USER_SWITCH_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_APP_BP_USER_SWITCH_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/IUserSwitchObserver.h>

namespace android {

namespace app {

class BpUserSwitchObserver : public ::android::BpInterface<IUserSwitchObserver> {
public:
  explicit BpUserSwitchObserver(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpUserSwitchObserver() = default;
  ::android::binder::Status onUserSwitching(int32_t newUserId, const ::android::sp<::android::os::IRemoteCallback>& reply) override;
  ::android::binder::Status onUserSwitchComplete(int32_t newUserId) override;
  ::android::binder::Status onForegroundProfileSwitch(int32_t newProfileId) override;
  ::android::binder::Status onLockedBootComplete(int32_t newUserId) override;
};  // class BpUserSwitchObserver

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BP_USER_SWITCH_OBSERVER_H_
