#ifndef AIDL_GENERATED_ANDROID_NET_BP_NETWORK_POLICY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_NET_BP_NETWORK_POLICY_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/net/INetworkPolicyListener.h>

namespace android {

namespace net {

class BpNetworkPolicyListener : public ::android::BpInterface<INetworkPolicyListener> {
public:
  explicit BpNetworkPolicyListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpNetworkPolicyListener() = default;
  ::android::binder::Status onUidRulesChanged(int32_t uid, int32_t uidRules) override;
  ::android::binder::Status onMeteredIfacesChanged(const ::std::vector<::android::String16>& meteredIfaces) override;
  ::android::binder::Status onRestrictBackgroundChanged(bool restrictBackground) override;
  ::android::binder::Status onUidPoliciesChanged(int32_t uid, int32_t uidPolicies) override;
  ::android::binder::Status onSubscriptionOverride(int32_t subId, int32_t overrideMask, int32_t overrideValue) override;
};  // class BpNetworkPolicyListener

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_BP_NETWORK_POLICY_LISTENER_H_
