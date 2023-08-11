#ifndef AIDL_GENERATED_ANDROID_APP_BACKUP_BP_FULL_BACKUP_RESTORE_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_APP_BACKUP_BP_FULL_BACKUP_RESTORE_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/backup/IFullBackupRestoreObserver.h>

namespace android {

namespace app {

namespace backup {

class BpFullBackupRestoreObserver : public ::android::BpInterface<IFullBackupRestoreObserver> {
public:
  explicit BpFullBackupRestoreObserver(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpFullBackupRestoreObserver() = default;
  ::android::binder::Status onStartBackup() override;
  ::android::binder::Status onBackupPackage(const ::android::String16& name) override;
  ::android::binder::Status onEndBackup() override;
  ::android::binder::Status onStartRestore() override;
  ::android::binder::Status onRestorePackage(const ::android::String16& name) override;
  ::android::binder::Status onEndRestore() override;
  ::android::binder::Status onTimeout() override;
};  // class BpFullBackupRestoreObserver

}  // namespace backup

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BACKUP_BP_FULL_BACKUP_RESTORE_OBSERVER_H_
