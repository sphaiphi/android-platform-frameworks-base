#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_I_BIOMETRIC_SERVICE_LOCKOUT_RESET_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_I_BIOMETRIC_SERVICE_LOCKOUT_RESET_CALLBACK_H_

#include <android/os/IRemoteCallback.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

namespace biometrics {

class IBiometricServiceLockoutResetCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(BiometricServiceLockoutResetCallback)
  virtual ::android::binder::Status onLockoutReset(int64_t deviceId, const ::android::sp<::android::os::IRemoteCallback>& callback) = 0;
};  // class IBiometricServiceLockoutResetCallback

class IBiometricServiceLockoutResetCallbackDefault : public IBiometricServiceLockoutResetCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onLockoutReset(int64_t deviceId, const ::android::sp<::android::os::IRemoteCallback>& callback) override;

};

}  // namespace biometrics

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_I_BIOMETRIC_SERVICE_LOCKOUT_RESET_CALLBACK_H_
