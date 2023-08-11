#ifndef AIDL_GENERATED_ANDROID_APP_BN_UI_MODE_MANAGER_H_
#define AIDL_GENERATED_ANDROID_APP_BN_UI_MODE_MANAGER_H_

#include <binder/IInterface.h>
#include <android/app/IUiModeManager.h>

namespace android {

namespace app {

class BnUiModeManager : public ::android::BnInterface<IUiModeManager> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnUiModeManager

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BN_UI_MODE_MANAGER_H_
