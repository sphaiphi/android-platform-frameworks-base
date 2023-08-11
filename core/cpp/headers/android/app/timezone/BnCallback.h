#ifndef AIDL_GENERATED_ANDROID_APP_TIMEZONE_BN_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_TIMEZONE_BN_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/app/timezone/ICallback.h>

namespace android {

namespace app {

namespace timezone {

class BnCallback : public ::android::BnInterface<ICallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnCallback

}  // namespace timezone

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_TIMEZONE_BN_CALLBACK_H_
