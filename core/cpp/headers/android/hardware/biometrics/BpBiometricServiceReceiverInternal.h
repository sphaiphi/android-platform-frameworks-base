#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BP_BIOMETRIC_SERVICE_RECEIVER_INTERNAL_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BP_BIOMETRIC_SERVICE_RECEIVER_INTERNAL_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/biometrics/IBiometricServiceReceiverInternal.h>

namespace android {

namespace hardware {

namespace biometrics {

class BpBiometricServiceReceiverInternal : public ::android::BpInterface<IBiometricServiceReceiverInternal> {
public:
  explicit BpBiometricServiceReceiverInternal(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpBiometricServiceReceiverInternal() = default;
  ::android::binder::Status onAuthenticationSucceeded(bool requireConfirmation, const ::std::vector<uint8_t>& token) override;
  ::android::binder::Status onAuthenticationFailed(int32_t cookie, bool requireConfirmation) override;
  ::android::binder::Status onError(int32_t cookie, int32_t error, const ::android::String16& message) override;
  ::android::binder::Status onAcquired(int32_t acquiredInfo, const ::android::String16& message) override;
  ::android::binder::Status onDialogDismissed(int32_t reason) override;
  ::android::binder::Status onTryAgainPressed() override;
};  // class BpBiometricServiceReceiverInternal

}  // namespace biometrics

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_BP_BIOMETRIC_SERVICE_RECEIVER_INTERNAL_H_
