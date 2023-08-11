#ifndef AIDL_GENERATED_ANDROID_OS_I_RECOVERY_SYSTEM_PROGRESS_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_I_RECOVERY_SYSTEM_PROGRESS_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

class IRecoverySystemProgressListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RecoverySystemProgressListener)
  virtual ::android::binder::Status onProgress(int32_t progress) = 0;
};  // class IRecoverySystemProgressListener

class IRecoverySystemProgressListenerDefault : public IRecoverySystemProgressListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onProgress(int32_t progress) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_RECOVERY_SYSTEM_PROGRESS_LISTENER_H_
