#ifndef AIDL_GENERATED_ANDROID_VIEW_I_WINDOW_FOCUS_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_WINDOW_FOCUS_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IWindowFocusObserver : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(WindowFocusObserver)
  virtual ::android::binder::Status focusGained(const ::android::sp<::android::IBinder>& inputToken) = 0;
  virtual ::android::binder::Status focusLost(const ::android::sp<::android::IBinder>& inputToken) = 0;
};  // class IWindowFocusObserver

class IWindowFocusObserverDefault : public IWindowFocusObserver {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status focusGained(const ::android::sp<::android::IBinder>& inputToken) override;
  ::android::binder::Status focusLost(const ::android::sp<::android::IBinder>& inputToken) override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_WINDOW_FOCUS_OBSERVER_H_
