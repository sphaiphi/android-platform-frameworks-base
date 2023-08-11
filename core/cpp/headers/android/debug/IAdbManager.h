#ifndef AIDL_GENERATED_ANDROID_DEBUG_I_ADB_MANAGER_H_
#define AIDL_GENERATED_ANDROID_DEBUG_I_ADB_MANAGER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace debug {

class IAdbManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AdbManager)
  virtual ::android::binder::Status allowDebugging(bool alwaysAllow, const ::android::String16& publicKey) = 0;
  virtual ::android::binder::Status denyDebugging() = 0;
  virtual ::android::binder::Status clearDebuggingKeys() = 0;
};  // class IAdbManager

class IAdbManagerDefault : public IAdbManager {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status allowDebugging(bool alwaysAllow, const ::android::String16& publicKey) override;
  ::android::binder::Status denyDebugging() override;
  ::android::binder::Status clearDebuggingKeys() override;

};

}  // namespace debug

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_DEBUG_I_ADB_MANAGER_H_
