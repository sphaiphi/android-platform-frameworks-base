#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_BN_PACKAGE_INSTALLER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_BN_PACKAGE_INSTALLER_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/content/pm/IPackageInstallerCallback.h>

namespace android {

namespace content {

namespace pm {

class BnPackageInstallerCallback : public ::android::BnInterface<IPackageInstallerCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnPackageInstallerCallback

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_BN_PACKAGE_INSTALLER_CALLBACK_H_
