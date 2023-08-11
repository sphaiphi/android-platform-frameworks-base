#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_I_ON_PERMISSIONS_CHANGE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_I_ON_PERMISSIONS_CHANGE_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace content {

namespace pm {

class IOnPermissionsChangeListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(OnPermissionsChangeListener)
  virtual ::android::binder::Status onPermissionsChanged(int32_t uid) = 0;
};  // class IOnPermissionsChangeListener

class IOnPermissionsChangeListenerDefault : public IOnPermissionsChangeListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onPermissionsChanged(int32_t uid) override;

};

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_I_ON_PERMISSIONS_CHANGE_LISTENER_H_
