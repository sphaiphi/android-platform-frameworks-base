#ifndef AIDL_GENERATED_ANDROID_SPEECH_TTS_BP_TEXT_TO_SPEECH_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SPEECH_TTS_BP_TEXT_TO_SPEECH_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/speech/tts/ITextToSpeechCallback.h>

namespace android {

namespace speech {

namespace tts {

class BpTextToSpeechCallback : public ::android::BpInterface<ITextToSpeechCallback> {
public:
  explicit BpTextToSpeechCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpTextToSpeechCallback() = default;
  ::android::binder::Status onStart(const ::android::String16& utteranceId) override;
  ::android::binder::Status onSuccess(const ::android::String16& utteranceId) override;
  ::android::binder::Status onStop(const ::android::String16& utteranceId, bool isStarted) override;
  ::android::binder::Status onError(const ::android::String16& utteranceId, int32_t errorCode) override;
  ::android::binder::Status onBeginSynthesis(const ::android::String16& utteranceId, int32_t sampleRateInHz, int32_t audioFormat, int32_t channelCount) override;
  ::android::binder::Status onAudioAvailable(const ::android::String16& utteranceId, const ::std::vector<uint8_t>& audio) override;
  ::android::binder::Status onRangeStart(const ::android::String16& utteranceId, int32_t start, int32_t end, int32_t frame) override;
};  // class BpTextToSpeechCallback

}  // namespace tts

}  // namespace speech

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SPEECH_TTS_BP_TEXT_TO_SPEECH_CALLBACK_H_
