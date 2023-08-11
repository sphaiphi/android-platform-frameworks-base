#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_BP_PACKAGE_DATA_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_BP_PACKAGE_DATA_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/content/pm/IPackageDataObserver.h>

namespace android {

namespace content {

namespace pm {

class BpPackageDataObserver : public ::android::BpInterface<IPackageDataObserver> {
public:
  explicit BpPackageDataObserver(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPackageDataObserver() = default;
  ::android::binder::Status onRemoveCompleted(const ::android::String16& packageName, bool succeeded) override;
};  // class BpPackageDataObserver

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_BP_PACKAGE_DATA_OBSERVER_H_
