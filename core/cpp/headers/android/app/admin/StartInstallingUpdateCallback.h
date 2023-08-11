#ifndef AIDL_GENERATED_ANDROID_APP_ADMIN_I_START_INSTALLING_UPDATE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_ADMIN_I_START_INSTALLING_UPDATE_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

namespace admin {

class IStartInstallingUpdateCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(StartInstallingUpdateCallback)
  virtual ::android::binder::Status onStartInstallingUpdateError(int32_t errorCode, const ::android::String16& errorMessage) = 0;
};  // class IStartInstallingUpdateCallback

class IStartInstallingUpdateCallbackDefault : public IStartInstallingUpdateCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onStartInstallingUpdateError(int32_t errorCode, const ::android::String16& errorMessage) override;

};

}  // namespace admin

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_ADMIN_I_START_INSTALLING_UPDATE_CALLBACK_H_
