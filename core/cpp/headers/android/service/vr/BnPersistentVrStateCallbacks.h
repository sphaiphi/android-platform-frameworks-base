#ifndef AIDL_GENERATED_ANDROID_SERVICE_VR_BN_PERSISTENT_VR_STATE_CALLBACKS_H_
#define AIDL_GENERATED_ANDROID_SERVICE_VR_BN_PERSISTENT_VR_STATE_CALLBACKS_H_

#include <binder/IInterface.h>
#include <android/service/vr/IPersistentVrStateCallbacks.h>

namespace android {

namespace service {

namespace vr {

class BnPersistentVrStateCallbacks : public ::android::BnInterface<IPersistentVrStateCallbacks> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnPersistentVrStateCallbacks

}  // namespace vr

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_VR_BN_PERSISTENT_VR_STATE_CALLBACKS_H_
