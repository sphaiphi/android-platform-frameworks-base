#ifndef AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_I_DISPLAY_MANAGER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_I_DISPLAY_MANAGER_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

namespace display {

class IDisplayManagerCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DisplayManagerCallback)
  virtual ::android::binder::Status onDisplayEvent(int32_t displayId, int32_t event) = 0;
};  // class IDisplayManagerCallback

class IDisplayManagerCallbackDefault : public IDisplayManagerCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onDisplayEvent(int32_t displayId, int32_t event) override;

};

}  // namespace display

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_I_DISPLAY_MANAGER_CALLBACK_H_
