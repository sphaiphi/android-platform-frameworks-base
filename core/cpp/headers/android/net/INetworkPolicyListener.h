#ifndef AIDL_GENERATED_ANDROID_NET_I_NETWORK_POLICY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_NET_I_NETWORK_POLICY_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace net {

class INetworkPolicyListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(NetworkPolicyListener)
  virtual ::android::binder::Status onUidRulesChanged(int32_t uid, int32_t uidRules) = 0;
  virtual ::android::binder::Status onMeteredIfacesChanged(const ::std::vector<::android::String16>& meteredIfaces) = 0;
  virtual ::android::binder::Status onRestrictBackgroundChanged(bool restrictBackground) = 0;
  virtual ::android::binder::Status onUidPoliciesChanged(int32_t uid, int32_t uidPolicies) = 0;
  virtual ::android::binder::Status onSubscriptionOverride(int32_t subId, int32_t overrideMask, int32_t overrideValue) = 0;
};  // class INetworkPolicyListener

class INetworkPolicyListenerDefault : public INetworkPolicyListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onUidRulesChanged(int32_t uid, int32_t uidRules) override;
  ::android::binder::Status onMeteredIfacesChanged(const ::std::vector<::android::String16>& meteredIfaces) override;
  ::android::binder::Status onRestrictBackgroundChanged(bool restrictBackground) override;
  ::android::binder::Status onUidPoliciesChanged(int32_t uid, int32_t uidPolicies) override;
  ::android::binder::Status onSubscriptionOverride(int32_t subId, int32_t overrideMask, int32_t overrideValue) override;

};

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_I_NETWORK_POLICY_LISTENER_H_
