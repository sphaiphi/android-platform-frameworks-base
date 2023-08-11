#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_VENDOR_COMMAND_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_VENDOR_COMMAND_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace hardware {

namespace hdmi {

class IHdmiVendorCommandListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HdmiVendorCommandListener)
  virtual ::android::binder::Status onReceived(int32_t logicalAddress, int32_t destAddress, const ::std::vector<uint8_t>& operands, bool hasVendorId) = 0;
  virtual ::android::binder::Status onControlStateChanged(bool enabled, int32_t reason) = 0;
};  // class IHdmiVendorCommandListener

class IHdmiVendorCommandListenerDefault : public IHdmiVendorCommandListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onReceived(int32_t logicalAddress, int32_t destAddress, const ::std::vector<uint8_t>& operands, bool hasVendorId) override;
  ::android::binder::Status onControlStateChanged(bool enabled, int32_t reason) override;

};

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_VENDOR_COMMAND_LISTENER_H_
