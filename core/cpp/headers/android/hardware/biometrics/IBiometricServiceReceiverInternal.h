#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_I_BIOMETRIC_SERVICE_RECEIVER_INTERNAL_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_I_BIOMETRIC_SERVICE_RECEIVER_INTERNAL_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace hardware {

namespace biometrics {

class IBiometricServiceReceiverInternal : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(BiometricServiceReceiverInternal)
  virtual ::android::binder::Status onAuthenticationSucceeded(bool requireConfirmation, const ::std::vector<uint8_t>& token) = 0;
  virtual ::android::binder::Status onAuthenticationFailed(int32_t cookie, bool requireConfirmation) = 0;
  virtual ::android::binder::Status onError(int32_t cookie, int32_t error, const ::android::String16& message) = 0;
  virtual ::android::binder::Status onAcquired(int32_t acquiredInfo, const ::android::String16& message) = 0;
  virtual ::android::binder::Status onDialogDismissed(int32_t reason) = 0;
  virtual ::android::binder::Status onTryAgainPressed() = 0;
};  // class IBiometricServiceReceiverInternal

class IBiometricServiceReceiverInternalDefault : public IBiometricServiceReceiverInternal {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onAuthenticationSucceeded(bool requireConfirmation, const ::std::vector<uint8_t>& token) override;
  ::android::binder::Status onAuthenticationFailed(int32_t cookie, bool requireConfirmation) override;
  ::android::binder::Status onError(int32_t cookie, int32_t error, const ::android::String16& message) override;
  ::android::binder::Status onAcquired(int32_t acquiredInfo, const ::android::String16& message) override;
  ::android::binder::Status onDialogDismissed(int32_t reason) override;
  ::android::binder::Status onTryAgainPressed() override;

};

}  // namespace biometrics

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_I_BIOMETRIC_SERVICE_RECEIVER_INTERNAL_H_
