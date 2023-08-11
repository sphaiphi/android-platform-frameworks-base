#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_DOCKED_STACK_LISTENER_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_DOCKED_STACK_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IDockedStackListener.h>

namespace android {

namespace view {

class BpDockedStackListener : public ::android::BpInterface<IDockedStackListener> {
public:
  explicit BpDockedStackListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDockedStackListener() = default;
  ::android::binder::Status onDividerVisibilityChanged(bool visible) override;
  ::android::binder::Status onDockedStackExistsChanged(bool exists) override;
  ::android::binder::Status onDockedStackMinimizedChanged(bool minimized, int64_t animDuration, bool isHomeStackResizable) override;
  ::android::binder::Status onAdjustedForImeChanged(bool adjustedForIme, int64_t animDuration) override;
  ::android::binder::Status onDockSideChanged(int32_t newDockSide) override;
};  // class BpDockedStackListener

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_DOCKED_STACK_LISTENER_H_
