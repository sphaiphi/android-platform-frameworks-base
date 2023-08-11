#ifndef AIDL_GENERATED_ANDROID_APP_TIMEZONE_I_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_TIMEZONE_I_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

namespace timezone {

class ICallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Callback)
  virtual ::android::binder::Status onFinished(int32_t error) = 0;
};  // class ICallback

class ICallbackDefault : public ICallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onFinished(int32_t error) override;

};

}  // namespace timezone

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_TIMEZONE_I_CALLBACK_H_
