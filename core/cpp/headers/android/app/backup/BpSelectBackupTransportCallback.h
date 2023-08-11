#ifndef AIDL_GENERATED_ANDROID_APP_BACKUP_BP_SELECT_BACKUP_TRANSPORT_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_BACKUP_BP_SELECT_BACKUP_TRANSPORT_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/backup/ISelectBackupTransportCallback.h>

namespace android {

namespace app {

namespace backup {

class BpSelectBackupTransportCallback : public ::android::BpInterface<ISelectBackupTransportCallback> {
public:
  explicit BpSelectBackupTransportCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpSelectBackupTransportCallback() = default;
  ::android::binder::Status onSuccess(const ::android::String16& transportName) override;
  ::android::binder::Status onFailure(int32_t reason) override;
};  // class BpSelectBackupTransportCallback

}  // namespace backup

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BACKUP_BP_SELECT_BACKUP_TRANSPORT_CALLBACK_H_
