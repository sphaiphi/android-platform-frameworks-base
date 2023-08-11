#ifndef AIDL_GENERATED_ANDROID_APP_I_SEARCH_MANAGER_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_APP_I_SEARCH_MANAGER_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace app {

class ISearchManagerCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(SearchManagerCallback)
  virtual ::android::binder::Status onDismiss() = 0;
  virtual ::android::binder::Status onCancel() = 0;
};  // class ISearchManagerCallback

class ISearchManagerCallbackDefault : public ISearchManagerCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onDismiss() override;
  ::android::binder::Status onCancel() override;

};

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_I_SEARCH_MANAGER_CALLBACK_H_
