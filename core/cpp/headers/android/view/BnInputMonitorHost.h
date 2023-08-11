#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_INPUT_MONITOR_HOST_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_INPUT_MONITOR_HOST_H_

#include <binder/IInterface.h>
#include <android/view/IInputMonitorHost.h>

namespace android {

namespace view {

class BnInputMonitorHost : public ::android::BnInterface<IInputMonitorHost> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnInputMonitorHost

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_INPUT_MONITOR_HOST_H_
