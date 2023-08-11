#ifndef AIDL_GENERATED_ANDROID_VIEW_I_APPLICATION_TOKEN_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_APPLICATION_TOKEN_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IApplicationToken : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(ApplicationToken)
  virtual ::android::binder::Status getName(::android::String16* _aidl_return) = 0;
};  // class IApplicationToken

class IApplicationTokenDefault : public IApplicationToken {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status getName(::android::String16* _aidl_return) override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_APPLICATION_TOKEN_H_
