#ifndef AIDL_GENERATED_ANDROID_VIEW_I_WINDOW_SESSION_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_WINDOW_SESSION_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IWindowSessionCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(WindowSessionCallback)
  virtual ::android::binder::Status onAnimatorScaleChanged(float scale) = 0;
};  // class IWindowSessionCallback

class IWindowSessionCallbackDefault : public IWindowSessionCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onAnimatorScaleChanged(float scale) override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_WINDOW_SESSION_CALLBACK_H_
