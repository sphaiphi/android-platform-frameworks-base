#ifndef AIDL_GENERATED_ANDROID_NET_BN_NETWORK_POLICY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_NET_BN_NETWORK_POLICY_LISTENER_H_

#include <binder/IInterface.h>
#include <android/net/INetworkPolicyListener.h>

namespace android {

namespace net {

class BnNetworkPolicyListener : public ::android::BnInterface<INetworkPolicyListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnNetworkPolicyListener

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_BN_NETWORK_POLICY_LISTENER_H_
