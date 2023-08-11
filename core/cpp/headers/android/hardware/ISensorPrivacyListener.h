#ifndef AIDL_GENERATED_ANDROID_HARDWARE_I_SENSOR_PRIVACY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_I_SENSOR_PRIVACY_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

class ISensorPrivacyListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(SensorPrivacyListener)
  virtual ::android::binder::Status onSensorPrivacyChanged(bool enabled) = 0;
};  // class ISensorPrivacyListener

class ISensorPrivacyListenerDefault : public ISensorPrivacyListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onSensorPrivacyChanged(bool enabled) override;

};

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_I_SENSOR_PRIVACY_LISTENER_H_
