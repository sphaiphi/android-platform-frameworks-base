#ifndef AIDL_GENERATED_ANDROID_DEBUG_BP_ADB_MANAGER_H_
#define AIDL_GENERATED_ANDROID_DEBUG_BP_ADB_MANAGER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/debug/IAdbManager.h>

namespace android {

namespace debug {

class BpAdbManager : public ::android::BpInterface<IAdbManager> {
public:
  explicit BpAdbManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAdbManager() = default;
  ::android::binder::Status allowDebugging(bool alwaysAllow, const ::android::String16& publicKey) override;
  ::android::binder::Status denyDebugging() override;
  ::android::binder::Status clearDebuggingKeys() override;
};  // class BpAdbManager

}  // namespace debug

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_DEBUG_BP_ADB_MANAGER_H_
