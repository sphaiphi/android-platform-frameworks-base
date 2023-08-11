#ifndef AIDL_GENERATED_ANDROID_SERVICE_QUICKSETTINGS_I_Q_S_TILE_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_QUICKSETTINGS_I_Q_S_TILE_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace service {

namespace quicksettings {

class IQSTileService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(QSTileService)
  virtual ::android::binder::Status onTileAdded() = 0;
  virtual ::android::binder::Status onTileRemoved() = 0;
  virtual ::android::binder::Status onStartListening() = 0;
  virtual ::android::binder::Status onStopListening() = 0;
  virtual ::android::binder::Status onClick(const ::android::sp<::android::IBinder>& wtoken) = 0;
  virtual ::android::binder::Status onUnlockComplete() = 0;
};  // class IQSTileService

class IQSTileServiceDefault : public IQSTileService {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onTileAdded() override;
  ::android::binder::Status onTileRemoved() override;
  ::android::binder::Status onStartListening() override;
  ::android::binder::Status onStopListening() override;
  ::android::binder::Status onClick(const ::android::sp<::android::IBinder>& wtoken) override;
  ::android::binder::Status onUnlockComplete() override;

};

}  // namespace quicksettings

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_QUICKSETTINGS_I_Q_S_TILE_SERVICE_H_
