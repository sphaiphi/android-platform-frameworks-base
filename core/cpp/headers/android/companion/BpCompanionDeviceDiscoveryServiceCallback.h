#ifndef AIDL_GENERATED_ANDROID_COMPANION_BP_COMPANION_DEVICE_DISCOVERY_SERVICE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_COMPANION_BP_COMPANION_DEVICE_DISCOVERY_SERVICE_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/companion/ICompanionDeviceDiscoveryServiceCallback.h>

namespace android {

namespace companion {

class BpCompanionDeviceDiscoveryServiceCallback : public ::android::BpInterface<ICompanionDeviceDiscoveryServiceCallback> {
public:
  explicit BpCompanionDeviceDiscoveryServiceCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCompanionDeviceDiscoveryServiceCallback() = default;
  ::android::binder::Status onDeviceSelected(const ::android::String16& packageName, int32_t userId, const ::android::String16& deviceAddress) override;
  ::android::binder::Status onDeviceSelectionCancel() override;
};  // class BpCompanionDeviceDiscoveryServiceCallback

}  // namespace companion

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_COMPANION_BP_COMPANION_DEVICE_DISCOVERY_SERVICE_CALLBACK_H_
