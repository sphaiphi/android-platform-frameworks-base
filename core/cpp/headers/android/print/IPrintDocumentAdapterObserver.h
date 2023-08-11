#ifndef AIDL_GENERATED_ANDROID_PRINT_I_PRINT_DOCUMENT_ADAPTER_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_PRINT_I_PRINT_DOCUMENT_ADAPTER_OBSERVER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace print {

class IPrintDocumentAdapterObserver : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PrintDocumentAdapterObserver)
  virtual ::android::binder::Status onDestroy() = 0;
};  // class IPrintDocumentAdapterObserver

class IPrintDocumentAdapterObserverDefault : public IPrintDocumentAdapterObserver {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onDestroy() override;

};

}  // namespace print

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_PRINT_I_PRINT_DOCUMENT_ADAPTER_OBSERVER_H_
