#ifndef AIDL_GENERATED_ANDROID_OS_I_PERMISSION_CONTROLLER_H_
#define AIDL_GENERATED_ANDROID_OS_I_PERMISSION_CONTROLLER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace os {

class IPermissionController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PermissionController)
  virtual ::android::binder::Status checkPermission(const ::android::String16& permission, int32_t pid, int32_t uid, bool* _aidl_return) = 0;
  virtual ::android::binder::Status noteOp(const ::android::String16& op, int32_t uid, const ::android::String16& packageName, int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status getPackagesForUid(int32_t uid, ::std::vector<::android::String16>* _aidl_return) = 0;
  virtual ::android::binder::Status isRuntimePermission(const ::android::String16& permission, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getPackageUid(const ::android::String16& packageName, int32_t flags, int32_t* _aidl_return) = 0;
};  // class IPermissionController

class IPermissionControllerDefault : public IPermissionController {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status checkPermission(const ::android::String16& permission, int32_t pid, int32_t uid, bool* _aidl_return) override;
  ::android::binder::Status noteOp(const ::android::String16& op, int32_t uid, const ::android::String16& packageName, int32_t* _aidl_return) override;
  ::android::binder::Status getPackagesForUid(int32_t uid, ::std::vector<::android::String16>* _aidl_return) override;
  ::android::binder::Status isRuntimePermission(const ::android::String16& permission, bool* _aidl_return) override;
  ::android::binder::Status getPackageUid(const ::android::String16& packageName, int32_t flags, int32_t* _aidl_return) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_PERMISSION_CONTROLLER_H_
