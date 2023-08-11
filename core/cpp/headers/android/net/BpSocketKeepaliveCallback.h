#ifndef AIDL_GENERATED_ANDROID_NET_BP_SOCKET_KEEPALIVE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_NET_BP_SOCKET_KEEPALIVE_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/net/ISocketKeepaliveCallback.h>

namespace android {

namespace net {

class BpSocketKeepaliveCallback : public ::android::BpInterface<ISocketKeepaliveCallback> {
public:
  explicit BpSocketKeepaliveCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpSocketKeepaliveCallback() = default;
  ::android::binder::Status onStarted(int32_t slot) override;
  ::android::binder::Status onStopped() override;
  ::android::binder::Status onError(int32_t error) override;
  ::android::binder::Status onDataReceived() override;
};  // class BpSocketKeepaliveCallback

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_BP_SOCKET_KEEPALIVE_CALLBACK_H_
