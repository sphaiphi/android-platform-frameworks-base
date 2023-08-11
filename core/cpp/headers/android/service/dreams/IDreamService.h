#ifndef AIDL_GENERATED_ANDROID_SERVICE_DREAMS_I_DREAM_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_DREAMS_I_DREAM_SERVICE_H_

#include <android/os/IRemoteCallback.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace service {

namespace dreams {

class IDreamService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DreamService)
  virtual ::android::binder::Status attach(const ::android::sp<::android::IBinder>& windowToken, bool canDoze, const ::android::sp<::android::os::IRemoteCallback>& started) = 0;
  virtual ::android::binder::Status detach() = 0;
  virtual ::android::binder::Status wakeUp() = 0;
};  // class IDreamService

class IDreamServiceDefault : public IDreamService {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status attach(const ::android::sp<::android::IBinder>& windowToken, bool canDoze, const ::android::sp<::android::os::IRemoteCallback>& started) override;
  ::android::binder::Status detach() override;
  ::android::binder::Status wakeUp() override;

};

}  // namespace dreams

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_DREAMS_I_DREAM_SERVICE_H_
