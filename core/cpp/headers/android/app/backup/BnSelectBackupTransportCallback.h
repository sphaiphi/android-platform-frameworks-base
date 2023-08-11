#ifndef AIDL_GENERATED_ANDROID_APP_BACKUP_BN_SELECT_BACKUP_TRANSPORT_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_BACKUP_BN_SELECT_BACKUP_TRANSPORT_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/app/backup/ISelectBackupTransportCallback.h>

namespace android {

namespace app {

namespace backup {

class BnSelectBackupTransportCallback : public ::android::BnInterface<ISelectBackupTransportCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnSelectBackupTransportCallback

}  // namespace backup

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BACKUP_BN_SELECT_BACKUP_TRANSPORT_CALLBACK_H_
