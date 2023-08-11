#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_OTA_STATUS_CHANGED_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_OTA_STATUS_CHANGED_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/euicc/IOtaStatusChangedCallback.h>

namespace android {

namespace service {

namespace euicc {

class BpOtaStatusChangedCallback : public ::android::BpInterface<IOtaStatusChangedCallback> {
public:
  explicit BpOtaStatusChangedCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpOtaStatusChangedCallback() = default;
  ::android::binder::Status onOtaStatusChanged(int32_t status) override;
};  // class BpOtaStatusChangedCallback

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_OTA_STATUS_CHANGED_CALLBACK_H_
