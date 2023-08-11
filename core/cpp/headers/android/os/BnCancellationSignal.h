#ifndef AIDL_GENERATED_ANDROID_OS_BN_CANCELLATION_SIGNAL_H_
#define AIDL_GENERATED_ANDROID_OS_BN_CANCELLATION_SIGNAL_H_

#include <binder/IInterface.h>
#include <android/os/ICancellationSignal.h>

namespace android {

namespace os {

class BnCancellationSignal : public ::android::BnInterface<ICancellationSignal> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnCancellationSignal

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_CANCELLATION_SIGNAL_H_
