#ifndef AIDL_GENERATED_ANDROID_PRINT_BP_PRINT_SERVICES_CHANGE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_PRINT_BP_PRINT_SERVICES_CHANGE_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/print/IPrintServicesChangeListener.h>

namespace android {

namespace print {

class BpPrintServicesChangeListener : public ::android::BpInterface<IPrintServicesChangeListener> {
public:
  explicit BpPrintServicesChangeListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPrintServicesChangeListener() = default;
  ::android::binder::Status onPrintServicesChanged() override;
};  // class BpPrintServicesChangeListener

}  // namespace print

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_PRINT_BP_PRINT_SERVICES_CHANGE_LISTENER_H_
