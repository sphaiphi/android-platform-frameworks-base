#ifndef AIDL_GENERATED_ANDROID_SERVICE_PERSISTENTDATA_BP_PERSISTENT_DATA_BLOCK_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_PERSISTENTDATA_BP_PERSISTENT_DATA_BLOCK_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/persistentdata/IPersistentDataBlockService.h>

namespace android {

namespace service {

namespace persistentdata {

class BpPersistentDataBlockService : public ::android::BpInterface<IPersistentDataBlockService> {
public:
  explicit BpPersistentDataBlockService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPersistentDataBlockService() = default;
  ::android::binder::Status write(const ::std::vector<uint8_t>& data, int32_t* _aidl_return) override;
  ::android::binder::Status read(::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status wipe() override;
  ::android::binder::Status getDataBlockSize(int32_t* _aidl_return) override;
  ::android::binder::Status getMaximumDataBlockSize(int64_t* _aidl_return) override;
  ::android::binder::Status setOemUnlockEnabled(bool enabled) override;
  ::android::binder::Status getOemUnlockEnabled(bool* _aidl_return) override;
  ::android::binder::Status getFlashLockState(int32_t* _aidl_return) override;
  ::android::binder::Status hasFrpCredentialHandle(bool* _aidl_return) override;
};  // class BpPersistentDataBlockService

}  // namespace persistentdata

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_PERSISTENTDATA_BP_PERSISTENT_DATA_BLOCK_SERVICE_H_
