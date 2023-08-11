#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_BP_PACKAGE_DELETE_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_BP_PACKAGE_DELETE_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/content/pm/IPackageDeleteObserver.h>

namespace android {

namespace content {

namespace pm {

class BpPackageDeleteObserver : public ::android::BpInterface<IPackageDeleteObserver> {
public:
  explicit BpPackageDeleteObserver(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPackageDeleteObserver() = default;
  ::android::binder::Status packageDeleted(const ::android::String16& packageName, int32_t returnCode) override;
};  // class BpPackageDeleteObserver

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_BP_PACKAGE_DELETE_OBSERVER_H_
