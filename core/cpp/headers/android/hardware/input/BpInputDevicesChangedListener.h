#ifndef AIDL_GENERATED_ANDROID_HARDWARE_INPUT_BP_INPUT_DEVICES_CHANGED_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_INPUT_BP_INPUT_DEVICES_CHANGED_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/input/IInputDevicesChangedListener.h>

namespace android {

namespace hardware {

namespace input {

class BpInputDevicesChangedListener : public ::android::BpInterface<IInputDevicesChangedListener> {
public:
  explicit BpInputDevicesChangedListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpInputDevicesChangedListener() = default;
  ::android::binder::Status onInputDevicesChanged(const ::std::vector<int32_t>& deviceIdAndGeneration) override;
};  // class BpInputDevicesChangedListener

}  // namespace input

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_INPUT_BP_INPUT_DEVICES_CHANGED_LISTENER_H_
