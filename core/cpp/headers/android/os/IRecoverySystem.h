#ifndef AIDL_GENERATED_ANDROID_OS_I_RECOVERY_SYSTEM_H_
#define AIDL_GENERATED_ANDROID_OS_I_RECOVERY_SYSTEM_H_

#include <android/os/IRecoverySystemProgressListener.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

class IRecoverySystem : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RecoverySystem)
  virtual ::android::binder::Status uncrypt(const ::android::String16& packageFile, const ::android::sp<::android::os::IRecoverySystemProgressListener>& listener, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setupBcb(const ::android::String16& command, bool* _aidl_return) = 0;
  virtual ::android::binder::Status clearBcb(bool* _aidl_return) = 0;
  virtual ::android::binder::Status rebootRecoveryWithCommand(const ::android::String16& command) = 0;
};  // class IRecoverySystem

class IRecoverySystemDefault : public IRecoverySystem {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status uncrypt(const ::android::String16& packageFile, const ::android::sp<::android::os::IRecoverySystemProgressListener>& listener, bool* _aidl_return) override;
  ::android::binder::Status setupBcb(const ::android::String16& command, bool* _aidl_return) override;
  ::android::binder::Status clearBcb(bool* _aidl_return) override;
  ::android::binder::Status rebootRecoveryWithCommand(const ::android::String16& command) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_RECOVERY_SYSTEM_H_
