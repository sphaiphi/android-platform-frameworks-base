#ifndef AIDL_GENERATED_ANDROID_NFC_BN_TAG_REMOVED_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_NFC_BN_TAG_REMOVED_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/nfc/ITagRemovedCallback.h>

namespace android {

namespace nfc {

class BnTagRemovedCallback : public ::android::BnInterface<ITagRemovedCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnTagRemovedCallback

}  // namespace nfc

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_NFC_BN_TAG_REMOVED_CALLBACK_H_
