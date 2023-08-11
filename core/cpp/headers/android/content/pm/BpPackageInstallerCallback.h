#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_BP_PACKAGE_INSTALLER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_BP_PACKAGE_INSTALLER_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/content/pm/IPackageInstallerCallback.h>

namespace android {

namespace content {

namespace pm {

class BpPackageInstallerCallback : public ::android::BpInterface<IPackageInstallerCallback> {
public:
  explicit BpPackageInstallerCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPackageInstallerCallback() = default;
  ::android::binder::Status onSessionCreated(int32_t sessionId) override;
  ::android::binder::Status onSessionBadgingChanged(int32_t sessionId) override;
  ::android::binder::Status onSessionActiveChanged(int32_t sessionId, bool active) override;
  ::android::binder::Status onSessionProgressChanged(int32_t sessionId, float progress) override;
  ::android::binder::Status onSessionFinished(int32_t sessionId, bool success) override;
};  // class BpPackageInstallerCallback

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_BP_PACKAGE_INSTALLER_CALLBACK_H_
