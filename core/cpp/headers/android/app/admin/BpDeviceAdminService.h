#ifndef AIDL_GENERATED_ANDROID_APP_ADMIN_BP_DEVICE_ADMIN_SERVICE_H_
#define AIDL_GENERATED_ANDROID_APP_ADMIN_BP_DEVICE_ADMIN_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/admin/IDeviceAdminService.h>

namespace android {

namespace app {

namespace admin {

class BpDeviceAdminService : public ::android::BpInterface<IDeviceAdminService> {
public:
  explicit BpDeviceAdminService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDeviceAdminService() = default;
};  // class BpDeviceAdminService

}  // namespace admin

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_ADMIN_BP_DEVICE_ADMIN_SERVICE_H_
