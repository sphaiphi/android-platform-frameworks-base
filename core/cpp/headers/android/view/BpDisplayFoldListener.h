#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_DISPLAY_FOLD_LISTENER_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_DISPLAY_FOLD_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IDisplayFoldListener.h>

namespace android {

namespace view {

class BpDisplayFoldListener : public ::android::BpInterface<IDisplayFoldListener> {
public:
  explicit BpDisplayFoldListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDisplayFoldListener() = default;
  ::android::binder::Status onDisplayFoldChanged(int32_t displayId, bool folded) override;
};  // class BpDisplayFoldListener

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_DISPLAY_FOLD_LISTENER_H_
