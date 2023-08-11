#ifndef AIDL_GENERATED_ANDROID_PRINT_I_PRINT_SERVICES_CHANGE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_PRINT_I_PRINT_SERVICES_CHANGE_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace print {

class IPrintServicesChangeListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PrintServicesChangeListener)
  virtual ::android::binder::Status onPrintServicesChanged() = 0;
};  // class IPrintServicesChangeListener

class IPrintServicesChangeListenerDefault : public IPrintServicesChangeListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onPrintServicesChanged() override;

};

}  // namespace print

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_PRINT_I_PRINT_SERVICES_CHANGE_LISTENER_H_
