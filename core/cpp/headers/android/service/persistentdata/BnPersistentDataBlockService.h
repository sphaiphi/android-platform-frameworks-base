#ifndef AIDL_GENERATED_ANDROID_SERVICE_PERSISTENTDATA_BN_PERSISTENT_DATA_BLOCK_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_PERSISTENTDATA_BN_PERSISTENT_DATA_BLOCK_SERVICE_H_

#include <binder/IInterface.h>
#include <android/service/persistentdata/IPersistentDataBlockService.h>

namespace android {

namespace service {

namespace persistentdata {

class BnPersistentDataBlockService : public ::android::BnInterface<IPersistentDataBlockService> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnPersistentDataBlockService

}  // namespace persistentdata

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_PERSISTENTDATA_BN_PERSISTENT_DATA_BLOCK_SERVICE_H_
