#ifndef AIDL_GENERATED_ANDROID_OS_STORAGE_BN_OBB_ACTION_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_STORAGE_BN_OBB_ACTION_LISTENER_H_

#include <binder/IInterface.h>
#include <android/os/storage/IObbActionListener.h>

namespace android {

namespace os {

namespace storage {

class BnObbActionListener : public ::android::BnInterface<IObbActionListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnObbActionListener

}  // namespace storage

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_STORAGE_BN_OBB_ACTION_LISTENER_H_
