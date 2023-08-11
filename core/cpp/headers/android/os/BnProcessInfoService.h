#ifndef AIDL_GENERATED_ANDROID_OS_BN_PROCESS_INFO_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_BN_PROCESS_INFO_SERVICE_H_

#include <binder/IInterface.h>
#include <android/os/IProcessInfoService.h>

namespace android {

namespace os {

class BnProcessInfoService : public ::android::BnInterface<IProcessInfoService> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnProcessInfoService

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_PROCESS_INFO_SERVICE_H_
