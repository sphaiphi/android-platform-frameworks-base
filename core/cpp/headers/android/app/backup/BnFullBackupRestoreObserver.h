#ifndef AIDL_GENERATED_ANDROID_APP_BACKUP_BN_FULL_BACKUP_RESTORE_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_APP_BACKUP_BN_FULL_BACKUP_RESTORE_OBSERVER_H_

#include <binder/IInterface.h>
#include <android/app/backup/IFullBackupRestoreObserver.h>

namespace android {

namespace app {

namespace backup {

class BnFullBackupRestoreObserver : public ::android::BnInterface<IFullBackupRestoreObserver> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnFullBackupRestoreObserver

}  // namespace backup

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BACKUP_BN_FULL_BACKUP_RESTORE_OBSERVER_H_
