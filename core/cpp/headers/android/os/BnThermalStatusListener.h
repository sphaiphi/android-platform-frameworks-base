#ifndef AIDL_GENERATED_ANDROID_OS_BN_THERMAL_STATUS_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_BN_THERMAL_STATUS_LISTENER_H_

#include <binder/IInterface.h>
#include <android/os/IThermalStatusListener.h>

namespace android {

namespace os {

class BnThermalStatusListener : public ::android::BnInterface<IThermalStatusListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnThermalStatusListener

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_THERMAL_STATUS_LISTENER_H_
