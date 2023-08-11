#ifndef AIDL_GENERATED_ANDROID_APP_BN_SEARCH_MANAGER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_BN_SEARCH_MANAGER_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/app/ISearchManagerCallback.h>

namespace android {

namespace app {

class BnSearchManagerCallback : public ::android::BnInterface<ISearchManagerCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnSearchManagerCallback

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BN_SEARCH_MANAGER_CALLBACK_H_
