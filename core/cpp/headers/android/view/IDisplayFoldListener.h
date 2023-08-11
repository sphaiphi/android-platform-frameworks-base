#ifndef AIDL_GENERATED_ANDROID_VIEW_I_DISPLAY_FOLD_LISTENER_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_DISPLAY_FOLD_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IDisplayFoldListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DisplayFoldListener)
  virtual ::android::binder::Status onDisplayFoldChanged(int32_t displayId, bool folded) = 0;
};  // class IDisplayFoldListener

class IDisplayFoldListenerDefault : public IDisplayFoldListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onDisplayFoldChanged(int32_t displayId, bool folded) override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_DISPLAY_FOLD_LISTENER_H_
