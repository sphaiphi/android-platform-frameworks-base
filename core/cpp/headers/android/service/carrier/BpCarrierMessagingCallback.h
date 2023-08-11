#ifndef AIDL_GENERATED_ANDROID_SERVICE_CARRIER_BP_CARRIER_MESSAGING_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_CARRIER_BP_CARRIER_MESSAGING_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/carrier/ICarrierMessagingCallback.h>

namespace android {

namespace service {

namespace carrier {

class BpCarrierMessagingCallback : public ::android::BpInterface<ICarrierMessagingCallback> {
public:
  explicit BpCarrierMessagingCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCarrierMessagingCallback() = default;
  ::android::binder::Status onFilterComplete(int32_t result) override;
  ::android::binder::Status onSendSmsComplete(int32_t result, int32_t messageRef) override;
  ::android::binder::Status onSendMultipartSmsComplete(int32_t result, const ::std::vector<int32_t>& messageRefs) override;
  ::android::binder::Status onSendMmsComplete(int32_t result, const ::std::vector<uint8_t>& sendConfPdu) override;
  ::android::binder::Status onDownloadMmsComplete(int32_t result) override;
};  // class BpCarrierMessagingCallback

}  // namespace carrier

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_CARRIER_BP_CARRIER_MESSAGING_CALLBACK_H_
