#ifndef AIDL_GENERATED_ANDROID_CONTENT_I_SYNC_STATUS_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_I_SYNC_STATUS_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace content {

class ISyncStatusObserver : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(SyncStatusObserver)
  virtual ::android::binder::Status onStatusChanged(int32_t which) = 0;
};  // class ISyncStatusObserver

class ISyncStatusObserverDefault : public ISyncStatusObserver {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onStatusChanged(int32_t which) override;

};

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_I_SYNC_STATUS_OBSERVER_H_
