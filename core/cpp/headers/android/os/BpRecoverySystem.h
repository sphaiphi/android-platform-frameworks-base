#ifndef AIDL_GENERATED_ANDROID_OS_BP_RECOVERY_SYSTEM_H_
#define AIDL_GENERATED_ANDROID_OS_BP_RECOVERY_SYSTEM_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/IRecoverySystem.h>

namespace android {

namespace os {

class BpRecoverySystem : public ::android::BpInterface<IRecoverySystem> {
public:
  explicit BpRecoverySystem(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpRecoverySystem() = default;
  ::android::binder::Status uncrypt(const ::android::String16& packageFile, const ::android::sp<::android::os::IRecoverySystemProgressListener>& listener, bool* _aidl_return) override;
  ::android::binder::Status setupBcb(const ::android::String16& command, bool* _aidl_return) override;
  ::android::binder::Status clearBcb(bool* _aidl_return) override;
  ::android::binder::Status rebootRecoveryWithCommand(const ::android::String16& command) override;
};  // class BpRecoverySystem

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_RECOVERY_SYSTEM_H_
