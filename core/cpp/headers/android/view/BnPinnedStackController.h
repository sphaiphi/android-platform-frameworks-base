#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_PINNED_STACK_CONTROLLER_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_PINNED_STACK_CONTROLLER_H_

#include <binder/IInterface.h>
#include <android/view/IPinnedStackController.h>

namespace android {

namespace view {

class BnPinnedStackController : public ::android::BnInterface<IPinnedStackController> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnPinnedStackController

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_PINNED_STACK_CONTROLLER_H_
