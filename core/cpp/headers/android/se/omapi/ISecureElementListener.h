#ifndef AIDL_GENERATED_ANDROID_SE_OMAPI_I_SECURE_ELEMENT_LISTENER_H_
#define AIDL_GENERATED_ANDROID_SE_OMAPI_I_SECURE_ELEMENT_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace se {

namespace omapi {

class ISecureElementListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(SecureElementListener)
};  // class ISecureElementListener

class ISecureElementListenerDefault : public ISecureElementListener {
public:
  ::android::IBinder* onAsBinder() override;
  
};

}  // namespace omapi

}  // namespace se

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SE_OMAPI_I_SECURE_ELEMENT_LISTENER_H_
