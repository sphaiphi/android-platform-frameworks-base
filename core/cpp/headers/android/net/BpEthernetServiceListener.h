#ifndef AIDL_GENERATED_ANDROID_NET_BP_ETHERNET_SERVICE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_NET_BP_ETHERNET_SERVICE_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/net/IEthernetServiceListener.h>

namespace android {

namespace net {

class BpEthernetServiceListener : public ::android::BpInterface<IEthernetServiceListener> {
public:
  explicit BpEthernetServiceListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpEthernetServiceListener() = default;
  ::android::binder::Status onAvailabilityChanged(const ::android::String16& iface, bool isAvailable) override;
};  // class BpEthernetServiceListener

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_BP_ETHERNET_SERVICE_LISTENER_H_
