#ifndef AIDL_GENERATED_ANDROID_APP_BP_STOP_USER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_BP_STOP_USER_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/IStopUserCallback.h>

namespace android {

namespace app {

class BpStopUserCallback : public ::android::BpInterface<IStopUserCallback> {
public:
  explicit BpStopUserCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpStopUserCallback() = default;
  ::android::binder::Status userStopped(int32_t userId) override;
  ::android::binder::Status userStopAborted(int32_t userId) override;
};  // class BpStopUserCallback

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BP_STOP_USER_CALLBACK_H_
