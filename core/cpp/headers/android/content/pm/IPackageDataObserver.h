#ifndef AIDL_GENERATED_ANDROID_CONTENT_PM_I_PACKAGE_DATA_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_PM_I_PACKAGE_DATA_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace content {

namespace pm {

class IPackageDataObserver : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PackageDataObserver)
  virtual ::android::binder::Status onRemoveCompleted(const ::android::String16& packageName, bool succeeded) = 0;
};  // class IPackageDataObserver

class IPackageDataObserverDefault : public IPackageDataObserver {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onRemoveCompleted(const ::android::String16& packageName, bool succeeded) override;

};

}  // namespace pm

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_PM_I_PACKAGE_DATA_OBSERVER_H_
