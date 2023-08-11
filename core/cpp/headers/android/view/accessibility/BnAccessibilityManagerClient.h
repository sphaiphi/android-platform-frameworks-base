#ifndef AIDL_GENERATED_ANDROID_VIEW_ACCESSIBILITY_BN_ACCESSIBILITY_MANAGER_CLIENT_H_
#define AIDL_GENERATED_ANDROID_VIEW_ACCESSIBILITY_BN_ACCESSIBILITY_MANAGER_CLIENT_H_

#include <binder/IInterface.h>
#include <android/view/accessibility/IAccessibilityManagerClient.h>

namespace android {

namespace view {

namespace accessibility {

class BnAccessibilityManagerClient : public ::android::BnInterface<IAccessibilityManagerClient> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnAccessibilityManagerClient

}  // namespace accessibility

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_ACCESSIBILITY_BN_ACCESSIBILITY_MANAGER_CLIENT_H_
