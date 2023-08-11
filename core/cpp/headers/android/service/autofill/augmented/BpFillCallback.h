#ifndef AIDL_GENERATED_ANDROID_SERVICE_AUTOFILL_AUGMENTED_BP_FILL_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_AUTOFILL_AUGMENTED_BP_FILL_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/autofill/augmented/IFillCallback.h>

namespace android {

namespace service {

namespace autofill {

namespace augmented {

class BpFillCallback : public ::android::BpInterface<IFillCallback> {
public:
  explicit BpFillCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpFillCallback() = default;
  ::android::binder::Status onCancellable(const ::android::sp<::android::os::ICancellationSignal>& cancellation) override;
  ::android::binder::Status onSuccess() override;
  ::android::binder::Status isCompleted(bool* _aidl_return) override;
  ::android::binder::Status cancel() override;
};  // class BpFillCallback

}  // namespace augmented

}  // namespace autofill

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_AUTOFILL_AUGMENTED_BP_FILL_CALLBACK_H_
