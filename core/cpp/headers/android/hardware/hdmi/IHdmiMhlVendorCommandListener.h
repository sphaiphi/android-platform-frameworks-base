#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_MHL_VENDOR_COMMAND_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_MHL_VENDOR_COMMAND_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace hardware {

namespace hdmi {

class IHdmiMhlVendorCommandListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HdmiMhlVendorCommandListener)
  virtual ::android::binder::Status onReceived(int32_t portId, int32_t offset, int32_t length, const ::std::vector<uint8_t>& data) = 0;
};  // class IHdmiMhlVendorCommandListener

class IHdmiMhlVendorCommandListenerDefault : public IHdmiMhlVendorCommandListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onReceived(int32_t portId, int32_t offset, int32_t length, const ::std::vector<uint8_t>& data) override;

};

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_MHL_VENDOR_COMMAND_LISTENER_H_
