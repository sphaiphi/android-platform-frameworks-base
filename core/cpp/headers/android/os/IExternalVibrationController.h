#ifndef AIDL_GENERATED_ANDROID_OS_I_EXTERNAL_VIBRATION_CONTROLLER_H_
#define AIDL_GENERATED_ANDROID_OS_I_EXTERNAL_VIBRATION_CONTROLLER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

class IExternalVibrationController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(ExternalVibrationController)
  virtual ::android::binder::Status mute(bool* _aidl_return) = 0;
  virtual ::android::binder::Status unmute(bool* _aidl_return) = 0;
};  // class IExternalVibrationController

class IExternalVibrationControllerDefault : public IExternalVibrationController {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status mute(bool* _aidl_return) override;
  ::android::binder::Status unmute(bool* _aidl_return) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_EXTERNAL_VIBRATION_CONTROLLER_H_
