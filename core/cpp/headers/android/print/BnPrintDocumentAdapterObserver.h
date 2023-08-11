#ifndef AIDL_GENERATED_ANDROID_PRINT_BN_PRINT_DOCUMENT_ADAPTER_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_PRINT_BN_PRINT_DOCUMENT_ADAPTER_OBSERVER_H_

#include <binder/IInterface.h>
#include <android/print/IPrintDocumentAdapterObserver.h>

namespace android {

namespace print {

class BnPrintDocumentAdapterObserver : public ::android::BnInterface<IPrintDocumentAdapterObserver> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnPrintDocumentAdapterObserver

}  // namespace print

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_PRINT_BN_PRINT_DOCUMENT_ADAPTER_OBSERVER_H_
