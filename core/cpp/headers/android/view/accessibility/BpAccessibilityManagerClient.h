#ifndef AIDL_GENERATED_ANDROID_VIEW_ACCESSIBILITY_BP_ACCESSIBILITY_MANAGER_CLIENT_H_
#define AIDL_GENERATED_ANDROID_VIEW_ACCESSIBILITY_BP_ACCESSIBILITY_MANAGER_CLIENT_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/accessibility/IAccessibilityManagerClient.h>

namespace android {

namespace view {

namespace accessibility {

class BpAccessibilityManagerClient : public ::android::BpInterface<IAccessibilityManagerClient> {
public:
  explicit BpAccessibilityManagerClient(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAccessibilityManagerClient() = default;
  ::android::binder::Status setState(int32_t stateFlags) override;
  ::android::binder::Status notifyServicesStateChanged(int64_t updatedUiTimeout) override;
  ::android::binder::Status setRelevantEventTypes(int32_t eventTypes) override;
};  // class BpAccessibilityManagerClient

}  // namespace accessibility

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_ACCESSIBILITY_BP_ACCESSIBILITY_MANAGER_CLIENT_H_
