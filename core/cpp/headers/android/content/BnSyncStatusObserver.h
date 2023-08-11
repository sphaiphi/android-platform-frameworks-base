#ifndef AIDL_GENERATED_ANDROID_CONTENT_BN_SYNC_STATUS_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_BN_SYNC_STATUS_OBSERVER_H_

#include <binder/IInterface.h>
#include <android/content/ISyncStatusObserver.h>

namespace android {

namespace content {

class BnSyncStatusObserver : public ::android::BnInterface<ISyncStatusObserver> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnSyncStatusObserver

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_BN_SYNC_STATUS_OBSERVER_H_
