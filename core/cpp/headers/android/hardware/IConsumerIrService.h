#ifndef AIDL_GENERATED_ANDROID_HARDWARE_I_CONSUMER_IR_SERVICE_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_I_CONSUMER_IR_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace hardware {

class IConsumerIrService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(ConsumerIrService)
  virtual ::android::binder::Status hasIrEmitter(bool* _aidl_return) = 0;
  virtual ::android::binder::Status transmit(const ::android::String16& packageName, int32_t carrierFrequency, const ::std::vector<int32_t>& pattern) = 0;
  virtual ::android::binder::Status getCarrierFrequencies(::std::vector<int32_t>* _aidl_return) = 0;
};  // class IConsumerIrService

class IConsumerIrServiceDefault : public IConsumerIrService {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status hasIrEmitter(bool* _aidl_return) override;
  ::android::binder::Status transmit(const ::android::String16& packageName, int32_t carrierFrequency, const ::std::vector<int32_t>& pattern) override;
  ::android::binder::Status getCarrierFrequencies(::std::vector<int32_t>* _aidl_return) override;

};

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_I_CONSUMER_IR_SERVICE_H_
