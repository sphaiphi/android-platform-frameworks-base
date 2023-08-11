#ifndef AIDL_GENERATED_ANDROID_HARDWARE_I_SENSOR_PRIVACY_MANAGER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_I_SENSOR_PRIVACY_MANAGER_H_

#include <android/hardware/ISensorPrivacyListener.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

class ISensorPrivacyManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(SensorPrivacyManager)
  virtual ::android::binder::Status addSensorPrivacyListener(const ::android::sp<::android::hardware::ISensorPrivacyListener>& listener) = 0;
  virtual ::android::binder::Status removeSensorPrivacyListener(const ::android::sp<::android::hardware::ISensorPrivacyListener>& listener) = 0;
  virtual ::android::binder::Status isSensorPrivacyEnabled(bool* _aidl_return) = 0;
  virtual ::android::binder::Status setSensorPrivacy(bool enable) = 0;
};  // class ISensorPrivacyManager

class ISensorPrivacyManagerDefault : public ISensorPrivacyManager {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status addSensorPrivacyListener(const ::android::sp<::android::hardware::ISensorPrivacyListener>& listener) override;
  ::android::binder::Status removeSensorPrivacyListener(const ::android::sp<::android::hardware::ISensorPrivacyListener>& listener) override;
  ::android::binder::Status isSensorPrivacyEnabled(bool* _aidl_return) override;
  ::android::binder::Status setSensorPrivacy(bool enable) override;

};

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_I_SENSOR_PRIVACY_MANAGER_H_
