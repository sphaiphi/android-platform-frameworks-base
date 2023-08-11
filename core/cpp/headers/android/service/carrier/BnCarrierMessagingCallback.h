#ifndef AIDL_GENERATED_ANDROID_SERVICE_CARRIER_BN_CARRIER_MESSAGING_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_CARRIER_BN_CARRIER_MESSAGING_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/service/carrier/ICarrierMessagingCallback.h>

namespace android {

namespace service {

namespace carrier {

class BnCarrierMessagingCallback : public ::android::BnInterface<ICarrierMessagingCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnCarrierMessagingCallback

}  // namespace carrier

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_CARRIER_BN_CARRIER_MESSAGING_CALLBACK_H_
