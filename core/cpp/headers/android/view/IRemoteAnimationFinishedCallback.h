#ifndef AIDL_GENERATED_ANDROID_VIEW_I_REMOTE_ANIMATION_FINISHED_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_REMOTE_ANIMATION_FINISHED_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IRemoteAnimationFinishedCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RemoteAnimationFinishedCallback)
  virtual ::android::binder::Status onAnimationFinished() = 0;
};  // class IRemoteAnimationFinishedCallback

class IRemoteAnimationFinishedCallbackDefault : public IRemoteAnimationFinishedCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onAnimationFinished() override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_REMOTE_ANIMATION_FINISHED_CALLBACK_H_
