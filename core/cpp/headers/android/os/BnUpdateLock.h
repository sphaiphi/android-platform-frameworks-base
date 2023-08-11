#ifndef AIDL_GENERATED_ANDROID_OS_BN_UPDATE_LOCK_H_
#define AIDL_GENERATED_ANDROID_OS_BN_UPDATE_LOCK_H_

#include <binder/IInterface.h>
#include <android/os/IUpdateLock.h>

namespace android {

namespace os {

class BnUpdateLock : public ::android::BnInterface<IUpdateLock> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnUpdateLock

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_UPDATE_LOCK_H_
