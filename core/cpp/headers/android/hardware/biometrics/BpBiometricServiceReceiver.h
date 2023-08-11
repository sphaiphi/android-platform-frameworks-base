#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BP_BIOMETRIC_SERVICE_RECEIVER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BP_BIOMETRIC_SERVICE_RECEIVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/biometrics/IBiometricServiceReceiver.h>

namespace android {

namespace hardware {

namespace biometrics {

class BpBiometricServiceReceiver : public ::android::BpInterface<IBiometricServiceReceiver> {
public:
  explicit BpBiometricServiceReceiver(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpBiometricServiceReceiver() = default;
  ::android::binder::Status onAuthenticationSucceeded() override;
  ::android::binder::Status onAuthenticationFailed() override;
  ::android::binder::Status onError(int32_t error, const ::android::String16& message) override;
  ::android::binder::Status onAcquired(int32_t acquiredInfo, const ::android::String16& message) override;
  ::android::binder::Status onDialogDismissed(int32_t reason) override;
};  // class BpBiometricServiceReceiver

}  // namespace biometrics

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BP_BIOMETRIC_SERVICE_RECEIVER_H_
