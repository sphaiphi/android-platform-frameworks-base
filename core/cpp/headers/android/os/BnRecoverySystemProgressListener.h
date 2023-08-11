#ifndef AIDL_GENERATED_ANDROID_OS_BN_RECOVERY_SYSTEM_PROGRESS_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_BN_RECOVERY_SYSTEM_PROGRESS_LISTENER_H_

#include <binder/IInterface.h>
#include <android/os/IRecoverySystemProgressListener.h>

namespace android {

namespace os {

class BnRecoverySystemProgressListener : public ::android::BnInterface<IRecoverySystemProgressListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnRecoverySystemProgressListener

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_RECOVERY_SYSTEM_PROGRESS_LISTENER_H_
