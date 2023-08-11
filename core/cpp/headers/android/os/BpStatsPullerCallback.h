#ifndef AIDL_GENERATED_ANDROID_OS_BP_STATS_PULLER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_OS_BP_STATS_PULLER_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/IStatsPullerCallback.h>

namespace android {

namespace os {

class BpStatsPullerCallback : public ::android::BpInterface<IStatsPullerCallback> {
public:
  explicit BpStatsPullerCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpStatsPullerCallback() = default;
  ::android::binder::Status pullData(int32_t atomTag, int64_t elapsedNanos, int64_t wallClocknanos, ::std::vector<::android::os::StatsLogEventWrapper>* _aidl_return) override;
};  // class BpStatsPullerCallback

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_STATS_PULLER_CALLBACK_H_
