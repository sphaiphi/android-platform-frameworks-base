#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_BN_OTA_DEXOPT_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_BN_OTA_DEXOPT_H_

#include <binder/IInterface.h>
#include <android/content/pm/IOtaDexopt.h>

namespace android {

namespace content {

namespace pm {

class BnOtaDexopt : public ::android::BnInterface<IOtaDexopt> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnOtaDexopt

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_BN_OTA_DEXOPT_H_
