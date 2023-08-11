#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_WINDOW_ID_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_WINDOW_ID_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IWindowId.h>

namespace android {

namespace view {

class BpWindowId : public ::android::BpInterface<IWindowId> {
public:
  explicit BpWindowId(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpWindowId() = default;
  ::android::binder::Status registerFocusObserver(const ::android::sp<::android::view::IWindowFocusObserver>& observer) override;
  ::android::binder::Status unregisterFocusObserver(const ::android::sp<::android::view::IWindowFocusObserver>& observer) override;
  ::android::binder::Status isFocused(bool* _aidl_return) override;
};  // class BpWindowId

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_WINDOW_ID_H_
