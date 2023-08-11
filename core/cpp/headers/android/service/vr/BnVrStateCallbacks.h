#ifndef AIDL_GENERATED_ANDROID_SERVICE_VR_BN_VR_STATE_CALLBACKS_H_
#define AIDL_GENERATED_ANDROID_SERVICE_VR_BN_VR_STATE_CALLBACKS_H_

#include <binder/IInterface.h>
#include <android/service/vr/IVrStateCallbacks.h>

namespace android {

namespace service {

namespace vr {

class BnVrStateCallbacks : public ::android::BnInterface<IVrStateCallbacks> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnVrStateCallbacks

}  // namespace vr

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_VR_BN_VR_STATE_CALLBACKS_H_
