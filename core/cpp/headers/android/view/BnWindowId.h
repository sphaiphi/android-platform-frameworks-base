#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_WINDOW_ID_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_WINDOW_ID_H_

#include <binder/IInterface.h>
#include <android/view/IWindowId.h>

namespace android {

namespace view {

class BnWindowId : public ::android::BnInterface<IWindowId> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnWindowId

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_WINDOW_ID_H_
