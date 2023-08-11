#ifndef AIDL_GENERATED_ANDROID_HARDWARE_INPUT_I_INPUT_DEVICES_CHANGED_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_INPUT_I_INPUT_DEVICES_CHANGED_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace hardware {

namespace input {

class IInputDevicesChangedListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(InputDevicesChangedListener)
  virtual ::android::binder::Status onInputDevicesChanged(const ::std::vector<int32_t>& deviceIdAndGeneration) = 0;
};  // class IInputDevicesChangedListener

class IInputDevicesChangedListenerDefault : public IInputDevicesChangedListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onInputDevicesChanged(const ::std::vector<int32_t>& deviceIdAndGeneration) override;

};

}  // namespace input

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_INPUT_I_INPUT_DEVICES_CHANGED_LISTENER_H_
