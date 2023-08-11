#ifndef AIDL_GENERATED_ANDROID_NFC_I_TAG_REMOVED_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_NFC_I_TAG_REMOVED_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace nfc {

class ITagRemovedCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(TagRemovedCallback)
  virtual ::android::binder::Status onTagRemoved() = 0;
};  // class ITagRemovedCallback

class ITagRemovedCallbackDefault : public ITagRemovedCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onTagRemoved() override;

};

}  // namespace nfc

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NFC_I_TAG_REMOVED_CALLBACK_H_
