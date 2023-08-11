#ifndef AIDL_GENERATED_ANDROID_CONTENT_BP_SYNC_ADAPTER_UNSYNCABLE_ACCOUNT_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_CONTENT_BP_SYNC_ADAPTER_UNSYNCABLE_ACCOUNT_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/content/ISyncAdapterUnsyncableAccountCallback.h>

namespace android {

namespace content {

class BpSyncAdapterUnsyncableAccountCallback : public ::android::BpInterface<ISyncAdapterUnsyncableAccountCallback> {
public:
  explicit BpSyncAdapterUnsyncableAccountCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpSyncAdapterUnsyncableAccountCallback() = default;
  ::android::binder::Status onUnsyncableAccountDone(bool isReady) override;
};  // class BpSyncAdapterUnsyncableAccountCallback

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_BP_SYNC_ADAPTER_UNSYNCABLE_ACCOUNT_CALLBACK_H_
