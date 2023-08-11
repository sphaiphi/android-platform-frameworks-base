#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BN_HDMI_VENDOR_COMMAND_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BN_HDMI_VENDOR_COMMAND_LISTENER_H_

#include <binder/IInterface.h>
#include <android/hardware/hdmi/IHdmiVendorCommandListener.h>

namespace android {

namespace hardware {

namespace hdmi {

class BnHdmiVendorCommandListener : public ::android::BnInterface<IHdmiVendorCommandListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnHdmiVendorCommandListener

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BN_HDMI_VENDOR_COMMAND_LISTENER_H_
