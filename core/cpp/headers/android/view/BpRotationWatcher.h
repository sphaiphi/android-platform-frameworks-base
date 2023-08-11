#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_ROTATION_WATCHER_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_ROTATION_WATCHER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IRotationWatcher.h>

namespace android {

namespace view {

class BpRotationWatcher : public ::android::BpInterface<IRotationWatcher> {
public:
  explicit BpRotationWatcher(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpRotationWatcher() = default;
  ::android::binder::Status onRotationChanged(int32_t rotation) override;
};  // class BpRotationWatcher

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_ROTATION_WATCHER_H_
