#ifndef AIDL_GENERATED_ANDROID_PRINT_BP_PRINT_DOCUMENT_ADAPTER_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_PRINT_BP_PRINT_DOCUMENT_ADAPTER_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/print/IPrintDocumentAdapterObserver.h>

namespace android {

namespace print {

class BpPrintDocumentAdapterObserver : public ::android::BpInterface<IPrintDocumentAdapterObserver> {
public:
  explicit BpPrintDocumentAdapterObserver(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPrintDocumentAdapterObserver() = default;
  ::android::binder::Status onDestroy() override;
};  // class BpPrintDocumentAdapterObserver

}  // namespace print

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_PRINT_BP_PRINT_DOCUMENT_ADAPTER_OBSERVER_H_
