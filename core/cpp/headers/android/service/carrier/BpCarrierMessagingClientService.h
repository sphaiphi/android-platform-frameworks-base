#ifndef AIDL_GENERATED_ANDROID_SERVICE_CARRIER_BP_CARRIER_MESSAGING_CLIENT_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_CARRIER_BP_CARRIER_MESSAGING_CLIENT_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/carrier/ICarrierMessagingClientService.h>

namespace android {

namespace service {

namespace carrier {

class BpCarrierMessagingClientService : public ::android::BpInterface<ICarrierMessagingClientService> {
public:
  explicit BpCarrierMessagingClientService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCarrierMessagingClientService() = default;
};  // class BpCarrierMessagingClientService

}  // namespace carrier

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_CARRIER_BP_CARRIER_MESSAGING_CLIENT_SERVICE_H_
