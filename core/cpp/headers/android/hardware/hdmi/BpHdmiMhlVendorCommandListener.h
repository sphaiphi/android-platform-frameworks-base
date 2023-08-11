#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_MHL_VENDOR_COMMAND_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_MHL_VENDOR_COMMAND_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/hdmi/IHdmiMhlVendorCommandListener.h>

namespace android {

namespace hardware {

namespace hdmi {

class BpHdmiMhlVendorCommandListener : public ::android::BpInterface<IHdmiMhlVendorCommandListener> {
public:
  explicit BpHdmiMhlVendorCommandListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHdmiMhlVendorCommandListener() = default;
  ::android::binder::Status onReceived(int32_t portId, int32_t offset, int32_t length, const ::std::vector<uint8_t>& data) override;
};  // class BpHdmiMhlVendorCommandListener

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_MHL_VENDOR_COMMAND_LISTENER_H_
