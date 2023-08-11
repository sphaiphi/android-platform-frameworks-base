#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_I_OTA_STATUS_CHANGED_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_I_OTA_STATUS_CHANGED_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace service {

namespace euicc {

class IOtaStatusChangedCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(OtaStatusChangedCallback)
  virtual ::android::binder::Status onOtaStatusChanged(int32_t status) = 0;
};  // class IOtaStatusChangedCallback

class IOtaStatusChangedCallbackDefault : public IOtaStatusChangedCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onOtaStatusChanged(int32_t status) override;

};

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_I_OTA_STATUS_CHANGED_CALLBACK_H_
