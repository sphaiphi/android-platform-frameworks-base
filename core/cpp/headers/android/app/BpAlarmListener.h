#ifndef AIDL_GENERATED_ANDROID_APP_BP_ALARM_LISTENER_H_
#define AIDL_GENERATED_ANDROID_APP_BP_ALARM_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/IAlarmListener.h>

namespace android {

namespace app {

class BpAlarmListener : public ::android::BpInterface<IAlarmListener> {
public:
  explicit BpAlarmListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAlarmListener() = default;
  ::android::binder::Status doAlarm(const ::android::sp<::android::app::IAlarmCompleteListener>& callback) override;
};  // class BpAlarmListener

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BP_ALARM_LISTENER_H_
