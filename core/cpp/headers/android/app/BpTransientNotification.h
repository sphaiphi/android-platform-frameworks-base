#ifndef AIDL_GENERATED_ANDROID_APP_BP_TRANSIENT_NOTIFICATION_H_
#define AIDL_GENERATED_ANDROID_APP_BP_TRANSIENT_NOTIFICATION_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/app/ITransientNotification.h>

namespace android {

namespace app {

class BpTransientNotification : public ::android::BpInterface<ITransientNotification> {
public:
  explicit BpTransientNotification(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpTransientNotification() = default;
  ::android::binder::Status show(const ::android::sp<::android::IBinder>& windowToken) override;
  ::android::binder::Status hide() override;
};  // class BpTransientNotification

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BP_TRANSIENT_NOTIFICATION_H_
