#ifndef AIDL_GENERATED_ANDROID_APP_BP_UI_MODE_MANAGER_H_
#define AIDL_GENERATED_ANDROID_APP_BP_UI_MODE_MANAGER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/IUiModeManager.h>

namespace android {

namespace app {

class BpUiModeManager : public ::android::BpInterface<IUiModeManager> {
public:
  explicit BpUiModeManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpUiModeManager() = default;
  ::android::binder::Status enableCarMode(int32_t flags) override;
  ::android::binder::Status disableCarMode(int32_t flags) override;
  ::android::binder::Status getCurrentModeType(int32_t* _aidl_return) override;
  ::android::binder::Status setNightMode(int32_t mode) override;
  ::android::binder::Status getNightMode(int32_t* _aidl_return) override;
  ::android::binder::Status isUiModeLocked(bool* _aidl_return) override;
  ::android::binder::Status isNightModeLocked(bool* _aidl_return) override;
  ::android::binder::Status setNightModeActivated(bool active, bool* _aidl_return) override;
};  // class BpUiModeManager

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BP_UI_MODE_MANAGER_H_
