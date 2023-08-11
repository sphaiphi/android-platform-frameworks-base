#ifndef AIDL_GENERATED_ANDROID_HARDWARE_I_SERIAL_MANAGER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_I_SERIAL_MANAGER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/ParcelFileDescriptor.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace hardware {

class ISerialManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(SerialManager)
  virtual ::android::binder::Status getSerialPorts(::std::vector<::android::String16>* _aidl_return) = 0;
  virtual ::android::binder::Status openSerialPort(const ::android::String16& name, ::android::os::ParcelFileDescriptor* _aidl_return) = 0;
};  // class ISerialManager

class ISerialManagerDefault : public ISerialManager {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status getSerialPorts(::std::vector<::android::String16>* _aidl_return) override;
  ::android::binder::Status openSerialPort(const ::android::String16& name, ::android::os::ParcelFileDescriptor* _aidl_return) override;

};

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_I_SERIAL_MANAGER_H_
