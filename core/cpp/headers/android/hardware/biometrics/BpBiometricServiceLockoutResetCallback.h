#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BP_BIOMETRIC_SERVICE_LOCKOUT_RESET_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BP_BIOMETRIC_SERVICE_LOCKOUT_RESET_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/biometrics/IBiometricServiceLockoutResetCallback.h>

namespace android {

namespace hardware {

namespace biometrics {

class BpBiometricServiceLockoutResetCallback : public ::android::BpInterface<IBiometricServiceLockoutResetCallback> {
public:
  explicit BpBiometricServiceLockoutResetCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpBiometricServiceLockoutResetCallback() = default;
  ::android::binder::Status onLockoutReset(int64_t deviceId, const ::android::sp<::android::os::IRemoteCallback>& callback) override;
};  // class BpBiometricServiceLockoutResetCallback

}  // namespace biometrics

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BP_BIOMETRIC_SERVICE_LOCKOUT_RESET_CALLBACK_H_
