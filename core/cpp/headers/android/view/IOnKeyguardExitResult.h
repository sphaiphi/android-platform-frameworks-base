#ifndef AIDL_GENERATED_ANDROID_VIEW_I_ON_KEYGUARD_EXIT_RESULT_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_ON_KEYGUARD_EXIT_RESULT_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IOnKeyguardExitResult : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(OnKeyguardExitResult)
  virtual ::android::binder::Status onKeyguardExitResult(bool success) = 0;
};  // class IOnKeyguardExitResult

class IOnKeyguardExitResultDefault : public IOnKeyguardExitResult {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onKeyguardExitResult(bool success) override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_ON_KEYGUARD_EXIT_RESULT_H_
