#ifndef AIDL_GENERATED_ANDROID_APP_I_EPHEMERAL_RESOLVER_H_
#define AIDL_GENERATED_ANDROID_APP_I_EPHEMERAL_RESOLVER_H_

#include <android/os/IRemoteCallback.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace app {

class IEphemeralResolver : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(EphemeralResolver)
  virtual ::android::binder::Status getEphemeralResolveInfoList(const ::android::sp<::android::os::IRemoteCallback>& callback, const ::std::vector<int32_t>& digestPrefix, int32_t sequence) = 0;
  virtual ::android::binder::Status getEphemeralIntentFilterList(const ::android::sp<::android::os::IRemoteCallback>& callback, const ::android::String16& hostName, int32_t sequence) = 0;
};  // class IEphemeralResolver

class IEphemeralResolverDefault : public IEphemeralResolver {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status getEphemeralResolveInfoList(const ::android::sp<::android::os::IRemoteCallback>& callback, const ::std::vector<int32_t>& digestPrefix, int32_t sequence) override;
  ::android::binder::Status getEphemeralIntentFilterList(const ::android::sp<::android::os::IRemoteCallback>& callback, const ::android::String16& hostName, int32_t sequence) override;

};

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_I_EPHEMERAL_RESOLVER_H_
