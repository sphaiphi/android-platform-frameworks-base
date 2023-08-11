#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_ERASE_SUBSCRIPTIONS_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_ERASE_SUBSCRIPTIONS_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/euicc/IEraseSubscriptionsCallback.h>

namespace android {

namespace service {

namespace euicc {

class BpEraseSubscriptionsCallback : public ::android::BpInterface<IEraseSubscriptionsCallback> {
public:
  explicit BpEraseSubscriptionsCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpEraseSubscriptionsCallback() = default;
  ::android::binder::Status onComplete(int32_t result) override;
};  // class BpEraseSubscriptionsCallback

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_ERASE_SUBSCRIPTIONS_CALLBACK_H_
