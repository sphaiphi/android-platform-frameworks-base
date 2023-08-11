#ifndef AIDL_GENERATED_ANDROID_OS_BP_NETWORK_ACTIVITY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_BP_NETWORK_ACTIVITY_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/INetworkActivityListener.h>

namespace android {

namespace os {

class BpNetworkActivityListener : public ::android::BpInterface<INetworkActivityListener> {
public:
  explicit BpNetworkActivityListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpNetworkActivityListener() = default;
  ::android::binder::Status onNetworkActive() override;
};  // class BpNetworkActivityListener

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_NETWORK_ACTIVITY_LISTENER_H_
