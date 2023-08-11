#ifndef AIDL_GENERATED_ANDROID_SERVICE_CARRIER_BN_CARRIER_MESSAGING_CLIENT_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_CARRIER_BN_CARRIER_MESSAGING_CLIENT_SERVICE_H_

#include <binder/IInterface.h>
#include <android/service/carrier/ICarrierMessagingClientService.h>

namespace android {

namespace service {

namespace carrier {

class BnCarrierMessagingClientService : public ::android::BnInterface<ICarrierMessagingClientService> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnCarrierMessagingClientService

}  // namespace carrier

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_CARRIER_BN_CARRIER_MESSAGING_CLIENT_SERVICE_H_
