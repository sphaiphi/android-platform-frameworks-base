#ifndef AIDL_GENERATED_ANDROID_VIEW_I_INPUT_MONITOR_HOST_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_INPUT_MONITOR_HOST_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IInputMonitorHost : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(InputMonitorHost)
  virtual ::android::binder::Status pilferPointers() = 0;
  virtual ::android::binder::Status dispose() = 0;
};  // class IInputMonitorHost

class IInputMonitorHostDefault : public IInputMonitorHost {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status pilferPointers() override;
  ::android::binder::Status dispose() override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_INPUT_MONITOR_HOST_H_
