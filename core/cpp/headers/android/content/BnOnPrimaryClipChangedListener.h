#ifndef AIDL_GENERATED_ANDROID_CONTENT_BN_ON_PRIMARY_CLIP_CHANGED_LISTENER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_BN_ON_PRIMARY_CLIP_CHANGED_LISTENER_H_

#include <binder/IInterface.h>
#include <android/content/IOnPrimaryClipChangedListener.h>

namespace android {

namespace content {

class BnOnPrimaryClipChangedListener : public ::android::BnInterface<IOnPrimaryClipChangedListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnOnPrimaryClipChangedListener

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_BN_ON_PRIMARY_CLIP_CHANGED_LISTENER_H_
