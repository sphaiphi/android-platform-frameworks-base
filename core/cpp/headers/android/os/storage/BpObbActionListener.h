#ifndef AIDL_GENERATED_ANDROID_OS_STORAGE_BP_OBB_ACTION_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_STORAGE_BP_OBB_ACTION_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/storage/IObbActionListener.h>

namespace android {

namespace os {

namespace storage {

class BpObbActionListener : public ::android::BpInterface<IObbActionListener> {
public:
  explicit BpObbActionListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpObbActionListener() = default;
  ::android::binder::Status onObbResult(const ::android::String16& filename, int32_t nonce, int32_t status) override;
};  // class BpObbActionListener

}  // namespace storage

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_STORAGE_BP_OBB_ACTION_LISTENER_H_
