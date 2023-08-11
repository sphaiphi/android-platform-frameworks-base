#ifndef AIDL_GENERATED_ANDROID_APP_BN_ALARM_LISTENER_H_
#define AIDL_GENERATED_ANDROID_APP_BN_ALARM_LISTENER_H_

#include <binder/IInterface.h>
#include <android/app/IAlarmListener.h>

namespace android {

namespace app {

class BnAlarmListener : public ::android::BnInterface<IAlarmListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnAlarmListener

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BN_ALARM_LISTENER_H_
