#ifndef AIDL_GENERATED_ANDROID_OS_I_EXTERNAL_VIBRATOR_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_I_EXTERNAL_VIBRATOR_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>
#include <vibrator/ExternalVibration.h>

namespace android {

namespace os {

class IExternalVibratorService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(ExternalVibratorService)
  enum  : int32_t {
    SCALE_MUTE = -100,
    SCALE_VERY_LOW = -2,
    SCALE_LOW = -1,
    SCALE_NONE = 0,
    SCALE_HIGH = 1,
    SCALE_VERY_HIGH = 2,
  };
  virtual ::android::binder::Status onExternalVibrationStart(const ::android::os::ExternalVibration& vib, int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status onExternalVibrationStop(const ::android::os::ExternalVibration& vib) = 0;
};  // class IExternalVibratorService

class IExternalVibratorServiceDefault : public IExternalVibratorService {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onExternalVibrationStart(const ::android::os::ExternalVibration& vib, int32_t* _aidl_return) override;
  ::android::binder::Status onExternalVibrationStop(const ::android::os::ExternalVibration& vib) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_EXTERNAL_VIBRATOR_SERVICE_H_
