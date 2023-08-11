#ifndef AIDL_GENERATED_ANDROID_OS_BP_MAINTENANCE_ACTIVITY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_BP_MAINTENANCE_ACTIVITY_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/IMaintenanceActivityListener.h>

namespace android {

namespace os {

class BpMaintenanceActivityListener : public ::android::BpInterface<IMaintenanceActivityListener> {
public:
  explicit BpMaintenanceActivityListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpMaintenanceActivityListener() = default;
  ::android::binder::Status onMaintenanceActivityChanged(bool active) override;
};  // class BpMaintenanceActivityListener

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_MAINTENANCE_ACTIVITY_LISTENER_H_
