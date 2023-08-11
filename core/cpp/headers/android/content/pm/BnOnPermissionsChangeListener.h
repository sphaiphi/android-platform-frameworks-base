#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_BN_ON_PERMISSIONS_CHANGE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_BN_ON_PERMISSIONS_CHANGE_LISTENER_H_

#include <binder/IInterface.h>
#include <android/content/pm/IOnPermissionsChangeListener.h>

namespace android {

namespace content {

namespace pm {

class BnOnPermissionsChangeListener : public ::android::BnInterface<IOnPermissionsChangeListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnOnPermissionsChangeListener

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_BN_ON_PERMISSIONS_CHANGE_LISTENER_H_
