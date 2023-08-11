#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_BP_OTA_DEXOPT_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_BP_OTA_DEXOPT_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/content/pm/IOtaDexopt.h>

namespace android {

namespace content {

namespace pm {

class BpOtaDexopt : public ::android::BpInterface<IOtaDexopt> {
public:
  explicit BpOtaDexopt(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpOtaDexopt() = default;
  ::android::binder::Status prepare() override;
  ::android::binder::Status cleanup() override;
  ::android::binder::Status isDone(bool* _aidl_return) override;
  ::android::binder::Status getProgress(float* _aidl_return) override;
  ::android::binder::Status dexoptNextPackage() override;
  ::android::binder::Status nextDexoptCommand(::android::String16* _aidl_return) override;
};  // class BpOtaDexopt

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_BP_OTA_DEXOPT_H_
