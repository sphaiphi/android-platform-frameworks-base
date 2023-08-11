#ifndef AIDL_GENERATED_ANDROID_HARDWARE_RADIO_I_CLOSE_HANDLE_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_RADIO_I_CLOSE_HANDLE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

namespace radio {

class ICloseHandle : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CloseHandle)
  virtual ::android::binder::Status close() = 0;
};  // class ICloseHandle

class ICloseHandleDefault : public ICloseHandle {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status close() override;

};

}  // namespace radio

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_RADIO_I_CLOSE_HANDLE_H_
