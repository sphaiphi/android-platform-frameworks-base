#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_WINDOW_SESSION_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_WINDOW_SESSION_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/view/IWindowSessionCallback.h>

namespace android {

namespace view {

class BnWindowSessionCallback : public ::android::BnInterface<IWindowSessionCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnWindowSessionCallback

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_WINDOW_SESSION_CALLBACK_H_
