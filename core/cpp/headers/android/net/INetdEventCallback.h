#ifndef AIDL_GENERATED_ANDROID_NET_I_NETD_EVENT_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_NET_I_NETD_EVENT_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace net {

class INetdEventCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(NetdEventCallback)
  enum  : int32_t {
    CALLBACK_CALLER_CONNECTIVITY_SERVICE = 0,
    CALLBACK_CALLER_DEVICE_POLICY = 1,
    CALLBACK_CALLER_NETWORK_WATCHLIST = 2,
  };
  virtual ::android::binder::Status onDnsEvent(int32_t netId, int32_t eventType, int32_t returnCode, const ::android::String16& hostname, const ::std::vector<::android::String16>& ipAddresses, int32_t ipAddressesCount, int64_t timestamp, int32_t uid) = 0;
  virtual ::android::binder::Status onNat64PrefixEvent(int32_t netId, bool added, const ::std::string& prefixString, int32_t prefixLength) = 0;
  virtual ::android::binder::Status onPrivateDnsValidationEvent(int32_t netId, const ::android::String16& ipAddress, const ::android::String16& hostname, bool validated) = 0;
  virtual ::android::binder::Status onConnectEvent(const ::android::String16& ipAddr, int32_t port, int64_t timestamp, int32_t uid) = 0;
};  // class INetdEventCallback

class INetdEventCallbackDefault : public INetdEventCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onDnsEvent(int32_t netId, int32_t eventType, int32_t returnCode, const ::android::String16& hostname, const ::std::vector<::android::String16>& ipAddresses, int32_t ipAddressesCount, int64_t timestamp, int32_t uid) override;
  ::android::binder::Status onNat64PrefixEvent(int32_t netId, bool added, const ::std::string& prefixString, int32_t prefixLength) override;
  ::android::binder::Status onPrivateDnsValidationEvent(int32_t netId, const ::android::String16& ipAddress, const ::android::String16& hostname, bool validated) override;
  ::android::binder::Status onConnectEvent(const ::android::String16& ipAddr, int32_t port, int64_t timestamp, int32_t uid) override;

};

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_I_NETD_EVENT_CALLBACK_H_
