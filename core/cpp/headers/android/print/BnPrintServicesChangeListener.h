#ifndef AIDL_GENERATED_ANDROID_PRINT_BN_PRINT_SERVICES_CHANGE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_PRINT_BN_PRINT_SERVICES_CHANGE_LISTENER_H_

#include <binder/IInterface.h>
#include <android/print/IPrintServicesChangeListener.h>

namespace android {

namespace print {

class BnPrintServicesChangeListener : public ::android::BnInterface<IPrintServicesChangeListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnPrintServicesChangeListener

}  // namespace print

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_PRINT_BN_PRINT_SERVICES_CHANGE_LISTENER_H_
