#ifndef AIDL_GENERATED_ANDROID_SERVICE_OEMLOCK_I_OEM_LOCK_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_OEMLOCK_I_OEM_LOCK_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace service {

namespace oemlock {

class IOemLockService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(OemLockService)
  virtual ::android::binder::Status getLockName(::android::String16* _aidl_return) = 0;
  virtual ::android::binder::Status setOemUnlockAllowedByCarrier(bool allowed, const ::std::vector<uint8_t>& signature) = 0;
  virtual ::android::binder::Status isOemUnlockAllowedByCarrier(bool* _aidl_return) = 0;
  virtual ::android::binder::Status setOemUnlockAllowedByUser(bool allowed) = 0;
  virtual ::android::binder::Status isOemUnlockAllowedByUser(bool* _aidl_return) = 0;
  virtual ::android::binder::Status isOemUnlockAllowed(bool* _aidl_return) = 0;
  virtual ::android::binder::Status isDeviceOemUnlocked(bool* _aidl_return) = 0;
};  // class IOemLockService

class IOemLockServiceDefault : public IOemLockService {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status getLockName(::android::String16* _aidl_return) override;
  ::android::binder::Status setOemUnlockAllowedByCarrier(bool allowed, const ::std::vector<uint8_t>& signature) override;
  ::android::binder::Status isOemUnlockAllowedByCarrier(bool* _aidl_return) override;
  ::android::binder::Status setOemUnlockAllowedByUser(bool allowed) override;
  ::android::binder::Status isOemUnlockAllowedByUser(bool* _aidl_return) override;
  ::android::binder::Status isOemUnlockAllowed(bool* _aidl_return) override;
  ::android::binder::Status isDeviceOemUnlocked(bool* _aidl_return) override;

};

}  // namespace oemlock

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_OEMLOCK_I_OEM_LOCK_SERVICE_H_
