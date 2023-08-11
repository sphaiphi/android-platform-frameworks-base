#ifndef AIDL_GENERATED_ANDROID_OS_STORAGE_I_OBB_ACTION_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_STORAGE_I_OBB_ACTION_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

namespace storage {

class IObbActionListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(ObbActionListener)
  virtual ::android::binder::Status onObbResult(const ::android::String16& filename, int32_t nonce, int32_t status) = 0;
};  // class IObbActionListener

class IObbActionListenerDefault : public IObbActionListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onObbResult(const ::android::String16& filename, int32_t nonce, int32_t status) override;

};

}  // namespace storage

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_STORAGE_I_OBB_ACTION_LISTENER_H_
