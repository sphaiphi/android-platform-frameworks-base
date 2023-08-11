#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BN_SERIAL_MANAGER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BN_SERIAL_MANAGER_H_

#include <binder/IInterface.h>
#include <android/hardware/ISerialManager.h>

namespace android {

namespace hardware {

class BnSerialManager : public ::android::BnInterface<ISerialManager> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnSerialManager

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BN_SERIAL_MANAGER_H_
