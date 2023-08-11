#ifndef AIDL_GENERATED_ANDROID_HARDWARE_IRIS_BN_IRIS_SERVICE_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_IRIS_BN_IRIS_SERVICE_H_

#include <binder/IInterface.h>
#include <android/hardware/iris/IIrisService.h>

namespace android {

namespace hardware {

namespace iris {

class BnIrisService : public ::android::BnInterface<IIrisService> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnIrisService

}  // namespace iris

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_IRIS_BN_IRIS_SERVICE_H_
