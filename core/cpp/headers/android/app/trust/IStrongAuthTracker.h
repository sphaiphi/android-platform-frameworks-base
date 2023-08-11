#ifndef AIDL_GENERATED_ANDROID_APP_TRUST_I_STRONG_AUTH_TRACKER_H_
#define AIDL_GENERATED_ANDROID_APP_TRUST_I_STRONG_AUTH_TRACKER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

namespace trust {

class IStrongAuthTracker : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(StrongAuthTracker)
  virtual ::android::binder::Status onStrongAuthRequiredChanged(int32_t strongAuthRequired, int32_t userId) = 0;
};  // class IStrongAuthTracker

class IStrongAuthTrackerDefault : public IStrongAuthTracker {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onStrongAuthRequiredChanged(int32_t strongAuthRequired, int32_t userId) override;

};

}  // namespace trust

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_TRUST_I_STRONG_AUTH_TRACKER_H_
