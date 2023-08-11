#ifndef AIDL_GENERATED_ANDROID_OS_BN_EXTERNAL_VIBRATOR_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_BN_EXTERNAL_VIBRATOR_SERVICE_H_

#include <binder/IInterface.h>
#include <android/os/IExternalVibratorService.h>

namespace android {

namespace os {

class BnExternalVibratorService : public ::android::BnInterface<IExternalVibratorService> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnExternalVibratorService

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_EXTERNAL_VIBRATOR_SERVICE_H_
