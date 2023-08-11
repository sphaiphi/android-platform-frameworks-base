#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_PINNED_STACK_CONTROLLER_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_PINNED_STACK_CONTROLLER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IPinnedStackController.h>

namespace android {

namespace view {

class BpPinnedStackController : public ::android::BpInterface<IPinnedStackController> {
public:
  explicit BpPinnedStackController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPinnedStackController() = default;
  ::android::binder::Status setIsMinimized(bool isMinimized) override;
  ::android::binder::Status setMinEdgeSize(int32_t minEdgeSize) override;
  ::android::binder::Status getDisplayRotation(int32_t* _aidl_return) override;
};  // class BpPinnedStackController

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_PINNED_STACK_CONTROLLER_H_
