#ifndef AIDL_GENERATED_ANDROID_HARDWARE_USB_BN_USB_SERIAL_READER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_USB_BN_USB_SERIAL_READER_H_

#include <binder/IInterface.h>
#include <android/hardware/usb/IUsbSerialReader.h>

namespace android {

namespace hardware {

namespace usb {

class BnUsbSerialReader : public ::android::BnInterface<IUsbSerialReader> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnUsbSerialReader

}  // namespace usb

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_USB_BN_USB_SERIAL_READER_H_
