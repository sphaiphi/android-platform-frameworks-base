#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_SYSTEM_AUDIO_MODE_CHANGE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_SYSTEM_AUDIO_MODE_CHANGE_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/hdmi/IHdmiSystemAudioModeChangeListener.h>

namespace android {

namespace hardware {

namespace hdmi {

class BpHdmiSystemAudioModeChangeListener : public ::android::BpInterface<IHdmiSystemAudioModeChangeListener> {
public:
  explicit BpHdmiSystemAudioModeChangeListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHdmiSystemAudioModeChangeListener() = default;
  ::android::binder::Status onStatusChanged(bool enabled) override;
};  // class BpHdmiSystemAudioModeChangeListener

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BP_HDMI_SYSTEM_AUDIO_MODE_CHANGE_LISTENER_H_
