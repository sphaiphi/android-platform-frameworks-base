#ifndef AIDL_GENERATED_ANDROID_OS_STORAGE_BN_STORAGE_SHUTDOWN_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_OS_STORAGE_BN_STORAGE_SHUTDOWN_OBSERVER_H_

#include <binder/IInterface.h>
#include <android/os/storage/IStorageShutdownObserver.h>

namespace android {

namespace os {

namespace storage {

class BnStorageShutdownObserver : public ::android::BnInterface<IStorageShutdownObserver> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnStorageShutdownObserver

}  // namespace storage

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_STORAGE_BN_STORAGE_SHUTDOWN_OBSERVER_H_
