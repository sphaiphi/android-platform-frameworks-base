#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_RECORD_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_RECORD_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/hdmi/IHdmiRecordListener.h>

namespace android {

namespace hardware {

namespace hdmi {

class BpHdmiRecordListener : public ::android::BpInterface<IHdmiRecordListener> {
public:
  explicit BpHdmiRecordListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHdmiRecordListener() = default;
  ::android::binder::Status getOneTouchRecordSource(int32_t recorderAddress, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status onOneTouchRecordResult(int32_t recorderAddress, int32_t result) override;
  ::android::binder::Status onTimerRecordingResult(int32_t recorderAddress, int32_t result) override;
  ::android::binder::Status onClearTimerRecordingResult(int32_t recorderAddress, int32_t result) override;
};  // class BpHdmiRecordListener

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_RECORD_LISTENER_H_
