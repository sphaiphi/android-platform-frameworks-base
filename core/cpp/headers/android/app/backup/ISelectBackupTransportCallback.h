#ifndef AIDL_GENERATED_ANDROID_APP_BACKUP_I_SELECT_BACKUP_TRANSPORT_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_BACKUP_I_SELECT_BACKUP_TRANSPORT_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

namespace backup {

class ISelectBackupTransportCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(SelectBackupTransportCallback)
  virtual ::android::binder::Status onSuccess(const ::android::String16& transportName) = 0;
  virtual ::android::binder::Status onFailure(int32_t reason) = 0;
};  // class ISelectBackupTransportCallback

class ISelectBackupTransportCallbackDefault : public ISelectBackupTransportCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onSuccess(const ::android::String16& transportName) override;
  ::android::binder::Status onFailure(int32_t reason) override;

};

}  // namespace backup

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BACKUP_I_SELECT_BACKUP_TRANSPORT_CALLBACK_H_
