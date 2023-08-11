#ifndef AIDL_GENERATED_ANDROID_OS_I_CANCELLATION_SIGNAL_H_
#define AIDL_GENERATED_ANDROID_OS_I_CANCELLATION_SIGNAL_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

class ICancellationSignal : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CancellationSignal)
  virtual ::android::binder::Status cancel() = 0;
};  // class ICancellationSignal

class ICancellationSignalDefault : public ICancellationSignal {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status cancel() override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_CANCELLATION_SIGNAL_H_
