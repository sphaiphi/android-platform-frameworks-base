#ifndef AIDL_GENERATED_ANDROID_HARDWARE_INPUT_I_TABLET_MODE_CHANGED_LISTENER_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_INPUT_I_TABLET_MODE_CHANGED_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

namespace input {

class ITabletModeChangedListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(TabletModeChangedListener)
  virtual ::android::binder::Status onTabletModeChanged(int64_t whenNanos, bool inTabletMode) = 0;
};  // class ITabletModeChangedListener

class ITabletModeChangedListenerDefault : public ITabletModeChangedListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onTabletModeChanged(int64_t whenNanos, bool inTabletMode) override;

};

}  // namespace input

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_INPUT_I_TABLET_MODE_CHANGED_LISTENER_H_
