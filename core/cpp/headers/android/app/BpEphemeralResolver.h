#ifndef AIDL_GENERATED_ANDROID_APP_BP_EPHEMERAL_RESOLVER_H_
#define AIDL_GENERATED_ANDROID_APP_BP_EPHEMERAL_RESOLVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/IEphemeralResolver.h>

namespace android {

namespace app {

class BpEphemeralResolver : public ::android::BpInterface<IEphemeralResolver> {
public:
  explicit BpEphemeralResolver(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpEphemeralResolver() = default;
  ::android::binder::Status getEphemeralResolveInfoList(const ::android::sp<::android::os::IRemoteCallback>& callback, const ::std::vector<int32_t>& digestPrefix, int32_t sequence) override;
  ::android::binder::Status getEphemeralIntentFilterList(const ::android::sp<::android::os::IRemoteCallback>& callback, const ::android::String16& hostName, int32_t sequence) override;
};  // class BpEphemeralResolver

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BP_EPHEMERAL_RESOLVER_H_
