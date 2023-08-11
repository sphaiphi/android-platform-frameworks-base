#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_I_GET_EID_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_I_GET_EID_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace service {

namespace euicc {

class IGetEidCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(GetEidCallback)
  virtual ::android::binder::Status onSuccess(const ::android::String16& eid) = 0;
};  // class IGetEidCallback

class IGetEidCallbackDefault : public IGetEidCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onSuccess(const ::android::String16& eid) override;

};

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_I_GET_EID_CALLBACK_H_
