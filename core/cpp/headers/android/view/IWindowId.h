#ifndef AIDL_GENERATED_ANDROID_VIEW_I_WINDOW_ID_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_WINDOW_ID_H_

#include <android/view/IWindowFocusObserver.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IWindowId : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(WindowId)
  virtual ::android::binder::Status registerFocusObserver(const ::android::sp<::android::view::IWindowFocusObserver>& observer) = 0;
  virtual ::android::binder::Status unregisterFocusObserver(const ::android::sp<::android::view::IWindowFocusObserver>& observer) = 0;
  virtual ::android::binder::Status isFocused(bool* _aidl_return) = 0;
};  // class IWindowId

class IWindowIdDefault : public IWindowId {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status registerFocusObserver(const ::android::sp<::android::view::IWindowFocusObserver>& observer) override;
  ::android::binder::Status unregisterFocusObserver(const ::android::sp<::android::view::IWindowFocusObserver>& observer) override;
  ::android::binder::Status isFocused(bool* _aidl_return) override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_WINDOW_ID_H_
