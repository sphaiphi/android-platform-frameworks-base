#ifndef AIDL_GENERATED_ANDROID_APP_BACKUP_I_FULL_BACKUP_RESTORE_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_APP_BACKUP_I_FULL_BACKUP_RESTORE_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

namespace backup {

class IFullBackupRestoreObserver : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FullBackupRestoreObserver)
  virtual ::android::binder::Status onStartBackup() = 0;
  virtual ::android::binder::Status onBackupPackage(const ::android::String16& name) = 0;
  virtual ::android::binder::Status onEndBackup() = 0;
  virtual ::android::binder::Status onStartRestore() = 0;
  virtual ::android::binder::Status onRestorePackage(const ::android::String16& name) = 0;
  virtual ::android::binder::Status onEndRestore() = 0;
  virtual ::android::binder::Status onTimeout() = 0;
};  // class IFullBackupRestoreObserver

class IFullBackupRestoreObserverDefault : public IFullBackupRestoreObserver {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onStartBackup() override;
  ::android::binder::Status onBackupPackage(const ::android::String16& name) override;
  ::android::binder::Status onEndBackup() override;
  ::android::binder::Status onStartRestore() override;
  ::android::binder::Status onRestorePackage(const ::android::String16& name) override;
  ::android::binder::Status onEndRestore() override;
  ::android::binder::Status onTimeout() override;

};

}  // namespace backup

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BACKUP_I_FULL_BACKUP_RESTORE_OBSERVER_H_
