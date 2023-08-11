#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_I_RETAIN_SUBSCRIPTIONS_FOR_FACTORY_RESET_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_I_RETAIN_SUBSCRIPTIONS_FOR_FACTORY_RESET_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace service {

namespace euicc {

class IRetainSubscriptionsForFactoryResetCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RetainSubscriptionsForFactoryResetCallback)
  virtual ::android::binder::Status onComplete(int32_t result) = 0;
};  // class IRetainSubscriptionsForFactoryResetCallback

class IRetainSubscriptionsForFactoryResetCallbackDefault : public IRetainSubscriptionsForFactoryResetCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onComplete(int32_t result) override;

};

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_I_RETAIN_SUBSCRIPTIONS_FOR_FACTORY_RESET_CALLBACK_H_
