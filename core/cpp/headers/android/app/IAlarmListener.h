#ifndef AIDL_GENERATED_ANDROID_APP_I_ALARM_LISTENER_H_
#define AIDL_GENERATED_ANDROID_APP_I_ALARM_LISTENER_H_

#include <android/app/IAlarmCompleteListener.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

class IAlarmListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AlarmListener)
  virtual ::android::binder::Status doAlarm(const ::android::sp<::android::app::IAlarmCompleteListener>& callback) = 0;
};  // class IAlarmListener

class IAlarmListenerDefault : public IAlarmListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status doAlarm(const ::android::sp<::android::app::IAlarmCompleteListener>& callback) override;

};

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_I_ALARM_LISTENER_H_
