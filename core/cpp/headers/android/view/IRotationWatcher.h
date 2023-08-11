#ifndef AIDL_GENERATED_ANDROID_VIEW_I_ROTATION_WATCHER_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_ROTATION_WATCHER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IRotationWatcher : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RotationWatcher)
  virtual ::android::binder::Status onRotationChanged(int32_t rotation) = 0;
};  // class IRotationWatcher

class IRotationWatcherDefault : public IRotationWatcher {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onRotationChanged(int32_t rotation) override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_ROTATION_WATCHER_H_
