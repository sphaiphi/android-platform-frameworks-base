#ifndef AIDL_GENERATED_ANDROID_HARDWARE_RADIO_BP_CLOSE_HANDLE_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_RADIO_BP_CLOSE_HANDLE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/radio/ICloseHandle.h>

namespace android {

namespace hardware {

namespace radio {

class BpCloseHandle : public ::android::BpInterface<ICloseHandle> {
public:
  explicit BpCloseHandle(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCloseHandle() = default;
  ::android::binder::Status close() override;
};  // class BpCloseHandle

}  // namespace radio

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_RADIO_BP_CLOSE_HANDLE_H_
