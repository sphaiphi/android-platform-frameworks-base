#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_BP_ON_PERMISSIONS_CHANGE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_BP_ON_PERMISSIONS_CHANGE_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/content/pm/IOnPermissionsChangeListener.h>

namespace android {

namespace content {

namespace pm {

class BpOnPermissionsChangeListener : public ::android::BpInterface<IOnPermissionsChangeListener> {
public:
  explicit BpOnPermissionsChangeListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpOnPermissionsChangeListener() = default;
  ::android::binder::Status onPermissionsChanged(int32_t uid) override;
};  // class BpOnPermissionsChangeListener

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_BP_ON_PERMISSIONS_CHANGE_LISTENER_H_
