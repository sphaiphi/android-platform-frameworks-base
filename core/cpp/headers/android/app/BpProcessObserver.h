#ifndef AIDL_GENERATED_ANDROID_APP_BP_PROCESS_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_APP_BP_PROCESS_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/IProcessObserver.h>

namespace android {

namespace app {

class BpProcessObserver : public ::android::BpInterface<IProcessObserver> {
public:
  explicit BpProcessObserver(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpProcessObserver() = default;
  ::android::binder::Status onForegroundActivitiesChanged(int32_t pid, int32_t uid, bool foregroundActivities) override;
  ::android::binder::Status onForegroundServicesChanged(int32_t pid, int32_t uid, int32_t serviceTypes) override;
  ::android::binder::Status onProcessDied(int32_t pid, int32_t uid) override;
};  // class BpProcessObserver

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BP_PROCESS_OBSERVER_H_
