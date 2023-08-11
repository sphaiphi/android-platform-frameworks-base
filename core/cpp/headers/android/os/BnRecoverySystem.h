#ifndef AIDL_GENERATED_ANDROID_OS_BN_RECOVERY_SYSTEM_H_
#define AIDL_GENERATED_ANDROID_OS_BN_RECOVERY_SYSTEM_H_

#include <binder/IInterface.h>
#include <android/os/IRecoverySystem.h>

namespace android {

namespace os {

class BnRecoverySystem : public ::android::BnInterface<IRecoverySystem> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnRecoverySystem

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_RECOVERY_SYSTEM_H_
