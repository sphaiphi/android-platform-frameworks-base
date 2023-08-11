#ifndef AIDL_GENERATED_ANDROID_OS_BP_RECOVERY_SYSTEM_PROGRESS_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_BP_RECOVERY_SYSTEM_PROGRESS_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/IRecoverySystemProgressListener.h>

namespace android {

namespace os {

class BpRecoverySystemProgressListener : public ::android::BpInterface<IRecoverySystemProgressListener> {
public:
  explicit BpRecoverySystemProgressListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpRecoverySystemProgressListener() = default;
  ::android::binder::Status onProgress(int32_t progress) override;
};  // class BpRecoverySystemProgressListener

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_RECOVERY_SYSTEM_PROGRESS_LISTENER_H_
