#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_APPLICATION_TOKEN_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_APPLICATION_TOKEN_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IApplicationToken.h>

namespace android {

namespace view {

class BpApplicationToken : public ::android::BpInterface<IApplicationToken> {
public:
  explicit BpApplicationToken(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpApplicationToken() = default;
  ::android::binder::Status getName(::android::String16* _aidl_return) override;
};  // class BpApplicationToken

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_APPLICATION_TOKEN_H_
