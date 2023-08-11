#ifndef AIDL_GENERATED_ANDROID_VIEW_ACCESSIBILITY_I_ACCESSIBILITY_MANAGER_CLIENT_H_
#define AIDL_GENERATED_ANDROID_VIEW_ACCESSIBILITY_I_ACCESSIBILITY_MANAGER_CLIENT_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

namespace accessibility {

class IAccessibilityManagerClient : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AccessibilityManagerClient)
  virtual ::android::binder::Status setState(int32_t stateFlags) = 0;
  virtual ::android::binder::Status notifyServicesStateChanged(int64_t updatedUiTimeout) = 0;
  virtual ::android::binder::Status setRelevantEventTypes(int32_t eventTypes) = 0;
};  // class IAccessibilityManagerClient

class IAccessibilityManagerClientDefault : public IAccessibilityManagerClient {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status setState(int32_t stateFlags) override;
  ::android::binder::Status notifyServicesStateChanged(int64_t updatedUiTimeout) override;
  ::android::binder::Status setRelevantEventTypes(int32_t eventTypes) override;

};

}  // namespace accessibility

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_ACCESSIBILITY_I_ACCESSIBILITY_MANAGER_CLIENT_H_
