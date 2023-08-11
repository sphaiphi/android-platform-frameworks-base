#ifndef AIDL_GENERATED_ANDROID_OS_BP_SCHEDULING_POLICY_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_BP_SCHEDULING_POLICY_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/ISchedulingPolicyService.h>

namespace android {

namespace os {

class BpSchedulingPolicyService : public ::android::BpInterface<ISchedulingPolicyService> {
public:
  explicit BpSchedulingPolicyService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpSchedulingPolicyService() = default;
  ::android::binder::Status requestPriority(int32_t pid, int32_t tid, int32_t prio, bool isForApp, int32_t* _aidl_return) override;
  ::android::binder::Status requestCpusetBoost(bool enable, const ::android::sp<::android::IBinder>& client, int32_t* _aidl_return) override;
};  // class BpSchedulingPolicyService

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_SCHEDULING_POLICY_SERVICE_H_
