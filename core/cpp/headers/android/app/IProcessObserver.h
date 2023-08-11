#ifndef AIDL_GENERATED_ANDROID_APP_I_PROCESS_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_APP_I_PROCESS_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

class IProcessObserver : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(ProcessObserver)
  virtual ::android::binder::Status onForegroundActivitiesChanged(int32_t pid, int32_t uid, bool foregroundActivities) = 0;
  virtual ::android::binder::Status onForegroundServicesChanged(int32_t pid, int32_t uid, int32_t serviceTypes) = 0;
  virtual ::android::binder::Status onProcessDied(int32_t pid, int32_t uid) = 0;
};  // class IProcessObserver

class IProcessObserverDefault : public IProcessObserver {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onForegroundActivitiesChanged(int32_t pid, int32_t uid, bool foregroundActivities) override;
  ::android::binder::Status onForegroundServicesChanged(int32_t pid, int32_t uid, int32_t serviceTypes) override;
  ::android::binder::Status onProcessDied(int32_t pid, int32_t uid) override;

};

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_I_PROCESS_OBSERVER_H_
