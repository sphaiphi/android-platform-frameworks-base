#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_WINDOW_FOCUS_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_WINDOW_FOCUS_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IWindowFocusObserver.h>

namespace android {

namespace view {

class BpWindowFocusObserver : public ::android::BpInterface<IWindowFocusObserver> {
public:
  explicit BpWindowFocusObserver(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpWindowFocusObserver() = default;
  ::android::binder::Status focusGained(const ::android::sp<::android::IBinder>& inputToken) override;
  ::android::binder::Status focusLost(const ::android::sp<::android::IBinder>& inputToken) override;
};  // class BpWindowFocusObserver

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_WINDOW_FOCUS_OBSERVER_H_
