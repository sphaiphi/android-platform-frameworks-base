#ifndef AIDL_GENERATED_ANDROID_APP_TRUST_BN_STRONG_AUTH_TRACKER_H_
#define AIDL_GENERATED_ANDROID_APP_TRUST_BN_STRONG_AUTH_TRACKER_H_

#include <binder/IInterface.h>
#include <android/app/trust/IStrongAuthTracker.h>

namespace android {

namespace app {

namespace trust {

class BnStrongAuthTracker : public ::android::BnInterface<IStrongAuthTracker> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnStrongAuthTracker

}  // namespace trust

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_TRUST_BN_STRONG_AUTH_TRACKER_H_
