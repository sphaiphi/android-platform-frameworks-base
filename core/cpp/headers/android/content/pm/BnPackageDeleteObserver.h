#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_BN_PACKAGE_DELETE_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_BN_PACKAGE_DELETE_OBSERVER_H_

#include <binder/IInterface.h>
#include <android/content/pm/IPackageDeleteObserver.h>

namespace android {

namespace content {

namespace pm {

class BnPackageDeleteObserver : public ::android::BnInterface<IPackageDeleteObserver> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnPackageDeleteObserver

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_BN_PACKAGE_DELETE_OBSERVER_H_
