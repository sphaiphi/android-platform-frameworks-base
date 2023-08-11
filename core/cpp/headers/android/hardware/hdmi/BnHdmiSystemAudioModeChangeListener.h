#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BN_HDMI_SYSTEM_AUDIO_MODE_CHANGE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BN_HDMI_SYSTEM_AUDIO_MODE_CHANGE_LISTENER_H_

#include <binder/IInterface.h>
#include <android/hardware/hdmi/IHdmiSystemAudioModeChangeListener.h>

namespace android {

namespace hardware {

namespace hdmi {

class BnHdmiSystemAudioModeChangeListener : public ::android::BnInterface<IHdmiSystemAudioModeChangeListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnHdmiSystemAudioModeChangeListener

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_BN_HDMI_SYSTEM_AUDIO_MODE_CHANGE_LISTENER_H_
