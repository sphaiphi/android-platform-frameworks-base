#ifndef AIDL_GENERATED_ANDROID_COMPANION_I_COMPANION_DEVICE_DISCOVERY_SERVICE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_COMPANION_I_COMPANION_DEVICE_DISCOVERY_SERVICE_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace companion {

class ICompanionDeviceDiscoveryServiceCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CompanionDeviceDiscoveryServiceCallback)
  virtual ::android::binder::Status onDeviceSelected(const ::android::String16& packageName, int32_t userId, const ::android::String16& deviceAddress) = 0;
  virtual ::android::binder::Status onDeviceSelectionCancel() = 0;
};  // class ICompanionDeviceDiscoveryServiceCallback

class ICompanionDeviceDiscoveryServiceCallbackDefault : public ICompanionDeviceDiscoveryServiceCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onDeviceSelected(const ::android::String16& packageName, int32_t userId, const ::android::String16& deviceAddress) override;
  ::android::binder::Status onDeviceSelectionCancel() override;

};

}  // namespace companion

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_COMPANION_I_COMPANION_DEVICE_DISCOVERY_SERVICE_CALLBACK_H_
