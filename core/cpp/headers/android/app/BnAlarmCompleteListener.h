#ifndef AIDL_GENERATED_ANDROID_APP_BN_ALARM_COMPLETE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_APP_BN_ALARM_COMPLETE_LISTENER_H_

#include <binder/IInterface.h>
#include <android/app/IAlarmCompleteListener.h>

namespace android {

namespace app {

class BnAlarmCompleteListener : public ::android::BnInterface<IAlarmCompleteListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnAlarmCompleteListener

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BN_ALARM_COMPLETE_LISTENER_H_
