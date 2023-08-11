#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_RETAIN_SUBSCRIPTIONS_FOR_FACTORY_RESET_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_RETAIN_SUBSCRIPTIONS_FOR_FACTORY_RESET_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/euicc/IRetainSubscriptionsForFactoryResetCallback.h>

namespace android {

namespace service {

namespace euicc {

class BpRetainSubscriptionsForFactoryResetCallback : public ::android::BpInterface<IRetainSubscriptionsForFactoryResetCallback> {
public:
  explicit BpRetainSubscriptionsForFactoryResetCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpRetainSubscriptionsForFactoryResetCallback() = default;
  ::android::binder::Status onComplete(int32_t result) override;
};  // class BpRetainSubscriptionsForFactoryResetCallback

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_RETAIN_SUBSCRIPTIONS_FOR_FACTORY_RESET_CALLBACK_H_
