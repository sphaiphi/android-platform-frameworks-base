#ifndef AIDL_GENERATED_ANDROID_APP_BP_REQUEST_FINISH_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_BP_REQUEST_FINISH_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/IRequestFinishCallback.h>

namespace android {

namespace app {

class BpRequestFinishCallback : public ::android::BpInterface<IRequestFinishCallback> {
public:
  explicit BpRequestFinishCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpRequestFinishCallback() = default;
  ::android::binder::Status requestFinish() override;
};  // class BpRequestFinishCallback

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BP_REQUEST_FINISH_CALLBACK_H_
