#ifndef AIDL_GENERATED_ANDROID_HARDWARE_FINGERPRINT_BP_FINGERPRINT_CLIENT_ACTIVE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_FINGERPRINT_BP_FINGERPRINT_CLIENT_ACTIVE_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/fingerprint/IFingerprintClientActiveCallback.h>

namespace android {

namespace hardware {

namespace fingerprint {

class BpFingerprintClientActiveCallback : public ::android::BpInterface<IFingerprintClientActiveCallback> {
public:
  explicit BpFingerprintClientActiveCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpFingerprintClientActiveCallback() = default;
  ::android::binder::Status onClientActiveChanged(bool isActive) override;
};  // class BpFingerprintClientActiveCallback

}  // namespace fingerprint

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_FINGERPRINT_BP_FINGERPRINT_CLIENT_ACTIVE_CALLBACK_H_
