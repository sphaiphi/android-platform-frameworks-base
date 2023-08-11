#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_WINDOW_SESSION_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_WINDOW_SESSION_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IWindowSessionCallback.h>

namespace android {

namespace view {

class BpWindowSessionCallback : public ::android::BpInterface<IWindowSessionCallback> {
public:
  explicit BpWindowSessionCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpWindowSessionCallback() = default;
  ::android::binder::Status onAnimatorScaleChanged(float scale) override;
};  // class BpWindowSessionCallback

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_WINDOW_SESSION_CALLBACK_H_
