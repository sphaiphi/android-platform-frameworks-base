#ifndef AIDL_GENERATED_ANDROID_CONTENT_BP_ON_PRIMARY_CLIP_CHANGED_LISTENER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_BP_ON_PRIMARY_CLIP_CHANGED_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/content/IOnPrimaryClipChangedListener.h>

namespace android {

namespace content {

class BpOnPrimaryClipChangedListener : public ::android::BpInterface<IOnPrimaryClipChangedListener> {
public:
  explicit BpOnPrimaryClipChangedListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpOnPrimaryClipChangedListener() = default;
  ::android::binder::Status dispatchPrimaryClipChanged() override;
};  // class BpOnPrimaryClipChangedListener

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_BP_ON_PRIMARY_CLIP_CHANGED_LISTENER_H_
