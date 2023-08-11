#ifndef AIDL_GENERATED_ANDROID_OS_STORAGE_BP_STORAGE_SHUTDOWN_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_OS_STORAGE_BP_STORAGE_SHUTDOWN_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/storage/IStorageShutdownObserver.h>

namespace android {

namespace os {

namespace storage {

class BpStorageShutdownObserver : public ::android::BpInterface<IStorageShutdownObserver> {
public:
  explicit BpStorageShutdownObserver(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpStorageShutdownObserver() = default;
  ::android::binder::Status onShutDownComplete(int32_t statusCode) override;
};  // class BpStorageShutdownObserver

}  // namespace storage

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_STORAGE_BP_STORAGE_SHUTDOWN_OBSERVER_H_
