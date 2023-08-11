#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_REMOTE_ANIMATION_FINISHED_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_REMOTE_ANIMATION_FINISHED_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/view/IRemoteAnimationFinishedCallback.h>

namespace android {

namespace view {

class BnRemoteAnimationFinishedCallback : public ::android::BnInterface<IRemoteAnimationFinishedCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnRemoteAnimationFinishedCallback

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_REMOTE_ANIMATION_FINISHED_CALLBACK_H_
