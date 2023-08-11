#ifndef AIDL_GENERATED_ANDROID_OS_I_THERMAL_STATUS_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_I_THERMAL_STATUS_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

class IThermalStatusListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(ThermalStatusListener)
  virtual ::android::binder::Status onStatusChange(int32_t status) = 0;
};  // class IThermalStatusListener

class IThermalStatusListenerDefault : public IThermalStatusListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onStatusChange(int32_t status) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_THERMAL_STATUS_LISTENER_H_
