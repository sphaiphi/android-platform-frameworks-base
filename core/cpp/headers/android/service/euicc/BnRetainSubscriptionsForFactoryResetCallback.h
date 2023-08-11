#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_BN_RETAIN_SUBSCRIPTIONS_FOR_FACTORY_RESET_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_BN_RETAIN_SUBSCRIPTIONS_FOR_FACTORY_RESET_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/service/euicc/IRetainSubscriptionsForFactoryResetCallback.h>

namespace android {

namespace service {

namespace euicc {

class BnRetainSubscriptionsForFactoryResetCallback : public ::android::BnInterface<IRetainSubscriptionsForFactoryResetCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnRetainSubscriptionsForFactoryResetCallback

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_BN_RETAIN_SUBSCRIPTIONS_FOR_FACTORY_RESET_CALLBACK_H_
