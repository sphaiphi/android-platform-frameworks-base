#ifndef AIDL_GENERATED_ANDROID_APP_I_ALARM_COMPLETE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_APP_I_ALARM_COMPLETE_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

class IAlarmCompleteListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AlarmCompleteListener)
  virtual ::android::binder::Status alarmComplete(const ::android::sp<::android::IBinder>& who) = 0;
};  // class IAlarmCompleteListener

class IAlarmCompleteListenerDefault : public IAlarmCompleteListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status alarmComplete(const ::android::sp<::android::IBinder>& who) override;

};

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_I_ALARM_COMPLETE_LISTENER_H_
