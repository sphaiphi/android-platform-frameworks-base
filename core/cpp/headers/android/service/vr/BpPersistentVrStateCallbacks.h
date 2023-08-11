#ifndef AIDL_GENERATED_ANDROID_SERVICE_VR_BP_PERSISTENT_VR_STATE_CALLBACKS_H_
#define AIDL_GENERATED_ANDROID_SERVICE_VR_BP_PERSISTENT_VR_STATE_CALLBACKS_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/vr/IPersistentVrStateCallbacks.h>

namespace android {

namespace service {

namespace vr {

class BpPersistentVrStateCallbacks : public ::android::BpInterface<IPersistentVrStateCallbacks> {
public:
  explicit BpPersistentVrStateCallbacks(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPersistentVrStateCallbacks() = default;
  ::android::binder::Status onPersistentVrStateChanged(bool enabled) override;
};  // class BpPersistentVrStateCallbacks

}  // namespace vr

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_VR_BP_PERSISTENT_VR_STATE_CALLBACKS_H_
