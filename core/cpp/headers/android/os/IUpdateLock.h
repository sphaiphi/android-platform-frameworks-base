#ifndef AIDL_GENERATED_ANDROID_OS_I_UPDATE_LOCK_H_
#define AIDL_GENERATED_ANDROID_OS_I_UPDATE_LOCK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

class IUpdateLock : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(UpdateLock)
  virtual ::android::binder::Status acquireUpdateLock(const ::android::sp<::android::IBinder>& token, const ::android::String16& tag) = 0;
  virtual ::android::binder::Status releaseUpdateLock(const ::android::sp<::android::IBinder>& token) = 0;
};  // class IUpdateLock

class IUpdateLockDefault : public IUpdateLock {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status acquireUpdateLock(const ::android::sp<::android::IBinder>& token, const ::android::String16& tag) override;
  ::android::binder::Status releaseUpdateLock(const ::android::sp<::android::IBinder>& token) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_UPDATE_LOCK_H_
