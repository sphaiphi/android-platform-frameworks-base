#ifndef AIDL_GENERATED_ANDROID_DEBUG_I_ADB_TRANSPORT_H_
#define AIDL_GENERATED_ANDROID_DEBUG_I_ADB_TRANSPORT_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace debug {

class IAdbTransport : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AdbTransport)
  virtual ::android::binder::Status onAdbEnabled(bool enabled) = 0;
};  // class IAdbTransport

class IAdbTransportDefault : public IAdbTransport {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onAdbEnabled(bool enabled) override;

};

}  // namespace debug

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_DEBUG_I_ADB_TRANSPORT_H_
