#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_WINDOW_FOCUS_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_WINDOW_FOCUS_OBSERVER_H_

#include <binder/IInterface.h>
#include <android/view/IWindowFocusObserver.h>

namespace android {

namespace view {

class BnWindowFocusObserver : public ::android::BnInterface<IWindowFocusObserver> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnWindowFocusObserver

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_WINDOW_FOCUS_OBSERVER_H_
