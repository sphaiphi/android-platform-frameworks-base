#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_INPUT_MONITOR_HOST_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_INPUT_MONITOR_HOST_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IInputMonitorHost.h>

namespace android {

namespace view {

class BpInputMonitorHost : public ::android::BpInterface<IInputMonitorHost> {
public:
  explicit BpInputMonitorHost(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpInputMonitorHost() = default;
  ::android::binder::Status pilferPointers() override;
  ::android::binder::Status dispose() override;
};  // class BpInputMonitorHost

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_INPUT_MONITOR_HOST_H_
