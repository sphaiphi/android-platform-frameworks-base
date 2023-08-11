#ifndef AIDL_GENERATED_ANDROID_HARDWARE_BN_CONSUMER_IR_SERVICE_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_BN_CONSUMER_IR_SERVICE_H_

#include <binder/IInterface.h>
#include <android/hardware/IConsumerIrService.h>

namespace android {

namespace hardware {

class BnConsumerIrService : public ::android::BnInterface<IConsumerIrService> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnConsumerIrService

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_BN_CONSUMER_IR_SERVICE_H_
