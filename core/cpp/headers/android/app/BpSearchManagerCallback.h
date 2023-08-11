#ifndef AIDL_GENERATED_ANDROID_APP_BP_SEARCH_MANAGER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_BP_SEARCH_MANAGER_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/ISearchManagerCallback.h>

namespace android {

namespace app {

class BpSearchManagerCallback : public ::android::BpInterface<ISearchManagerCallback> {
public:
  explicit BpSearchManagerCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpSearchManagerCallback() = default;
  ::android::binder::Status onDismiss() override;
  ::android::binder::Status onCancel() override;
};  // class BpSearchManagerCallback

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BP_SEARCH_MANAGER_CALLBACK_H_
