#ifndef AIDL_GENERATED_ANDROID_NET_BN_CAPTIVE_PORTAL_H_
#define AIDL_GENERATED_ANDROID_NET_BN_CAPTIVE_PORTAL_H_

#include <binder/IInterface.h>
#include <android/net/ICaptivePortal.h>

namespace android {

namespace net {

class BnCaptivePortal : public ::android::BnInterface<ICaptivePortal> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnCaptivePortal

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_BN_CAPTIVE_PORTAL_H_
