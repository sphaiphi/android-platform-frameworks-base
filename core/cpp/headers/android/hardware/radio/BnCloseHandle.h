#ifndef AIDL_GENERATED_ANDROID_HARDWARE_RADIO_BN_CLOSE_HANDLE_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_RADIO_BN_CLOSE_HANDLE_H_

#include <binder/IInterface.h>
#include <android/hardware/radio/ICloseHandle.h>

namespace android {

namespace hardware {

namespace radio {

class BnCloseHandle : public ::android::BnInterface<ICloseHandle> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnCloseHandle

}  // namespace radio

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_RADIO_BN_CLOSE_HANDLE_H_
