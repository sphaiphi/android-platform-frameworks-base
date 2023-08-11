#ifndef AIDL_GENERATED_ANDROID_NET_BP_CAPTIVE_PORTAL_H_
#define AIDL_GENERATED_ANDROID_NET_BP_CAPTIVE_PORTAL_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/net/ICaptivePortal.h>

namespace android {

namespace net {

class BpCaptivePortal : public ::android::BpInterface<ICaptivePortal> {
public:
  explicit BpCaptivePortal(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCaptivePortal() = default;
  ::android::binder::Status appResponse(int32_t response) override;
  ::android::binder::Status logEvent(int32_t eventId, const ::android::String16& packageName) override;
};  // class BpCaptivePortal

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_BP_CAPTIVE_PORTAL_H_
