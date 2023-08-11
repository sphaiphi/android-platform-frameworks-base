#ifndef AIDL_GENERATED_ANDROID_OS_I_NETWORK_ACTIVITY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_I_NETWORK_ACTIVITY_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

class INetworkActivityListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(NetworkActivityListener)
  virtual ::android::binder::Status onNetworkActive() = 0;
};  // class INetworkActivityListener

class INetworkActivityListenerDefault : public INetworkActivityListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onNetworkActive() override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_NETWORK_ACTIVITY_LISTENER_H_
