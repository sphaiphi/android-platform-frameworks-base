#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_VENDOR_COMMAND_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_VENDOR_COMMAND_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/hdmi/IHdmiVendorCommandListener.h>

namespace android {

namespace hardware {

namespace hdmi {

class BpHdmiVendorCommandListener : public ::android::BpInterface<IHdmiVendorCommandListener> {
public:
  explicit BpHdmiVendorCommandListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHdmiVendorCommandListener() = default;
  ::android::binder::Status onReceived(int32_t logicalAddress, int32_t destAddress, const ::std::vector<uint8_t>& operands, bool hasVendorId) override;
  ::android::binder::Status onControlStateChanged(bool enabled, int32_t reason) override;
};  // class BpHdmiVendorCommandListener

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_VENDOR_COMMAND_LISTENER_H_
