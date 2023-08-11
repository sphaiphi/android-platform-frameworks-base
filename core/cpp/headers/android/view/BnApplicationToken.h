#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_APPLICATION_TOKEN_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_APPLICATION_TOKEN_H_

#include <binder/IInterface.h>
#include <android/view/IApplicationToken.h>

namespace android {

namespace view {

class BnApplicationToken : public ::android::BnInterface<IApplicationToken> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnApplicationToken

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_APPLICATION_TOKEN_H_
