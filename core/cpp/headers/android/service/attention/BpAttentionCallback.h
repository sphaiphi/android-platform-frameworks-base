#ifndef AIDL_GENERATED_ANDROID_SERVICE_ATTENTION_BP_ATTENTION_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_ATTENTION_BP_ATTENTION_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/service/attention/IAttentionCallback.h>

namespace android {

namespace service {

namespace attention {

class BpAttentionCallback : public ::android::BpInterface<IAttentionCallback> {
public:
  explicit BpAttentionCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAttentionCallback() = default;
  ::android::binder::Status onSuccess(int32_t result, int64_t timestamp) override;
  ::android::binder::Status onFailure(int32_t error) override;
};  // class BpAttentionCallback

}  // namespace attention

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_ATTENTION_BP_ATTENTION_CALLBACK_H_
