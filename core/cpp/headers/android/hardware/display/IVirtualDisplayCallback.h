#ifndef AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_I_VIRTUAL_DISPLAY_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_I_VIRTUAL_DISPLAY_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

namespace display {

class IVirtualDisplayCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VirtualDisplayCallback)
  virtual ::android::binder::Status onPaused() = 0;
  virtual ::android::binder::Status onResumed() = 0;
  virtual ::android::binder::Status onStopped() = 0;
};  // class IVirtualDisplayCallback

class IVirtualDisplayCallbackDefault : public IVirtualDisplayCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onPaused() override;
  ::android::binder::Status onResumed() override;
  ::android::binder::Status onStopped() override;

};

}  // namespace display

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_I_VIRTUAL_DISPLAY_CALLBACK_H_
