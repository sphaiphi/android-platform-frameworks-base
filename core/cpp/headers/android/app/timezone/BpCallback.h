#ifndef AIDL_GENERATED_ANDROID_APP_TIMEZONE_BP_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_TIMEZONE_BP_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/timezone/ICallback.h>

namespace android {

namespace app {

namespace timezone {

class BpCallback : public ::android::BpInterface<ICallback> {
public:
  explicit BpCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCallback() = default;
  ::android::binder::Status onFinished(int32_t error) override;
};  // class BpCallback

}  // namespace timezone

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_TIMEZONE_BP_CALLBACK_H_
