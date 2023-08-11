#ifndef AIDL_GENERATED_ANDROID_OS_BP_UPDATE_LOCK_H_
#define AIDL_GENERATED_ANDROID_OS_BP_UPDATE_LOCK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/IUpdateLock.h>

namespace android {

namespace os {

class BpUpdateLock : public ::android::BpInterface<IUpdateLock> {
public:
  explicit BpUpdateLock(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpUpdateLock() = default;
  ::android::binder::Status acquireUpdateLock(const ::android::sp<::android::IBinder>& token, const ::android::String16& tag) override;
  ::android::binder::Status releaseUpdateLock(const ::android::sp<::android::IBinder>& token) override;
};  // class BpUpdateLock

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_UPDATE_LOCK_H_
