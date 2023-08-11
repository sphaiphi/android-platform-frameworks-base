#ifndef AIDL_GENERATED_ANDROID_CONTENT_I_ON_PRIMARY_CLIP_CHANGED_LISTENER_H_
#define AIDL_GENERATED_ANDROID_CONTENT_I_ON_PRIMARY_CLIP_CHANGED_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace content {

class IOnPrimaryClipChangedListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(OnPrimaryClipChangedListener)
  virtual ::android::binder::Status dispatchPrimaryClipChanged() = 0;
};  // class IOnPrimaryClipChangedListener

class IOnPrimaryClipChangedListenerDefault : public IOnPrimaryClipChangedListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status dispatchPrimaryClipChanged() override;

};

}  // namespace content

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_CONTENT_I_ON_PRIMARY_CLIP_CHANGED_LISTENER_H_
