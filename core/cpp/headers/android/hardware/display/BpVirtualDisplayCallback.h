#ifndef AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_BP_VIRTUAL_DISPLAY_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_BP_VIRTUAL_DISPLAY_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/display/IVirtualDisplayCallback.h>

namespace android {

namespace hardware {

namespace display {

class BpVirtualDisplayCallback : public ::android::BpInterface<IVirtualDisplayCallback> {
public:
  explicit BpVirtualDisplayCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpVirtualDisplayCallback() = default;
  ::android::binder::Status onPaused() override;
  ::android::binder::Status onResumed() override;
  ::android::binder::Status onStopped() override;
};  // class BpVirtualDisplayCallback

}  // namespace display

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_BP_VIRTUAL_DISPLAY_CALLBACK_H_
