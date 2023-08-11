#ifndef AIDL_GENERATED_ANDROID_APP_ROLE_I_ON_ROLE_HOLDERS_CHANGED_LISTENER_H_
#define AIDL_GENERATED_ANDROID_APP_ROLE_I_ON_ROLE_HOLDERS_CHANGED_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

namespace role {

class IOnRoleHoldersChangedListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(OnRoleHoldersChangedListener)
  virtual ::android::binder::Status onRoleHoldersChanged(const ::android::String16& roleName, int32_t userId) = 0;
};  // class IOnRoleHoldersChangedListener

class IOnRoleHoldersChangedListenerDefault : public IOnRoleHoldersChangedListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onRoleHoldersChanged(const ::android::String16& roleName, int32_t userId) override;

};

}  // namespace role

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_ROLE_I_ON_ROLE_HOLDERS_CHANGED_LISTENER_H_
