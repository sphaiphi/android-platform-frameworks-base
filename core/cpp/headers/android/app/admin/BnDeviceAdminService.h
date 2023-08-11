#ifndef AIDL_GENERATED_ANDROID_APP_ADMIN_BN_DEVICE_ADMIN_SERVICE_H_
#define AIDL_GENERATED_ANDROID_APP_ADMIN_BN_DEVICE_ADMIN_SERVICE_H_

#include <binder/IInterface.h>
#include <android/app/admin/IDeviceAdminService.h>

namespace android {

namespace app {

namespace admin {

class BnDeviceAdminService : public ::android::BnInterface<IDeviceAdminService> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnDeviceAdminService

}  // namespace admin

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_ADMIN_BN_DEVICE_ADMIN_SERVICE_H_
