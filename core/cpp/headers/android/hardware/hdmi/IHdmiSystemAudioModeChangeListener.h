#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_SYSTEM_AUDIO_MODE_CHANGE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_SYSTEM_AUDIO_MODE_CHANGE_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

namespace hdmi {

class IHdmiSystemAudioModeChangeListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HdmiSystemAudioModeChangeListener)
  virtual ::android::binder::Status onStatusChanged(bool enabled) = 0;
};  // class IHdmiSystemAudioModeChangeListener

class IHdmiSystemAudioModeChangeListenerDefault : public IHdmiSystemAudioModeChangeListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onStatusChanged(bool enabled) override;

};

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_SYSTEM_AUDIO_MODE_CHANGE_LISTENER_H_
