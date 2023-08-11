#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BP_BIOMETRIC_CONFIRM_DEVICE_CREDENTIAL_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BP_BIOMETRIC_CONFIRM_DEVICE_CREDENTIAL_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/biometrics/IBiometricConfirmDeviceCredentialCallback.h>

namespace android {

namespace hardware {

namespace biometrics {

class BpBiometricConfirmDeviceCredentialCallback : public ::android::BpInterface<IBiometricConfirmDeviceCredentialCallback> {
public:
  explicit BpBiometricConfirmDeviceCredentialCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpBiometricConfirmDeviceCredentialCallback() = default;
  ::android::binder::Status cancel() override;
};  // class BpBiometricConfirmDeviceCredentialCallback

}  // namespace biometrics

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BP_BIOMETRIC_CONFIRM_DEVICE_CREDENTIAL_CALLBACK_H_
