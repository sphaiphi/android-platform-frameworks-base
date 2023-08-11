#ifndef AIDL_GENERATED_ANDROID_OS_I_DEVICE_IDENTIFIERS_POLICY_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_I_DEVICE_IDENTIFIERS_POLICY_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

class IDeviceIdentifiersPolicyService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DeviceIdentifiersPolicyService)
  virtual ::android::binder::Status getSerial(::android::String16* _aidl_return) = 0;
  virtual ::android::binder::Status getSerialForPackage(const ::android::String16& callingPackage, ::android::String16* _aidl_return) = 0;
};  // class IDeviceIdentifiersPolicyService

class IDeviceIdentifiersPolicyServiceDefault : public IDeviceIdentifiersPolicyService {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status getSerial(::android::String16* _aidl_return) override;
  ::android::binder::Status getSerialForPackage(const ::android::String16& callingPackage, ::android::String16* _aidl_return) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_DEVICE_IDENTIFIERS_POLICY_SERVICE_H_
