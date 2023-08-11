#ifndef AIDL_GENERATED_ANDROID_SERVICE_DREAMS_BP_DREAM_SERVICE_H_
#define AIDL_GENERATED_ANDROID_SERVICE_DREAMS_BP_DREAM_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/dreams/IDreamService.h>

namespace android {

namespace service {

namespace dreams {

class BpDreamService : public ::android::BpInterface<IDreamService> {
public:
  explicit BpDreamService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDreamService() = default;
  ::android::binder::Status attach(const ::android::sp<::android::IBinder>& windowToken, bool canDoze, const ::android::sp<::android::os::IRemoteCallback>& started) override;
  ::android::binder::Status detach() override;
  ::android::binder::Status wakeUp() override;
};  // class BpDreamService

}  // namespace dreams

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_DREAMS_BP_DREAM_SERVICE_H_
