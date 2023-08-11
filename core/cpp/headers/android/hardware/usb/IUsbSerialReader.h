#ifndef AIDL_GENERATED_ANDROID_HARDWARE_USB_I_USB_SERIAL_READER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_USB_I_USB_SERIAL_READER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

namespace usb {

class IUsbSerialReader : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(UsbSerialReader)
  virtual ::android::binder::Status getSerial(const ::android::String16& packageName, ::android::String16* _aidl_return) = 0;
};  // class IUsbSerialReader

class IUsbSerialReaderDefault : public IUsbSerialReader {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status getSerial(const ::android::String16& packageName, ::android::String16* _aidl_return) override;

};

}  // namespace usb

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_USB_I_USB_SERIAL_READER_H_
