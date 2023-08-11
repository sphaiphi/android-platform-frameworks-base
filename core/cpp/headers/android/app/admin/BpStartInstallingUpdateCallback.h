#ifndef AIDL_GENERATED_ANDROID_APP_ADMIN_BP_START_INSTALLING_UPDATE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_ADMIN_BP_START_INSTALLING_UPDATE_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/admin/StartInstallingUpdateCallback.h>

namespace android {

namespace app {

namespace admin {

class BpStartInstallingUpdateCallback : public ::android::BpInterface<IStartInstallingUpdateCallback> {
public:
  explicit BpStartInstallingUpdateCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpStartInstallingUpdateCallback() = default;
  ::android::binder::Status onStartInstallingUpdateError(int32_t errorCode, const ::android::String16& errorMessage) override;
};  // class BpStartInstallingUpdateCallback

}  // namespace admin

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_ADMIN_BP_START_INSTALLING_UPDATE_CALLBACK_H_
