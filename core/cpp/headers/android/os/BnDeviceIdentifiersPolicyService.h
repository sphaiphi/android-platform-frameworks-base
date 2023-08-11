#ifndef AIDL_GENERATED_ANDROID_OS_BN_DEVICE_IDENTIFIERS_POLICY_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_BN_DEVICE_IDENTIFIERS_POLICY_SERVICE_H_

#include <binder/IInterface.h>
#include <android/os/IDeviceIdentifiersPolicyService.h>

namespace android {

namespace os {

class BnDeviceIdentifiersPolicyService : public ::android::BnInterface<IDeviceIdentifiersPolicyService> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnDeviceIdentifiersPolicyService

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_DEVICE_IDENTIFIERS_POLICY_SERVICE_H_
