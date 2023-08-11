#ifndef AIDL_GENERATED_ANDROID_SERVICE_QUICKSETTINGS_BN_Q_S_TILE_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_QUICKSETTINGS_BN_Q_S_TILE_SERVICE_H_

#include <binder/IInterface.h>
#include <android/service/quicksettings/IQSTileService.h>

namespace android {

namespace service {

namespace quicksettings {

class BnQSTileService : public ::android::BnInterface<IQSTileService> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnQSTileService

}  // namespace quicksettings

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_QUICKSETTINGS_BN_Q_S_TILE_SERVICE_H_
