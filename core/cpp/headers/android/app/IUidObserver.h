#ifndef AIDL_GENERATED_ANDROID_APP_I_UID_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_APP_I_UID_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

class IUidObserver : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(UidObserver)
  virtual ::android::binder::Status onUidGone(int32_t uid, bool disabled) = 0;
  virtual ::android::binder::Status onUidActive(int32_t uid) = 0;
  virtual ::android::binder::Status onUidIdle(int32_t uid, bool disabled) = 0;
  virtual ::android::binder::Status onUidStateChanged(int32_t uid, int32_t procState, int64_t procStateSeq) = 0;
  virtual ::android::binder::Status onUidCachedChanged(int32_t uid, bool cached) = 0;
};  // class IUidObserver

class IUidObserverDefault : public IUidObserver {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onUidGone(int32_t uid, bool disabled) override;
  ::android::binder::Status onUidActive(int32_t uid) override;
  ::android::binder::Status onUidIdle(int32_t uid, bool disabled) override;
  ::android::binder::Status onUidStateChanged(int32_t uid, int32_t procState, int64_t procStateSeq) override;
  ::android::binder::Status onUidCachedChanged(int32_t uid, bool cached) override;

};

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_I_UID_OBSERVER_H_
