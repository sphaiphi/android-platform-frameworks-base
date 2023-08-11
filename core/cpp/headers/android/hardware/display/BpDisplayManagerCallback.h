#ifndef AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_BP_DISPLAY_MANAGER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_BP_DISPLAY_MANAGER_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/display/IDisplayManagerCallback.h>

namespace android {

namespace hardware {

namespace display {

class BpDisplayManagerCallback : public ::android::BpInterface<IDisplayManagerCallback> {
public:
  explicit BpDisplayManagerCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDisplayManagerCallback() = default;
  ::android::binder::Status onDisplayEvent(int32_t displayId, int32_t event) override;
};  // class BpDisplayManagerCallback

}  // namespace display

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_DISPLAY_BP_DISPLAY_MANAGER_CALLBACK_H_
