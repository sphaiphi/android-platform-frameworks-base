#ifndef AIDL_GENERATED_ANDROID_CONTENT_BP_SYNC_STATUS_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_BP_SYNC_STATUS_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/content/ISyncStatusObserver.h>

namespace android {

namespace content {

class BpSyncStatusObserver : public ::android::BpInterface<ISyncStatusObserver> {
public:
  explicit BpSyncStatusObserver(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpSyncStatusObserver() = default;
  ::android::binder::Status onStatusChanged(int32_t which) override;
};  // class BpSyncStatusObserver

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_BP_SYNC_STATUS_OBSERVER_H_
