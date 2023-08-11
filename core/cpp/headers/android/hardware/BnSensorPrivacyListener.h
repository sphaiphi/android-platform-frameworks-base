#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BN_SENSOR_PRIVACY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BN_SENSOR_PRIVACY_LISTENER_H_

#include <binder/IInterface.h>
#include <android/hardware/ISensorPrivacyListener.h>

namespace android {

namespace hardware {

class BnSensorPrivacyListener : public ::android::BnInterface<ISensorPrivacyListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnSensorPrivacyListener

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BN_SENSOR_PRIVACY_LISTENER_H_
