#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_I_BIOMETRIC_CONFIRM_DEVICE_CREDENTIAL_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_I_BIOMETRIC_CONFIRM_DEVICE_CREDENTIAL_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

namespace biometrics {

class IBiometricConfirmDeviceCredentialCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(BiometricConfirmDeviceCredentialCallback)
  virtual ::android::binder::Status cancel() = 0;
};  // class IBiometricConfirmDeviceCredentialCallback

class IBiometricConfirmDeviceCredentialCallbackDefault : public IBiometricConfirmDeviceCredentialCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status cancel() override;

};

}  // namespace biometrics

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_I_BIOMETRIC_CONFIRM_DEVICE_CREDENTIAL_CALLBACK_H_
