#ifndef AIDL_GENERATED_ANDROID_OS_I_SCHEDULING_POLICY_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_I_SCHEDULING_POLICY_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

class ISchedulingPolicyService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(SchedulingPolicyService)
  virtual ::android::binder::Status requestPriority(int32_t pid, int32_t tid, int32_t prio, bool isForApp, int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status requestCpusetBoost(bool enable, const ::android::sp<::android::IBinder>& client, int32_t* _aidl_return) = 0;
};  // class ISchedulingPolicyService

class ISchedulingPolicyServiceDefault : public ISchedulingPolicyService {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status requestPriority(int32_t pid, int32_t tid, int32_t prio, bool isForApp, int32_t* _aidl_return) override;
  ::android::binder::Status requestCpusetBoost(bool enable, const ::android::sp<::android::IBinder>& client, int32_t* _aidl_return) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_SCHEDULING_POLICY_SERVICE_H_
