#ifndef AIDL_GENERATED_ANDROID_APP_BP_UID_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_APP_BP_UID_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/IUidObserver.h>

namespace android {

namespace app {

class BpUidObserver : public ::android::BpInterface<IUidObserver> {
public:
  explicit BpUidObserver(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpUidObserver() = default;
  ::android::binder::Status onUidGone(int32_t uid, bool disabled) override;
  ::android::binder::Status onUidActive(int32_t uid) override;
  ::android::binder::Status onUidIdle(int32_t uid, bool disabled) override;
  ::android::binder::Status onUidStateChanged(int32_t uid, int32_t procState, int64_t procStateSeq) override;
  ::android::binder::Status onUidCachedChanged(int32_t uid, bool cached) override;
};  // class BpUidObserver

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BP_UID_OBSERVER_H_
