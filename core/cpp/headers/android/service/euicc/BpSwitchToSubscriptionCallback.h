#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_SWITCH_TO_SUBSCRIPTION_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_SWITCH_TO_SUBSCRIPTION_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/euicc/ISwitchToSubscriptionCallback.h>

namespace android {

namespace service {

namespace euicc {

class BpSwitchToSubscriptionCallback : public ::android::BpInterface<ISwitchToSubscriptionCallback> {
public:
  explicit BpSwitchToSubscriptionCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpSwitchToSubscriptionCallback() = default;
  ::android::binder::Status onComplete(int32_t result) override;
};  // class BpSwitchToSubscriptionCallback

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_SWITCH_TO_SUBSCRIPTION_CALLBACK_H_
