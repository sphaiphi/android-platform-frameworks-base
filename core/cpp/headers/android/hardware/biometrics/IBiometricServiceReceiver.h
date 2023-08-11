#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_I_BIOMETRIC_SERVICE_RECEIVER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_I_BIOMETRIC_SERVICE_RECEIVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

namespace biometrics {

class IBiometricServiceReceiver : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(BiometricServiceReceiver)
  virtual ::android::binder::Status onAuthenticationSucceeded() = 0;
  virtual ::android::binder::Status onAuthenticationFailed() = 0;
  virtual ::android::binder::Status onError(int32_t error, const ::android::String16& message) = 0;
  virtual ::android::binder::Status onAcquired(int32_t acquiredInfo, const ::android::String16& message) = 0;
  virtual ::android::binder::Status onDialogDismissed(int32_t reason) = 0;
};  // class IBiometricServiceReceiver

class IBiometricServiceReceiverDefault : public IBiometricServiceReceiver {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onAuthenticationSucceeded() override;
  ::android::binder::Status onAuthenticationFailed() override;
  ::android::binder::Status onError(int32_t error, const ::android::String16& message) override;
  ::android::binder::Status onAcquired(int32_t acquiredInfo, const ::android::String16& message) override;
  ::android::binder::Status onDialogDismissed(int32_t reason) override;

};

}  // namespace biometrics

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BIOMETRICS_I_BIOMETRIC_SERVICE_RECEIVER_H_
