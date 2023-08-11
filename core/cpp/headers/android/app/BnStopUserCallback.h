#ifndef AIDL_GENERATED_ANDROID_APP_BN_STOP_USER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_BN_STOP_USER_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/app/IStopUserCallback.h>

namespace android {

namespace app {

class BnStopUserCallback : public ::android::BnInterface<IStopUserCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnStopUserCallback

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BN_STOP_USER_CALLBACK_H_
