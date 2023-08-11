#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_I_PACKAGE_DELETE_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_I_PACKAGE_DELETE_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace content {

namespace pm {

class IPackageDeleteObserver : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PackageDeleteObserver)
  virtual ::android::binder::Status packageDeleted(const ::android::String16& packageName, int32_t returnCode) = 0;
};  // class IPackageDeleteObserver

class IPackageDeleteObserverDefault : public IPackageDeleteObserver {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status packageDeleted(const ::android::String16& packageName, int32_t returnCode) override;

};

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_I_PACKAGE_DELETE_OBSERVER_H_
