#ifndef AIDL_GENERATED_ANDROID_SERVICE_CARRIER_I_CARRIER_MESSAGING_CLIENT_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_CARRIER_I_CARRIER_MESSAGING_CLIENT_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace service {

namespace carrier {

class ICarrierMessagingClientService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CarrierMessagingClientService)
};  // class ICarrierMessagingClientService

class ICarrierMessagingClientServiceDefault : public ICarrierMessagingClientService {
public:
  ::android::IBinder* onAsBinder() override;
  
};

}  // namespace carrier

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_CARRIER_I_CARRIER_MESSAGING_CLIENT_SERVICE_H_
