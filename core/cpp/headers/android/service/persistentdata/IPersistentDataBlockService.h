#ifndef AIDL_GENERATED_ANDROID_SERVICE_PERSISTENTDATA_I_PERSISTENT_DATA_BLOCK_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_PERSISTENTDATA_I_PERSISTENT_DATA_BLOCK_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace service {

namespace persistentdata {

class IPersistentDataBlockService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PersistentDataBlockService)
  virtual ::android::binder::Status write(const ::std::vector<uint8_t>& data, int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status read(::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status wipe() = 0;
  virtual ::android::binder::Status getDataBlockSize(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status getMaximumDataBlockSize(int64_t* _aidl_return) = 0;
  virtual ::android::binder::Status setOemUnlockEnabled(bool enabled) = 0;
  virtual ::android::binder::Status getOemUnlockEnabled(bool* _aidl_return) = 0;
  virtual ::android::binder::Status getFlashLockState(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status hasFrpCredentialHandle(bool* _aidl_return) = 0;
};  // class IPersistentDataBlockService

class IPersistentDataBlockServiceDefault : public IPersistentDataBlockService {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status write(const ::std::vector<uint8_t>& data, int32_t* _aidl_return) override;
  ::android::binder::Status read(::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status wipe() override;
  ::android::binder::Status getDataBlockSize(int32_t* _aidl_return) override;
  ::android::binder::Status getMaximumDataBlockSize(int64_t* _aidl_return) override;
  ::android::binder::Status setOemUnlockEnabled(bool enabled) override;
  ::android::binder::Status getOemUnlockEnabled(bool* _aidl_return) override;
  ::android::binder::Status getFlashLockState(int32_t* _aidl_return) override;
  ::android::binder::Status hasFrpCredentialHandle(bool* _aidl_return) override;

};

}  // namespace persistentdata

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_PERSISTENTDATA_I_PERSISTENT_DATA_BLOCK_SERVICE_H_
