#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_GET_OTA_STATUS_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_GET_OTA_STATUS_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/euicc/IGetOtaStatusCallback.h>

namespace android {

namespace service {

namespace euicc {

class BpGetOtaStatusCallback : public ::android::BpInterface<IGetOtaStatusCallback> {
public:
  explicit BpGetOtaStatusCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpGetOtaStatusCallback() = default;
  ::android::binder::Status onSuccess(int32_t status) override;
};  // class BpGetOtaStatusCallback

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_GET_OTA_STATUS_CALLBACK_H_
