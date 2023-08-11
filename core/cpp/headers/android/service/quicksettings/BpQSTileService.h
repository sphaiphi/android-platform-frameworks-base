#ifndef AIDL_GENERATED_ANDROID_SERVICE_QUICKSETTINGS_BP_Q_S_TILE_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_QUICKSETTINGS_BP_Q_S_TILE_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/quicksettings/IQSTileService.h>

namespace android {

namespace service {

namespace quicksettings {

class BpQSTileService : public ::android::BpInterface<IQSTileService> {
public:
  explicit BpQSTileService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpQSTileService() = default;
  ::android::binder::Status onTileAdded() override;
  ::android::binder::Status onTileRemoved() override;
  ::android::binder::Status onStartListening() override;
  ::android::binder::Status onStopListening() override;
  ::android::binder::Status onClick(const ::android::sp<::android::IBinder>& wtoken) override;
  ::android::binder::Status onUnlockComplete() override;
};  // class BpQSTileService

}  // namespace quicksettings

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_QUICKSETTINGS_BP_Q_S_TILE_SERVICE_H_
