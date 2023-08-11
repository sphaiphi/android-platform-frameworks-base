#ifndef AIDL_GENERATED_ANDROID_OS_BN_EXTERNAL_VIBRATION_CONTROLLER_H_
#define AIDL_GENERATED_ANDROID_OS_BN_EXTERNAL_VIBRATION_CONTROLLER_H_

#include <binder/IInterface.h>
#include <android/os/IExternalVibrationController.h>

namespace android {

namespace os {

class BnExternalVibrationController : public ::android::BnInterface<IExternalVibrationController> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnExternalVibrationController

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_EXTERNAL_VIBRATION_CONTROLLER_H_
