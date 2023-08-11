#ifndef AIDL_GENERATED_ANDROID_DEBUG_BP_ADB_TRANSPORT_H_
#define AIDL_GENERATED_ANDROID_DEBUG_BP_ADB_TRANSPORT_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/debug/IAdbTransport.h>

namespace android {

namespace debug {

class BpAdbTransport : public ::android::BpInterface<IAdbTransport> {
public:
  explicit BpAdbTransport(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAdbTransport() = default;
  ::android::binder::Status onAdbEnabled(bool enabled) override;
};  // class BpAdbTransport

}  // namespace debug

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_DEBUG_BP_ADB_TRANSPORT_H_
