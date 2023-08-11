#ifndef AIDL_GENERATED_ANDROID_SPEECH_TTS_I_TEXT_TO_SPEECH_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_SPEECH_TTS_I_TEXT_TO_SPEECH_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace speech {

namespace tts {

class ITextToSpeechCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(TextToSpeechCallback)
  virtual ::android::binder::Status onStart(const ::android::String16& utteranceId) = 0;
  virtual ::android::binder::Status onSuccess(const ::android::String16& utteranceId) = 0;
  virtual ::android::binder::Status onStop(const ::android::String16& utteranceId, bool isStarted) = 0;
  virtual ::android::binder::Status onError(const ::android::String16& utteranceId, int32_t errorCode) = 0;
  virtual ::android::binder::Status onBeginSynthesis(const ::android::String16& utteranceId, int32_t sampleRateInHz, int32_t audioFormat, int32_t channelCount) = 0;
  virtual ::android::binder::Status onAudioAvailable(const ::android::String16& utteranceId, const ::std::vector<uint8_t>& audio) = 0;
  virtual ::android::binder::Status onRangeStart(const ::android::String16& utteranceId, int32_t start, int32_t end, int32_t frame) = 0;
};  // class ITextToSpeechCallback

class ITextToSpeechCallbackDefault : public ITextToSpeechCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onStart(const ::android::String16& utteranceId) override;
  ::android::binder::Status onSuccess(const ::android::String16& utteranceId) override;
  ::android::binder::Status onStop(const ::android::String16& utteranceId, bool isStarted) override;
  ::android::binder::Status onError(const ::android::String16& utteranceId, int32_t errorCode) override;
  ::android::binder::Status onBeginSynthesis(const ::android::String16& utteranceId, int32_t sampleRateInHz, int32_t audioFormat, int32_t channelCount) override;
  ::android::binder::Status onAudioAvailable(const ::android::String16& utteranceId, const ::std::vector<uint8_t>& audio) override;
  ::android::binder::Status onRangeStart(const ::android::String16& utteranceId, int32_t start, int32_t end, int32_t frame) override;

};

}  // namespace tts

}  // namespace speech

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_SPEECH_TTS_I_TEXT_TO_SPEECH_CALLBACK_H_
