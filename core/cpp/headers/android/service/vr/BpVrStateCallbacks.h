#ifndef AIDL_GENERATED_ANDROID_SERVICE_VR_BP_VR_STATE_CALLBACKS_H_
#define AIDL_GENERATED_ANDROID_SERVICE_VR_BP_VR_STATE_CALLBACKS_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/vr/IVrStateCallbacks.h>

namespace android {

namespace service {

namespace vr {

class BpVrStateCallbacks : public ::android::BpInterface<IVrStateCallbacks> {
public:
  explicit BpVrStateCallbacks(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpVrStateCallbacks() = default;
  ::android::binder::Status onVrStateChanged(bool enabled) override;
};  // class BpVrStateCallbacks

}  // namespace vr

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_VR_BP_VR_STATE_CALLBACKS_H_
