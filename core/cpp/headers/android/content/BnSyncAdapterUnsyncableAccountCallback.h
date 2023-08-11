#ifndef AIDL_GENERATED_ANDROID_CONTENT_BN_SYNC_ADAPTER_UNSYNCABLE_ACCOUNT_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_CONTENT_BN_SYNC_ADAPTER_UNSYNCABLE_ACCOUNT_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/content/ISyncAdapterUnsyncableAccountCallback.h>

namespace android {

namespace content {

class BnSyncAdapterUnsyncableAccountCallback : public ::android::BnInterface<ISyncAdapterUnsyncableAccountCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnSyncAdapterUnsyncableAccountCallback

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_BN_SYNC_ADAPTER_UNSYNCABLE_ACCOUNT_CALLBACK_H_
