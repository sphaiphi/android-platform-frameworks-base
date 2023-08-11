#ifndef AIDL_GENERATED_ANDROID_SERVICE_VR_I_VR_STATE_CALLBACKS_H_
#define AIDL_GENERATED_ANDROID_SERVICE_VR_I_VR_STATE_CALLBACKS_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace service {

namespace vr {

class IVrStateCallbacks : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VrStateCallbacks)
  virtual ::android::binder::Status onVrStateChanged(bool enabled) = 0;
};  // class IVrStateCallbacks

class IVrStateCallbacksDefault : public IVrStateCallbacks {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onVrStateChanged(bool enabled) override;

};

}  // namespace vr

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_VR_I_VR_STATE_CALLBACKS_H_
