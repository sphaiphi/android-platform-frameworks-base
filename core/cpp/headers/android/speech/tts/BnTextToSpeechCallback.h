#ifndef AIDL_GENERATED_ANDROID_SPEECH_TTS_BN_TEXT_TO_SPEECH_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SPEECH_TTS_BN_TEXT_TO_SPEECH_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/speech/tts/ITextToSpeechCallback.h>

namespace android {

namespace speech {

namespace tts {

class BnTextToSpeechCallback : public ::android::BnInterface<ITextToSpeechCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnTextToSpeechCallback

}  // namespace tts

}  // namespace speech

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SPEECH_TTS_BN_TEXT_TO_SPEECH_CALLBACK_H_
