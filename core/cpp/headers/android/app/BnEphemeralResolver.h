#ifndef AIDL_GENERATED_ANDROID_APP_BN_EPHEMERAL_RESOLVER_H_
#define AIDL_GENERATED_ANDROID_APP_BN_EPHEMERAL_RESOLVER_H_

#include <binder/IInterface.h>
#include <android/app/IEphemeralResolver.h>

namespace android {

namespace app {

class BnEphemeralResolver : public ::android::BnInterface<IEphemeralResolver> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnEphemeralResolver

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BN_EPHEMERAL_RESOLVER_H_
