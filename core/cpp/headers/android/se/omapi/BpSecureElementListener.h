#ifndef AIDL_GENERATED_ANDROID_SE_OMAPI_BP_SECURE_ELEMENT_LISTENER_H_
#define AIDL_GENERATED_ANDROID_SE_OMAPI_BP_SECURE_ELEMENT_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/se/omapi/ISecureElementListener.h>

namespace android {

namespace se {

namespace omapi {

class BpSecureElementListener : public ::android::BpInterface<ISecureElementListener> {
public:
  explicit BpSecureElementListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpSecureElementListener() = default;
};  // class BpSecureElementListener

}  // namespace omapi

}  // namespace se

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SE_OMAPI_BP_SECURE_ELEMENT_LISTENER_H_
