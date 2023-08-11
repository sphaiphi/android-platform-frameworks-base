#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BP_SERIAL_MANAGER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BP_SERIAL_MANAGER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/ISerialManager.h>

namespace android {

namespace hardware {

class BpSerialManager : public ::android::BpInterface<ISerialManager> {
public:
  explicit BpSerialManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpSerialManager() = default;
  ::android::binder::Status getSerialPorts(::std::vector<::android::String16>* _aidl_return) override;
  ::android::binder::Status openSerialPort(const ::android::String16& name, ::android::os::ParcelFileDescriptor* _aidl_return) override;
};  // class BpSerialManager

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BP_SERIAL_MANAGER_H_
