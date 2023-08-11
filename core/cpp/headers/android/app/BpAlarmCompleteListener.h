#ifndef AIDL_GENERATED_ANDROID_APP_BP_ALARM_COMPLETE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_APP_BP_ALARM_COMPLETE_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/IAlarmCompleteListener.h>

namespace android {

namespace app {

class BpAlarmCompleteListener : public ::android::BpInterface<IAlarmCompleteListener> {
public:
  explicit BpAlarmCompleteListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAlarmCompleteListener() = default;
  ::android::binder::Status alarmComplete(const ::android::sp<::android::IBinder>& who) override;
};  // class BpAlarmCompleteListener

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BP_ALARM_COMPLETE_LISTENER_H_
