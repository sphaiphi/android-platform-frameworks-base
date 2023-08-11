#ifndef AIDL_GENERATED_ANDROID_OS_BN_PERMISSION_CONTROLLER_H_
#define AIDL_GENERATED_ANDROID_OS_BN_PERMISSION_CONTROLLER_H_

#include <binder/IInterface.h>
#include <android/os/IPermissionController.h>

namespace android {

namespace os {

class BnPermissionController : public ::android::BnInterface<IPermissionController> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnPermissionController

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_PERMISSION_CONTROLLER_H_
