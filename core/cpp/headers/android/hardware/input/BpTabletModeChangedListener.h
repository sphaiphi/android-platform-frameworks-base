#ifndef AIDL_GENERATED_ANDROID_HARDWARE_INPUT_BP_TABLET_MODE_CHANGED_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_INPUT_BP_TABLET_MODE_CHANGED_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/input/ITabletModeChangedListener.h>

namespace android {

namespace hardware {

namespace input {

class BpTabletModeChangedListener : public ::android::BpInterface<ITabletModeChangedListener> {
public:
  explicit BpTabletModeChangedListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpTabletModeChangedListener() = default;
  ::android::binder::Status onTabletModeChanged(int64_t whenNanos, bool inTabletMode) override;
};  // class BpTabletModeChangedListener

}  // namespace input

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_INPUT_BP_TABLET_MODE_CHANGED_LISTENER_H_
