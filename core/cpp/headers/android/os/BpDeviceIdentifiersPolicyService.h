#ifndef AIDL_GENERATED_ANDROID_OS_BP_DEVICE_IDENTIFIERS_POLICY_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_BP_DEVICE_IDENTIFIERS_POLICY_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/IDeviceIdentifiersPolicyService.h>

namespace android {

namespace os {

class BpDeviceIdentifiersPolicyService : public ::android::BpInterface<IDeviceIdentifiersPolicyService> {
public:
  explicit BpDeviceIdentifiersPolicyService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDeviceIdentifiersPolicyService() = default;
  ::android::binder::Status getSerial(::android::String16* _aidl_return) override;
  ::android::binder::Status getSerialForPackage(const ::android::String16& callingPackage, ::android::String16* _aidl_return) override;
};  // class BpDeviceIdentifiersPolicyService

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_DEVICE_IDENTIFIERS_POLICY_SERVICE_H_
