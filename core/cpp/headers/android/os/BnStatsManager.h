#ifndef AIDL_GENERATED_ANDROID_OS_BN_STATS_MANAGER_H_
#define AIDL_GENERATED_ANDROID_OS_BN_STATS_MANAGER_H_

#include <binder/IInterface.h>
#include <android/os/IStatsManager.h>

namespace android {

namespace os {

class BnStatsManager : public ::android::BnInterface<IStatsManager> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnStatsManager

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_STATS_MANAGER_H_
