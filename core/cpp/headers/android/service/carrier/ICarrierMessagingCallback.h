#ifndef AIDL_GENERATED_ANDROID_SERVICE_CARRIER_I_CARRIER_MESSAGING_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_CARRIER_I_CARRIER_MESSAGING_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace service {

namespace carrier {

class ICarrierMessagingCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CarrierMessagingCallback)
  virtual ::android::binder::Status onFilterComplete(int32_t result) = 0;
  virtual ::android::binder::Status onSendSmsComplete(int32_t result, int32_t messageRef) = 0;
  virtual ::android::binder::Status onSendMultipartSmsComplete(int32_t result, const ::std::vector<int32_t>& messageRefs) = 0;
  virtual ::android::binder::Status onSendMmsComplete(int32_t result, const ::std::vector<uint8_t>& sendConfPdu) = 0;
  virtual ::android::binder::Status onDownloadMmsComplete(int32_t result) = 0;
};  // class ICarrierMessagingCallback

class ICarrierMessagingCallbackDefault : public ICarrierMessagingCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onFilterComplete(int32_t result) override;
  ::android::binder::Status onSendSmsComplete(int32_t result, int32_t messageRef) override;
  ::android::binder::Status onSendMultipartSmsComplete(int32_t result, const ::std::vector<int32_t>& messageRefs) override;
  ::android::binder::Status onSendMmsComplete(int32_t result, const ::std::vector<uint8_t>& sendConfPdu) override;
  ::android::binder::Status onDownloadMmsComplete(int32_t result) override;

};

}  // namespace carrier

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_CARRIER_I_CARRIER_MESSAGING_CALLBACK_H_
