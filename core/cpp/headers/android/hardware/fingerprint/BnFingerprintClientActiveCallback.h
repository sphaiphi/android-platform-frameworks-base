#ifndef AIDL_GENERATED_ANDROID_HARDWARE_FINGERPRINT_BN_FINGERPRINT_CLIENT_ACTIVE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_FINGERPRINT_BN_FINGERPRINT_CLIENT_ACTIVE_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/hardware/fingerprint/IFingerprintClientActiveCallback.h>

namespace android {

namespace hardware {

namespace fingerprint {

class BnFingerprintClientActiveCallback : public ::android::BnInterface<IFingerprintClientActiveCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnFingerprintClientActiveCallback

}  // namespace fingerprint

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_FINGERPRINT_BN_FINGERPRINT_CLIENT_ACTIVE_CALLBACK_H_
