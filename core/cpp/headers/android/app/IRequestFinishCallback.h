#ifndef AIDL_GENERATED_ANDROID_APP_I_REQUEST_FINISH_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_I_REQUEST_FINISH_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

class IRequestFinishCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RequestFinishCallback)
  virtual ::android::binder::Status requestFinish() = 0;
};  // class IRequestFinishCallback

class IRequestFinishCallbackDefault : public IRequestFinishCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status requestFinish() override;

};

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_I_REQUEST_FINISH_CALLBACK_H_
