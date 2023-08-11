#ifndef AIDL_GENERATED_ANDROID_VIEW_I_DOCKED_STACK_LISTENER_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_DOCKED_STACK_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IDockedStackListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DockedStackListener)
  virtual ::android::binder::Status onDividerVisibilityChanged(bool visible) = 0;
  virtual ::android::binder::Status onDockedStackExistsChanged(bool exists) = 0;
  virtual ::android::binder::Status onDockedStackMinimizedChanged(bool minimized, int64_t animDuration, bool isHomeStackResizable) = 0;
  virtual ::android::binder::Status onAdjustedForImeChanged(bool adjustedForIme, int64_t animDuration) = 0;
  virtual ::android::binder::Status onDockSideChanged(int32_t newDockSide) = 0;
};  // class IDockedStackListener

class IDockedStackListenerDefault : public IDockedStackListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onDividerVisibilityChanged(bool visible) override;
  ::android::binder::Status onDockedStackExistsChanged(bool exists) override;
  ::android::binder::Status onDockedStackMinimizedChanged(bool minimized, int64_t animDuration, bool isHomeStackResizable) override;
  ::android::binder::Status onAdjustedForImeChanged(bool adjustedForIme, int64_t animDuration) override;
  ::android::binder::Status onDockSideChanged(int32_t newDockSide) override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_DOCKED_STACK_LISTENER_H_
