#ifndef AIDL_GENERATED_ANDROID_NFC_BP_TAG_REMOVED_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_NFC_BP_TAG_REMOVED_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/nfc/ITagRemovedCallback.h>

namespace android {

namespace nfc {

class BpTagRemovedCallback : public ::android::BpInterface<ITagRemovedCallback> {
public:
  explicit BpTagRemovedCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpTagRemovedCallback() = default;
  ::android::binder::Status onTagRemoved() override;
};  // class BpTagRemovedCallback

}  // namespace nfc

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NFC_BP_TAG_REMOVED_CALLBACK_H_
