#ifndef AIDL_GENERATED_ANDROID_SE_OMAPI_BN_SECURE_ELEMENT_LISTENER_H_
#define AIDL_GENERATED_ANDROID_SE_OMAPI_BN_SECURE_ELEMENT_LISTENER_H_

#include <binder/IInterface.h>
#include <android/se/omapi/ISecureElementListener.h>

namespace android {

namespace se {

namespace omapi {

class BnSecureElementListener : public ::android::BnInterface<ISecureElementListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnSecureElementListener

}  // namespace omapi

}  // namespace se

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SE_OMAPI_BN_SECURE_ELEMENT_LISTENER_H_
