#ifndef AIDL_GENERATED_ANDROID_NET_BN_SOCKET_KEEPALIVE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_NET_BN_SOCKET_KEEPALIVE_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/net/ISocketKeepaliveCallback.h>

namespace android {

namespace net {

class BnSocketKeepaliveCallback : public ::android::BnInterface<ISocketKeepaliveCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnSocketKeepaliveCallback

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_BN_SOCKET_KEEPALIVE_CALLBACK_H_
