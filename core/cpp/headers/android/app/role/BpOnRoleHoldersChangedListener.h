#ifndef AIDL_GENERATED_ANDROID_APP_ROLE_BP_ON_ROLE_HOLDERS_CHANGED_LISTENER_H_
#define AIDL_GENERATED_ANDROID_APP_ROLE_BP_ON_ROLE_HOLDERS_CHANGED_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/role/IOnRoleHoldersChangedListener.h>

namespace android {

namespace app {

namespace role {

class BpOnRoleHoldersChangedListener : public ::android::BpInterface<IOnRoleHoldersChangedListener> {
public:
  explicit BpOnRoleHoldersChangedListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpOnRoleHoldersChangedListener() = default;
  ::android::binder::Status onRoleHoldersChanged(const ::android::String16& roleName, int32_t userId) override;
};  // class BpOnRoleHoldersChangedListener

}  // namespace role

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_ROLE_BP_ON_ROLE_HOLDERS_CHANGED_LISTENER_H_
