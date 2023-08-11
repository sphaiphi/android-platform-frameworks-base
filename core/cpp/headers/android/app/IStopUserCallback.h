#ifndef AIDL_GENERATED_ANDROID_APP_I_STOP_USER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_I_STOP_USER_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

class IStopUserCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(StopUserCallback)
  virtual ::android::binder::Status userStopped(int32_t userId) = 0;
  virtual ::android::binder::Status userStopAborted(int32_t userId) = 0;
};  // class IStopUserCallback

class IStopUserCallbackDefault : public IStopUserCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status userStopped(int32_t userId) override;
  ::android::binder::Status userStopAborted(int32_t userId) override;

};

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_I_STOP_USER_CALLBACK_H_
