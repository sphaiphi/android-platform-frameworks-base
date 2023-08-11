#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BP_SENSOR_PRIVACY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BP_SENSOR_PRIVACY_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/ISensorPrivacyListener.h>

namespace android {

namespace hardware {

class BpSensorPrivacyListener : public ::android::BpInterface<ISensorPrivacyListener> {
public:
  explicit BpSensorPrivacyListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpSensorPrivacyListener() = default;
  ::android::binder::Status onSensorPrivacyChanged(bool enabled) override;
};  // class BpSensorPrivacyListener

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BP_SENSOR_PRIVACY_LISTENER_H_
