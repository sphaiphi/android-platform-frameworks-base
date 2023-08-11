#ifndef AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_CONTROL_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_CONTROL_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

namespace hdmi {

class IHdmiControlCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HdmiControlCallback)
  virtual ::android::binder::Status onComplete(int32_t result) = 0;
};  // class IHdmiControlCallback

class IHdmiControlCallbackDefault : public IHdmiControlCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onComplete(int32_t result) override;

};

}  // namespace hdmi

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_HDMI_I_HDMI_CONTROL_CALLBACK_H_
