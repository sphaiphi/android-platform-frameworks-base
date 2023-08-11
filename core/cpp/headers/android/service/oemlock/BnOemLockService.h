#ifndef AIDL_GENERATED_ANDROID_SERVICE_OEMLOCK_BN_OEM_LOCK_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_OEMLOCK_BN_OEM_LOCK_SERVICE_H_

#include <binder/IInterface.h>
#include <android/service/oemlock/IOemLockService.h>

namespace android {

namespace service {

namespace oemlock {

class BnOemLockService : public ::android::BnInterface<IOemLockService> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnOemLockService

}  // namespace oemlock

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_OEMLOCK_BN_OEM_LOCK_SERVICE_H_
