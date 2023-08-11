#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_DEX_BP_SNAPSHOT_RUNTIME_PROFILE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_DEX_BP_SNAPSHOT_RUNTIME_PROFILE_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/content/pm/dex/ISnapshotRuntimeProfileCallback.h>

namespace android {

namespace content {

namespace pm {

namespace dex {

class BpSnapshotRuntimeProfileCallback : public ::android::BpInterface<ISnapshotRuntimeProfileCallback> {
public:
  explicit BpSnapshotRuntimeProfileCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpSnapshotRuntimeProfileCallback() = default;
  ::android::binder::Status onSuccess(const ::android::os::ParcelFileDescriptor& profileReadFd) override;
  ::android::binder::Status onError(int32_t errCode) override;
};  // class BpSnapshotRuntimeProfileCallback

}  // namespace dex

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_DEX_BP_SNAPSHOT_RUNTIME_PROFILE_CALLBACK_H_
