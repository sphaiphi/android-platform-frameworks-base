#ifndef AIDL_GENERATED_ANDROID_CONTENT_I_SYNC_ADAPTER_UNSYNCABLE_ACCOUNT_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_CONTENT_I_SYNC_ADAPTER_UNSYNCABLE_ACCOUNT_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace content {

class ISyncAdapterUnsyncableAccountCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(SyncAdapterUnsyncableAccountCallback)
  virtual ::android::binder::Status onUnsyncableAccountDone(bool isReady) = 0;
};  // class ISyncAdapterUnsyncableAccountCallback

class ISyncAdapterUnsyncableAccountCallbackDefault : public ISyncAdapterUnsyncableAccountCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onUnsyncableAccountDone(bool isReady) override;

};

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_I_SYNC_ADAPTER_UNSYNCABLE_ACCOUNT_CALLBACK_H_
