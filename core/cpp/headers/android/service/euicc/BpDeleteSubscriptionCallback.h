#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_DELETE_SUBSCRIPTION_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_DELETE_SUBSCRIPTION_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/euicc/IDeleteSubscriptionCallback.h>

namespace android {

namespace service {

namespace euicc {

class BpDeleteSubscriptionCallback : public ::android::BpInterface<IDeleteSubscriptionCallback> {
public:
  explicit BpDeleteSubscriptionCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDeleteSubscriptionCallback() = default;
  ::android::binder::Status onComplete(int32_t result) override;
};  // class BpDeleteSubscriptionCallback

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_DELETE_SUBSCRIPTION_CALLBACK_H_
