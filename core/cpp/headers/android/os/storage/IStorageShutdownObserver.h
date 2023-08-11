#ifndef AIDL_GENERATED_ANDROID_OS_STORAGE_I_STORAGE_SHUTDOWN_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_OS_STORAGE_I_STORAGE_SHUTDOWN_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

namespace storage {

class IStorageShutdownObserver : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(StorageShutdownObserver)
  virtual ::android::binder::Status onShutDownComplete(int32_t statusCode) = 0;
};  // class IStorageShutdownObserver

class IStorageShutdownObserverDefault : public IStorageShutdownObserver {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onShutDownComplete(int32_t statusCode) override;

};

}  // namespace storage

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_STORAGE_I_STORAGE_SHUTDOWN_OBSERVER_H_
