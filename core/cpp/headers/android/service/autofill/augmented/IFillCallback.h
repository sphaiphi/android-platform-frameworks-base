#ifndef AIDL_GENERATED_ANDROID_SERVICE_AUTOFILL_AUGMENTED_I_FILL_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_AUTOFILL_AUGMENTED_I_FILL_CALLBACK_H_

#include <android/os/ICancellationSignal.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace service {

namespace autofill {

namespace augmented {

class IFillCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FillCallback)
  virtual ::android::binder::Status onCancellable(const ::android::sp<::android::os::ICancellationSignal>& cancellation) = 0;
  virtual ::android::binder::Status onSuccess() = 0;
  virtual ::android::binder::Status isCompleted(bool* _aidl_return) = 0;
  virtual ::android::binder::Status cancel() = 0;
};  // class IFillCallback

class IFillCallbackDefault : public IFillCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onCancellable(const ::android::sp<::android::os::ICancellationSignal>& cancellation) override;
  ::android::binder::Status onSuccess() override;
  ::android::binder::Status isCompleted(bool* _aidl_return) override;
  ::android::binder::Status cancel() override;

};

}  // namespace augmented

}  // namespace autofill

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_AUTOFILL_AUGMENTED_I_FILL_CALLBACK_H_
