#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BP_CONSUMER_IR_SERVICE_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BP_CONSUMER_IR_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/IConsumerIrService.h>

namespace android {

namespace hardware {

class BpConsumerIrService : public ::android::BpInterface<IConsumerIrService> {
public:
  explicit BpConsumerIrService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpConsumerIrService() = default;
  ::android::binder::Status hasIrEmitter(bool* _aidl_return) override;
  ::android::binder::Status transmit(const ::android::String16& packageName, int32_t carrierFrequency, const ::std::vector<int32_t>& pattern) override;
  ::android::binder::Status getCarrierFrequencies(::std::vector<int32_t>* _aidl_return) override;
};  // class BpConsumerIrService

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BP_CONSUMER_IR_SERVICE_H_
