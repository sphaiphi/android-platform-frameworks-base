#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_ON_KEYGUARD_EXIT_RESULT_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_ON_KEYGUARD_EXIT_RESULT_H_

#include <binder/IInterface.h>
#include <android/view/IOnKeyguardExitResult.h>

namespace android {

namespace view {

class BnOnKeyguardExitResult : public ::android::BnInterface<IOnKeyguardExitResult> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnOnKeyguardExitResult

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_ON_KEYGUARD_EXIT_RESULT_H_
