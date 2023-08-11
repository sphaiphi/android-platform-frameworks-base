#ifndef AIDL_GENERATED_ANDROID_HARDWARE_USB_BP_USB_SERIAL_READER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_USB_BP_USB_SERIAL_READER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/usb/IUsbSerialReader.h>

namespace android {

namespace hardware {

namespace usb {

class BpUsbSerialReader : public ::android::BpInterface<IUsbSerialReader> {
public:
  explicit BpUsbSerialReader(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpUsbSerialReader() = default;
  ::android::binder::Status getSerial(const ::android::String16& packageName, ::android::String16* _aidl_return) override;
};  // class BpUsbSerialReader

}  // namespace usb

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_USB_BP_USB_SERIAL_READER_H_
