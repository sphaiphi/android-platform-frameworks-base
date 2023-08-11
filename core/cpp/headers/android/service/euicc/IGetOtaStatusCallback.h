#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_I_GET_OTA_STATUS_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_I_GET_OTA_STATUS_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace service {

namespace euicc {

class IGetOtaStatusCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(GetOtaStatusCallback)
  virtual ::android::binder::Status onSuccess(int32_t status) = 0;
};  // class IGetOtaStatusCallback

class IGetOtaStatusCallbackDefault : public IGetOtaStatusCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onSuccess(int32_t status) override;

};

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_I_GET_OTA_STATUS_CALLBACK_H_
