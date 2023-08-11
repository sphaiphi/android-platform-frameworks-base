#ifndef AIDL_GENERATED_ANDROID_NET_BN_NETD_EVENT_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_NET_BN_NETD_EVENT_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/net/INetdEventCallback.h>

namespace android {

namespace net {

class BnNetdEventCallback : public ::android::BnInterface<INetdEventCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnNetdEventCallback

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_BN_NETD_EVENT_CALLBACK_H_
