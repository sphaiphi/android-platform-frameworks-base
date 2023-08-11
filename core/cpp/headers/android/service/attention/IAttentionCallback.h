#ifndef AIDL_GENERATED_ANDROID_SERVICE_ATTENTION_I_ATTENTION_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SERVICE_ATTENTION_I_ATTENTION_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace service {

namespace attention {

class IAttentionCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AttentionCallback)
  virtual ::android::binder::Status onSuccess(int32_t result, int64_t timestamp) = 0;
  virtual ::android::binder::Status onFailure(int32_t error) = 0;
};  // class IAttentionCallback

class IAttentionCallbackDefault : public IAttentionCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onSuccess(int32_t result, int64_t timestamp) override;
  ::android::binder::Status onFailure(int32_t error) override;

};

}  // namespace attention

}  // namespace service

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SERVICE_ATTENTION_I_ATTENTION_CALLBACK_H_
