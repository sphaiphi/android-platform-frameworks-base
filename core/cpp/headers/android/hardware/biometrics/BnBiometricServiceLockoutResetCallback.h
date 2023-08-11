#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BN_BIOMETRIC_SERVICE_LOCKOUT_RESET_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BN_BIOMETRIC_SERVICE_LOCKOUT_RESET_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/hardware/biometrics/IBiometricServiceLockoutResetCallback.h>

namespace android {

namespace hardware {

namespace biometrics {

class BnBiometricServiceLockoutResetCallback : public ::android::BnInterface<IBiometricServiceLockoutResetCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnBiometricServiceLockoutResetCallback

}  // namespace biometrics

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BN_BIOMETRIC_SERVICE_LOCKOUT_RESET_CALLBACK_H_
