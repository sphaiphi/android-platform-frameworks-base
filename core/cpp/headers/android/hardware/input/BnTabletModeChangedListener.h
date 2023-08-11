#ifndef AIDL_GENERATED_ANDROID_HARDWARE_INPUT_BN_TABLET_MODE_CHANGED_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_INPUT_BN_TABLET_MODE_CHANGED_LISTENER_H_

#include <binder/IInterface.h>
#include <android/hardware/input/ITabletModeChangedListener.h>

namespace android {

namespace hardware {

namespace input {

class BnTabletModeChangedListener : public ::android::BnInterface<ITabletModeChangedListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnTabletModeChangedListener

}  // namespace input

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_INPUT_BN_TABLET_MODE_CHANGED_LISTENER_H_
