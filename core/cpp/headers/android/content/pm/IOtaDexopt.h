#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_I_OTA_DEXOPT_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_I_OTA_DEXOPT_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace content {

namespace pm {

class IOtaDexopt : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(OtaDexopt)
  virtual ::android::binder::Status prepare() = 0;
  virtual ::android::binder::Status cleanup() = 0;
  virtual ::android::binder::Status isDone(bool* _aidl_return) = 0;
  virtual ::android::binder::Status getProgress(float* _aidl_return) = 0;
  virtual ::android::binder::Status dexoptNextPackage() = 0;
  virtual ::android::binder::Status nextDexoptCommand(::android::String16* _aidl_return) = 0;
};  // class IOtaDexopt

class IOtaDexoptDefault : public IOtaDexopt {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status prepare() override;
  ::android::binder::Status cleanup() override;
  ::android::binder::Status isDone(bool* _aidl_return) override;
  ::android::binder::Status getProgress(float* _aidl_return) override;
  ::android::binder::Status dexoptNextPackage() override;
  ::android::binder::Status nextDexoptCommand(::android::String16* _aidl_return) override;

};

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_I_OTA_DEXOPT_H_
