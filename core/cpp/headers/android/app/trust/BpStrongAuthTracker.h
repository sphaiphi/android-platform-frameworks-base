#ifndef AIDL_GENERATED_ANDROID_APP_TRUST_BP_STRONG_AUTH_TRACKER_H_
#define AIDL_GENERATED_ANDROID_APP_TRUST_BP_STRONG_AUTH_TRACKER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/trust/IStrongAuthTracker.h>

namespace android {

namespace app {

namespace trust {

class BpStrongAuthTracker : public ::android::BpInterface<IStrongAuthTracker> {
public:
  explicit BpStrongAuthTracker(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpStrongAuthTracker() = default;
  ::android::binder::Status onStrongAuthRequiredChanged(int32_t strongAuthRequired, int32_t userId) override;
};  // class BpStrongAuthTracker

}  // namespace trust

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_TRUST_BP_STRONG_AUTH_TRACKER_H_
