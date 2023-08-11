#ifndef AIDL_GENERATED_ANDROID_SERVICE_ATTENTION_BN_ATTENTION_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_ATTENTION_BN_ATTENTION_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/service/attention/IAttentionCallback.h>

namespace android {

namespace service {

namespace attention {

class BnAttentionCallback : public ::android::BnInterface<IAttentionCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnAttentionCallback

}  // namespace attention

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_ATTENTION_BN_ATTENTION_CALLBACK_H_
