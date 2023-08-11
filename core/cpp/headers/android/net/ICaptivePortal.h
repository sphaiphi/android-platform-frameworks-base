#ifndef AIDL_GENERATED_ANDROID_NET_I_CAPTIVE_PORTAL_H_
#define AIDL_GENERATED_ANDROID_NET_I_CAPTIVE_PORTAL_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace net {

class ICaptivePortal : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CaptivePortal)
  virtual ::android::binder::Status appResponse(int32_t response) = 0;
  virtual ::android::binder::Status logEvent(int32_t eventId, const ::android::String16& packageName) = 0;
};  // class ICaptivePortal

class ICaptivePortalDefault : public ICaptivePortal {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status appResponse(int32_t response) override;
  ::android::binder::Status logEvent(int32_t eventId, const ::android::String16& packageName) override;

};

}  // namespace net

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NET_I_CAPTIVE_PORTAL_H_
