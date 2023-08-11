#ifndef AIDL_GENERATED_ANDROID_OS_I_MAINTENANCE_ACTIVITY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_I_MAINTENANCE_ACTIVITY_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

class IMaintenanceActivityListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(MaintenanceActivityListener)
  virtual ::android::binder::Status onMaintenanceActivityChanged(bool active) = 0;
};  // class IMaintenanceActivityListener

class IMaintenanceActivityListenerDefault : public IMaintenanceActivityListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onMaintenanceActivityChanged(bool active) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_MAINTENANCE_ACTIVITY_LISTENER_H_
