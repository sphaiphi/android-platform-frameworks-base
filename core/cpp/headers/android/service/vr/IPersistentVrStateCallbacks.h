#ifndef AIDL_GENERATED_ANDROID_SERVICE_VR_I_PERSISTENT_VR_STATE_CALLBACKS_H_
#define AIDL_GENERATED_ANDROID_SERVICE_VR_I_PERSISTENT_VR_STATE_CALLBACKS_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace service {

namespace vr {

class IPersistentVrStateCallbacks : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PersistentVrStateCallbacks)
  virtual ::android::binder::Status onPersistentVrStateChanged(bool enabled) = 0;
};  // class IPersistentVrStateCallbacks

class IPersistentVrStateCallbacksDefault : public IPersistentVrStateCallbacks {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onPersistentVrStateChanged(bool enabled) override;

};

}  // namespace vr

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_VR_I_PERSISTENT_VR_STATE_CALLBACKS_H_
