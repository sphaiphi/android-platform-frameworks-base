#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_CONTROL_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_CONTROL_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/hdmi/IHdmiControlCallback.h>

namespace android {

namespace hardware {

namespace hdmi {

class BpHdmiControlCallback : public ::android::BpInterface<IHdmiControlCallback> {
public:
  explicit BpHdmiControlCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHdmiControlCallback() = default;
  ::android::binder::Status onComplete(int32_t result) override;
};  // class BpHdmiControlCallback

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_CONTROL_CALLBACK_H_
