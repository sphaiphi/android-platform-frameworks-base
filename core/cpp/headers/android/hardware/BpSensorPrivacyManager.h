#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BP_SENSOR_PRIVACY_MANAGER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BP_SENSOR_PRIVACY_MANAGER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/ISensorPrivacyManager.h>

namespace android {

namespace hardware {

class BpSensorPrivacyManager : public ::android::BpInterface<ISensorPrivacyManager> {
public:
  explicit BpSensorPrivacyManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpSensorPrivacyManager() = default;
  ::android::binder::Status addSensorPrivacyListener(const ::android::sp<::android::hardware::ISensorPrivacyListener>& listener) override;
  ::android::binder::Status removeSensorPrivacyListener(const ::android::sp<::android::hardware::ISensorPrivacyListener>& listener) override;
  ::android::binder::Status isSensorPrivacyEnabled(bool* _aidl_return) override;
  ::android::binder::Status setSensorPrivacy(bool enable) override;
};  // class BpSensorPrivacyManager

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BP_SENSOR_PRIVACY_MANAGER_H_
