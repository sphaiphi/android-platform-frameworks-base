#ifndef AIDL_GENERATED_ANDROID_HARDWARE_FINGERPRINT_I_FINGERPRINT_CLIENT_ACTIVE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_FINGERPRINT_I_FINGERPRINT_CLIENT_ACTIVE_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

namespace fingerprint {

class IFingerprintClientActiveCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FingerprintClientActiveCallback)
  virtual ::android::binder::Status onClientActiveChanged(bool isActive) = 0;
};  // class IFingerprintClientActiveCallback

class IFingerprintClientActiveCallbackDefault : public IFingerprintClientActiveCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onClientActiveChanged(bool isActive) override;

};

}  // namespace fingerprint

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_FINGERPRINT_I_FINGERPRINT_CLIENT_ACTIVE_CALLBACK_H_
