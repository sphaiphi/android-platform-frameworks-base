#ifndef AIDL_GENERATED_ANDROID_COMPANION_BN_COMPANION_DEVICE_DISCOVERY_SERVICE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_COMPANION_BN_COMPANION_DEVICE_DISCOVERY_SERVICE_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/companion/ICompanionDeviceDiscoveryServiceCallback.h>

namespace android {

namespace companion {

class BnCompanionDeviceDiscoveryServiceCallback : public ::android::BnInterface<ICompanionDeviceDiscoveryServiceCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnCompanionDeviceDiscoveryServiceCallback

}  // namespace companion

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_COMPANION_BN_COMPANION_DEVICE_DISCOVERY_SERVICE_CALLBACK_H_
