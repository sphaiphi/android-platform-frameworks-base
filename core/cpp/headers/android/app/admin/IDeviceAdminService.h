#ifndef AIDL_GENERATED_ANDROID_APP_ADMIN_I_DEVICE_ADMIN_SERVICE_H_
#define AIDL_GENERATED_ANDROID_APP_ADMIN_I_DEVICE_ADMIN_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

namespace admin {

class IDeviceAdminService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DeviceAdminService)
};  // class IDeviceAdminService

class IDeviceAdminServiceDefault : public IDeviceAdminService {
public:
  ::android::IBinder* onAsBinder() override;
  
};

}  // namespace admin

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_ADMIN_I_DEVICE_ADMIN_SERVICE_H_
