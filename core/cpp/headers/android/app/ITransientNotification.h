#ifndef AIDL_GENERATED_ANDROID_APP_I_TRANSIENT_NOTIFICATION_H_
#define AIDL_GENERATED_ANDROID_APP_I_TRANSIENT_NOTIFICATION_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

class ITransientNotification : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(TransientNotification)
  virtual ::android::binder::Status show(const ::android::sp<::android::IBinder>& windowToken) = 0;
  virtual ::android::binder::Status hide() = 0;
};  // class ITransientNotification

class ITransientNotificationDefault : public ITransientNotification {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status show(const ::android::sp<::android::IBinder>& windowToken) override;
  ::android::binder::Status hide() override;

};

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_I_TRANSIENT_NOTIFICATION_H_
