#ifndef AIDL_GENERATED_ANDROID_NET_I_SOCKET_KEEPALIVE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_NET_I_SOCKET_KEEPALIVE_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace net {

class ISocketKeepaliveCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(SocketKeepaliveCallback)
  virtual ::android::binder::Status onStarted(int32_t slot) = 0;
  virtual ::android::binder::Status onStopped() = 0;
  virtual ::android::binder::Status onError(int32_t error) = 0;
  virtual ::android::binder::Status onDataReceived() = 0;
};  // class ISocketKeepaliveCallback

class ISocketKeepaliveCallbackDefault : public ISocketKeepaliveCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onStarted(int32_t slot) override;
  ::android::binder::Status onStopped() override;
  ::android::binder::Status onError(int32_t error) override;
  ::android::binder::Status onDataReceived() override;

};

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_I_SOCKET_KEEPALIVE_CALLBACK_H_
