#ifndef AIDL_GENERATED_ANDROID_OS_BN_NETWORK_ACTIVITY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_BN_NETWORK_ACTIVITY_LISTENER_H_

#include <binder/IInterface.h>
#include <android/os/INetworkActivityListener.h>

namespace android {

namespace os {

class BnNetworkActivityListener : public ::android::BnInterface<INetworkActivityListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnNetworkActivityListener

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_NETWORK_ACTIVITY_LISTENER_H_
