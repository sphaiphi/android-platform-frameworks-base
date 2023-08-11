#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_RECORD_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_RECORD_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace hardware {

namespace hdmi {

class IHdmiRecordListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HdmiRecordListener)
  virtual ::android::binder::Status getOneTouchRecordSource(int32_t recorderAddress, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status onOneTouchRecordResult(int32_t recorderAddress, int32_t result) = 0;
  virtual ::android::binder::Status onTimerRecordingResult(int32_t recorderAddress, int32_t result) = 0;
  virtual ::android::binder::Status onClearTimerRecordingResult(int32_t recorderAddress, int32_t result) = 0;
};  // class IHdmiRecordListener

class IHdmiRecordListenerDefault : public IHdmiRecordListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status getOneTouchRecordSource(int32_t recorderAddress, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status onOneTouchRecordResult(int32_t recorderAddress, int32_t result) override;
  ::android::binder::Status onTimerRecordingResult(int32_t recorderAddress, int32_t result) override;
  ::android::binder::Status onClearTimerRecordingResult(int32_t recorderAddress, int32_t result) override;

};

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_RECORD_LISTENER_H_
