#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_UPDATE_SUBSCRIPTION_NICKNAME_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_UPDATE_SUBSCRIPTION_NICKNAME_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/euicc/IUpdateSubscriptionNicknameCallback.h>

namespace android {

namespace service {

namespace euicc {

class BpUpdateSubscriptionNicknameCallback : public ::android::BpInterface<IUpdateSubscriptionNicknameCallback> {
public:
  explicit BpUpdateSubscriptionNicknameCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpUpdateSubscriptionNicknameCallback() = default;
  ::android::binder::Status onComplete(int32_t result) override;
};  // class BpUpdateSubscriptionNicknameCallback

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_UPDATE_SUBSCRIPTION_NICKNAME_CALLBACK_H_
