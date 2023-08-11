#ifndef AIDL_GENERATED_ANDROID_OS_I_PROCESS_INFO_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_I_PROCESS_INFO_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace os {

class IProcessInfoService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(ProcessInfoService)
  virtual ::android::binder::Status getProcessStatesFromPids(const ::std::vector<int32_t>& pids, ::std::vector<int32_t>* states) = 0;
  virtual ::android::binder::Status getProcessStatesAndOomScoresFromPids(const ::std::vector<int32_t>& pids, ::std::vector<int32_t>* states, ::std::vector<int32_t>* scores) = 0;
};  // class IProcessInfoService

class IProcessInfoServiceDefault : public IProcessInfoService {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status getProcessStatesFromPids(const ::std::vector<int32_t>& pids, ::std::vector<int32_t>* states) override;
  ::android::binder::Status getProcessStatesAndOomScoresFromPids(const ::std::vector<int32_t>& pids, ::std::vector<int32_t>* states, ::std::vector<int32_t>* scores) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_PROCESS_INFO_SERVICE_H_
