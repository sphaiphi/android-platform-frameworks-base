#ifndef AIDL_GENERATED_ANDROID_OS_BP_THERMAL_STATUS_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_BP_THERMAL_STATUS_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/IThermalStatusListener.h>

namespace android {

namespace os {

class BpThermalStatusListener : public ::android::BpInterface<IThermalStatusListener> {
public:
  explicit BpThermalStatusListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpThermalStatusListener() = default;
  ::android::binder::Status onStatusChange(int32_t status) override;
};  // class BpThermalStatusListener

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_THERMAL_STATUS_LISTENER_H_
