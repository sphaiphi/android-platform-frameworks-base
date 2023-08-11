#ifndef AIDL_GENERATED_ANDROID_NET_BP_NETD_EVENT_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_NET_BP_NETD_EVENT_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/net/INetdEventCallback.h>

namespace android {

namespace net {

class BpNetdEventCallback : public ::android::BpInterface<INetdEventCallback> {
public:
  explicit BpNetdEventCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpNetdEventCallback() = default;
  ::android::binder::Status onDnsEvent(int32_t netId, int32_t eventType, int32_t returnCode, const ::android::String16& hostname, const ::std::vector<::android::String16>& ipAddresses, int32_t ipAddressesCount, int64_t timestamp, int32_t uid) override;
  ::android::binder::Status onNat64PrefixEvent(int32_t netId, bool added, const ::std::string& prefixString, int32_t prefixLength) override;
  ::android::binder::Status onPrivateDnsValidationEvent(int32_t netId, const ::android::String16& ipAddress, const ::android::String16& hostname, bool validated) override;
  ::android::binder::Status onConnectEvent(const ::android::String16& ipAddr, int32_t port, int64_t timestamp, int32_t uid) override;
};  // class BpNetdEventCallback

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_BP_NETD_EVENT_CALLBACK_H_
