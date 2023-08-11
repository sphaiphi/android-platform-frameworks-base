#ifndef AIDL_GENERATED_ANDROID_DEBUG_BN_ADB_MANAGER_H_
#define AIDL_GENERATED_ANDROID_DEBUG_BN_ADB_MANAGER_H_

#include <binder/IInterface.h>
#include <android/debug/IAdbManager.h>

namespace android {

namespace debug {

class BnAdbManager : public ::android::BnInterface<IAdbManager> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnAdbManager

}  // namespace debug

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_DEBUG_BN_ADB_MANAGER_H_
