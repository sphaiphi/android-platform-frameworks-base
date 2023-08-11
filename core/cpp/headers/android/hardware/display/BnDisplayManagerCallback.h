#ifndef AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_BN_DISPLAY_MANAGER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_BN_DISPLAY_MANAGER_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/hardware/display/IDisplayManagerCallback.h>

namespace android {

namespace hardware {

namespace display {

class BnDisplayManagerCallback : public ::android::BnInterface<IDisplayManagerCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnDisplayManagerCallback

}  // namespace display

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_BN_DISPLAY_MANAGER_CALLBACK_H_
