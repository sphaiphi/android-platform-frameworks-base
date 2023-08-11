#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_DISPLAY_FOLD_LISTENER_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_DISPLAY_FOLD_LISTENER_H_

#include <binder/IInterface.h>
#include <android/view/IDisplayFoldListener.h>

namespace android {

namespace view {

class BnDisplayFoldListener : public ::android::BnInterface<IDisplayFoldListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnDisplayFoldListener

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_DISPLAY_FOLD_LISTENER_H_
