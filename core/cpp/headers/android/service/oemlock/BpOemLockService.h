#ifndef AIDL_GENERATED_ANDROID_SERVICE_OEMLOCK_BP_OEM_LOCK_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_OEMLOCK_BP_OEM_LOCK_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/oemlock/IOemLockService.h>

namespace android {

namespace service {

namespace oemlock {

class BpOemLockService : public ::android::BpInterface<IOemLockService> {
public:
  explicit BpOemLockService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpOemLockService() = default;
  ::android::binder::Status getLockName(::android::String16* _aidl_return) override;
  ::android::binder::Status setOemUnlockAllowedByCarrier(bool allowed, const ::std::vector<uint8_t>& signature) override;
  ::android::binder::Status isOemUnlockAllowedByCarrier(bool* _aidl_return) override;
  ::android::binder::Status setOemUnlockAllowedByUser(bool allowed) override;
  ::android::binder::Status isOemUnlockAllowedByUser(bool* _aidl_return) override;
  ::android::binder::Status isOemUnlockAllowed(bool* _aidl_return) override;
  ::android::binder::Status isDeviceOemUnlocked(bool* _aidl_return) override;
};  // class BpOemLockService

}  // namespace oemlock

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_OEMLOCK_BP_OEM_LOCK_SERVICE_H_
