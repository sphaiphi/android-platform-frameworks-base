#ifndef AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_GET_EID_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_GET_EID_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/euicc/IGetEidCallback.h>

namespace android {

namespace service {

namespace euicc {

class BpGetEidCallback : public ::android::BpInterface<IGetEidCallback> {
public:
  explicit BpGetEidCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpGetEidCallback() = default;
  ::android::binder::Status onSuccess(const ::android::String16& eid) override;
};  // class BpGetEidCallback

}  // namespace euicc

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_EUICC_BP_GET_EID_CALLBACK_H_
