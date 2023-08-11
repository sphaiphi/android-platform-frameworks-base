#ifndef AIDL_GENERATED_ANDROID_SERVICE_DREAMS_BN_DREAM_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_DREAMS_BN_DREAM_SERVICE_H_

#include <binder/IInterface.h>
#include <android/service/dreams/IDreamService.h>

namespace android {

namespace service {

namespace dreams {

class BnDreamService : public ::android::BnInterface<IDreamService> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnDreamService

}  // namespace dreams

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_DREAMS_BN_DREAM_SERVICE_H_
