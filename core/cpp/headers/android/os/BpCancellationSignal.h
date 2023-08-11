#ifndef AIDL_GENERATED_ANDROID_OS_BP_CANCELLATION_SIGNAL_H_
#define AIDL_GENERATED_ANDROID_OS_BP_CANCELLATION_SIGNAL_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/ICancellationSignal.h>

namespace android {

namespace os {

class BpCancellationSignal : public ::android::BpInterface<ICancellationSignal> {
public:
  explicit BpCancellationSignal(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCancellationSignal() = default;
  ::android::binder::Status cancel() override;
};  // class BpCancellationSignal

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_CANCELLATION_SIGNAL_H_
