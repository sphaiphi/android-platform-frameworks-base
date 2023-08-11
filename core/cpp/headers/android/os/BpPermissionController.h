#ifndef AIDL_GENERATED_ANDROID_OS_BP_PERMISSION_CONTROLLER_H_
#define AIDL_GENERATED_ANDROID_OS_BP_PERMISSION_CONTROLLER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/IPermissionController.h>

namespace android {

namespace os {

class BpPermissionController : public ::android::BpInterface<IPermissionController> {
public:
  explicit BpPermissionController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPermissionController() = default;
  ::android::binder::Status checkPermission(const ::android::String16& permission, int32_t pid, int32_t uid, bool* _aidl_return) override;
  ::android::binder::Status noteOp(const ::android::String16& op, int32_t uid, const ::android::String16& packageName, int32_t* _aidl_return) override;
  ::android::binder::Status getPackagesForUid(int32_t uid, ::std::vector<::android::String16>* _aidl_return) override;
  ::android::binder::Status isRuntimePermission(const ::android::String16& permission, bool* _aidl_return) override;
  ::android::binder::Status getPackageUid(const ::android::String16& packageName, int32_t flags, int32_t* _aidl_return) override;
};  // class BpPermissionController

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_PERMISSION_CONTROLLER_H_
