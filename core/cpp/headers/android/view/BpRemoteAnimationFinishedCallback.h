#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_REMOTE_ANIMATION_FINISHED_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_REMOTE_ANIMATION_FINISHED_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IRemoteAnimationFinishedCallback.h>

namespace android {

namespace view {

class BpRemoteAnimationFinishedCallback : public ::android::BpInterface<IRemoteAnimationFinishedCallback> {
public:
  explicit BpRemoteAnimationFinishedCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpRemoteAnimationFinishedCallback() = default;
  ::android::binder::Status onAnimationFinished() override;
};  // class BpRemoteAnimationFinishedCallback

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_REMOTE_ANIMATION_FINISHED_CALLBACK_H_
