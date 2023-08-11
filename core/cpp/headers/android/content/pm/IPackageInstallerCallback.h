#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_I_PACKAGE_INSTALLER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_I_PACKAGE_INSTALLER_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace content {

namespace pm {

class IPackageInstallerCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PackageInstallerCallback)
  virtual ::android::binder::Status onSessionCreated(int32_t sessionId) = 0;
  virtual ::android::binder::Status onSessionBadgingChanged(int32_t sessionId) = 0;
  virtual ::android::binder::Status onSessionActiveChanged(int32_t sessionId, bool active) = 0;
  virtual ::android::binder::Status onSessionProgressChanged(int32_t sessionId, float progress) = 0;
  virtual ::android::binder::Status onSessionFinished(int32_t sessionId, bool success) = 0;
};  // class IPackageInstallerCallback

class IPackageInstallerCallbackDefault : public IPackageInstallerCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onSessionCreated(int32_t sessionId) override;
  ::android::binder::Status onSessionBadgingChanged(int32_t sessionId) override;
  ::android::binder::Status onSessionActiveChanged(int32_t sessionId, bool active) override;
  ::android::binder::Status onSessionProgressChanged(int32_t sessionId, float progress) override;
  ::android::binder::Status onSessionFinished(int32_t sessionId, bool success) override;

};

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_I_PACKAGE_INSTALLER_CALLBACK_H_
