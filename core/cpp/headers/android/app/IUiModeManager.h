#ifndef AIDL_GENERATED_ANDROID_APP_I_UI_MODE_MANAGER_H_
#define AIDL_GENERATED_ANDROID_APP_I_UI_MODE_MANAGER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

class IUiModeManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(UiModeManager)
  virtual ::android::binder::Status enableCarMode(int32_t flags) = 0;
  virtual ::android::binder::Status disableCarMode(int32_t flags) = 0;
  virtual ::android::binder::Status getCurrentModeType(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status setNightMode(int32_t mode) = 0;
  virtual ::android::binder::Status getNightMode(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status isUiModeLocked(bool* _aidl_return) = 0;
  virtual ::android::binder::Status isNightModeLocked(bool* _aidl_return) = 0;
  virtual ::android::binder::Status setNightModeActivated(bool active, bool* _aidl_return) = 0;
};  // class IUiModeManager

class IUiModeManagerDefault : public IUiModeManager {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status enableCarMode(int32_t flags) override;
  ::android::binder::Status disableCarMode(int32_t flags) override;
  ::android::binder::Status getCurrentModeType(int32_t* _aidl_return) override;
  ::android::binder::Status setNightMode(int32_t mode) override;
  ::android::binder::Status getNightMode(int32_t* _aidl_return) override;
  ::android::binder::Status isUiModeLocked(bool* _aidl_return) override;
  ::android::binder::Status isNightModeLocked(bool* _aidl_return) override;
  ::android::binder::Status setNightModeActivated(bool active, bool* _aidl_return) override;

};

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_I_UI_MODE_MANAGER_H_
