#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_ROTATION_WATCHER_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_ROTATION_WATCHER_H_

#include <binder/IInterface.h>
#include <android/view/IRotationWatcher.h>

namespace android {

namespace view {

class BnRotationWatcher : public ::android::BnInterface<IRotationWatcher> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnRotationWatcher

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_ROTATION_WATCHER_H_
