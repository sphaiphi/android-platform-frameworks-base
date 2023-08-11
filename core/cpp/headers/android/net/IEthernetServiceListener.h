#ifndef AIDL_GENERATED_ANDROID_NET_I_ETHERNET_SERVICE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_NET_I_ETHERNET_SERVICE_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace net {

class IEthernetServiceListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(EthernetServiceListener)
  virtual ::android::binder::Status onAvailabilityChanged(const ::android::String16& iface, bool isAvailable) = 0;
};  // class IEthernetServiceListener

class IEthernetServiceListenerDefault : public IEthernetServiceListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onAvailabilityChanged(const ::android::String16& iface, bool isAvailable) override;

};

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_I_ETHERNET_SERVICE_LISTENER_H_
