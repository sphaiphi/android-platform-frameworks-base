#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BN_HDMI_CONTROL_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BN_HDMI_CONTROL_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/hardware/hdmi/IHdmiControlCallback.h>

namespace android {

namespace hardware {

namespace hdmi {

class BnHdmiControlCallback : public ::android::BnInterface<IHdmiControlCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnHdmiControlCallback

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BN_HDMI_CONTROL_CALLBACK_H_
