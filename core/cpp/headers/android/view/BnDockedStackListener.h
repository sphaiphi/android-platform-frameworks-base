#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_DOCKED_STACK_LISTENER_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_DOCKED_STACK_LISTENER_H_

#include <binder/IInterface.h>
#include <android/view/IDockedStackListener.h>

namespace android {

namespace view {

class BnDockedStackListener : public ::android::BnInterface<IDockedStackListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnDockedStackListener

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_DOCKED_STACK_LISTENER_H_
