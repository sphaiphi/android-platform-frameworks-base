#ifndef AIDL_GENERATED_ANDROID_OS_BP_PROCESS_INFO_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_BP_PROCESS_INFO_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/IProcessInfoService.h>

namespace android {

namespace os {

class BpProcessInfoService : public ::android::BpInterface<IProcessInfoService> {
public:
  explicit BpProcessInfoService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpProcessInfoService() = default;
  ::android::binder::Status getProcessStatesFromPids(const ::std::vector<int32_t>& pids, ::std::vector<int32_t>* states) override;
  ::android::binder::Status getProcessStatesAndOomScoresFromPids(const ::std::vector<int32_t>& pids, ::std::vector<int32_t>* states, ::std::vector<int32_t>* scores) override;
};  // class BpProcessInfoService

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_PROCESS_INFO_SERVICE_H_
