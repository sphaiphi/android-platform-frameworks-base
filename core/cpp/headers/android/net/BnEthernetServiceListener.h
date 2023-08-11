#ifndef AIDL_GENERATED_ANDROID_NET_BN_ETHERNET_SERVICE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_NET_BN_ETHERNET_SERVICE_LISTENER_H_

#include <binder/IInterface.h>
#include <android/net/IEthernetServiceListener.h>

namespace android {

namespace net {

class BnEthernetServiceListener : public ::android::BnInterface<IEthernetServiceListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnEthernetServiceListener

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_BN_ETHERNET_SERVICE_LISTENER_H_
