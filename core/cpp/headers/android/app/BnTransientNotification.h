#ifndef AIDL_GENERATED_ANDROID_APP_BN_TRANSIENT_NOTIFICATION_H_
#define AIDL_GENERATED_ANDROID_APP_BN_TRANSIENT_NOTIFICATION_H_

#include <binder/IInterface.h>
#include <android/app/ITransientNotification.h>

namespace android {

namespace app {

class BnTransientNotification : public ::android::BnInterface<ITransientNotification> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnTransientNotification

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BN_TRANSIENT_NOTIFICATION_H_
