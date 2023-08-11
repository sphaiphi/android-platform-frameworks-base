#ifndef AIDL_GENERATED_ANDROID_APP_ADMIN_BN_START_INSTALLING_UPDATE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_ADMIN_BN_START_INSTALLING_UPDATE_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/app/admin/StartInstallingUpdateCallback.h>

namespace android {

namespace app {

namespace admin {

class BnStartInstallingUpdateCallback : public ::android::BnInterface<IStartInstallingUpdateCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnStartInstallingUpdateCallback

}  // namespace admin

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_ADMIN_BN_START_INSTALLING_UPDATE_CALLBACK_H_
