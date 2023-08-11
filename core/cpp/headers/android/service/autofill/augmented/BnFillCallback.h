#ifndef AIDL_GENERATED_ANDROID_SERVICE_AUTOFILL_AUGMENTED_BN_FILL_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_AUTOFILL_AUGMENTED_BN_FILL_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/service/autofill/augmented/IFillCallback.h>

namespace android {

namespace service {

namespace autofill {

namespace augmented {

class BnFillCallback : public ::android::BnInterface<IFillCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnFillCallback

}  // namespace augmented

}  // namespace autofill

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_AUTOFILL_AUGMENTED_BN_FILL_CALLBACK_H_
