#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_ON_KEYGUARD_EXIT_RESULT_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_ON_KEYGUARD_EXIT_RESULT_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IOnKeyguardExitResult.h>

namespace android {

namespace view {

class BpOnKeyguardExitResult : public ::android::BpInterface<IOnKeyguardExitResult> {
public:
  explicit BpOnKeyguardExitResult(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpOnKeyguardExitResult() = default;
  ::android::binder::Status onKeyguardExitResult(bool success) override;
};  // class BpOnKeyguardExitResult

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_ON_KEYGUARD_EXIT_RESULT_H_
