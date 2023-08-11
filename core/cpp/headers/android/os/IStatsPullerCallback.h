#ifndef AIDL_GENERATED_ANDROID_OS_I_STATS_PULLER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_OS_I_STATS_PULLER_CALLBACK_H_

#include <android/os/StatsLogEventWrapper.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace os {

class IStatsPullerCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(StatsPullerCallback)
  virtual ::android::binder::Status pullData(int32_t atomTag, int64_t elapsedNanos, int64_t wallClocknanos, ::std::vector<::android::os::StatsLogEventWrapper>* _aidl_return) = 0;
};  // class IStatsPullerCallback

class IStatsPullerCallbackDefault : public IStatsPullerCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status pullData(int32_t atomTag, int64_t elapsedNanos, int64_t wallClocknanos, ::std::vector<::android::os::StatsLogEventWrapper>* _aidl_return) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_STATS_PULLER_CALLBACK_H_
