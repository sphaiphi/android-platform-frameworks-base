#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_DEX_I_SNAPSHOT_RUNTIME_PROFILE_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_DEX_I_SNAPSHOT_RUNTIME_PROFILE_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/ParcelFileDescriptor.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace content {

namespace pm {

namespace dex {

class ISnapshotRuntimeProfileCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(SnapshotRuntimeProfileCallback)
  virtual ::android::binder::Status onSuccess(const ::android::os::ParcelFileDescriptor& profileReadFd) = 0;
  virtual ::android::binder::Status onError(int32_t errCode) = 0;
};  // class ISnapshotRuntimeProfileCallback

class ISnapshotRuntimeProfileCallbackDefault : public ISnapshotRuntimeProfileCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onSuccess(const ::android::os::ParcelFileDescriptor& profileReadFd) override;
  ::android::binder::Status onError(int32_t errCode) override;

};

}  // namespace dex

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_DEX_I_SNAPSHOT_RUNTIME_PROFILE_CALLBACK_H_
