#ifndef AIDL_GENERATED_ANDROID_APP_ROLE_BN_ON_ROLE_HOLDERS_CHANGED_LISTENER_H_
#define AIDL_GENERATED_ANDROID_APP_ROLE_BN_ON_ROLE_HOLDERS_CHANGED_LISTENER_H_

#include <binder/IInterface.h>
#include <android/app/role/IOnRoleHoldersChangedListener.h>

namespace android {

namespace app {

namespace role {

class BnOnRoleHoldersChangedListener : public ::android::BnInterface<IOnRoleHoldersChangedListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnOnRoleHoldersChangedListener

}  // namespace role

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_ROLE_BN_ON_ROLE_HOLDERS_CHANGED_LISTENER_H_
