#ifndef AIDL_GENERATED_ANDROID_VIEW_I_PINNED_STACK_CONTROLLER_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_PINNED_STACK_CONTROLLER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IPinnedStackController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PinnedStackController)
  virtual ::android::binder::Status setIsMinimized(bool isMinimized) = 0;
  virtual ::android::binder::Status setMinEdgeSize(int32_t minEdgeSize) = 0;
  virtual ::android::binder::Status getDisplayRotation(int32_t* _aidl_return) = 0;
};  // class IPinnedStackController

class IPinnedStackControllerDefault : public IPinnedStackController {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status setIsMinimized(bool isMinimized) override;
  ::android::binder::Status setMinEdgeSize(int32_t minEdgeSize) override;
  ::android::binder::Status getDisplayRotation(int32_t* _aidl_return) override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_PINNED_STACK_CONTROLLER_H_
