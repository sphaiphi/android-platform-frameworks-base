# RecognitionListener - Reverse Engineering Documentation

## Executive Summary
`RecognitionListener` is the primary callback interface for receiving speech recognition events from the `SpeechRecognizer`. It handles the lifecycle of a recognition session, from readiness to partial results, final results, and errors.

## API Reference

### Methods
- `void onReadyForSpeech(Bundle params)`: Called when the system is ready to listen.
- `void onBeginningOfSpeech()`: Called when the user starts speaking.
- `void onRmsChanged(float rmsdB)`: Called when the audio volume level changes (buffer visualization).
- `void onBufferReceived(byte[] buffer)`: Called when raw audio buffer is received.
- `void onEndOfSpeech()`: Called when the user stops speaking.
- `void onError(int error)`: Called on error. Error codes defined in `SpeechRecognizer`.
- `void onResults(Bundle results)`: Called with final recognition results (N-best list).
- `void onPartialResults(Bundle partialResults)`: Called with partial (streaming) results.
- `void onSegmentResults(Bundle segmentResults)`: Called with results for a segment (for segmented sessions). Default empty implementation.
- `void onEndOfSegmentedSession()`: Called at the end of a segmented session. Default empty implementation.
- `void onLanguageDetection(Bundle results)`: Called with language detection/switching results. Default empty implementation.
- `void onEvent(int eventType, Bundle params)`: Generic event callback.

## Java-to-C++ Translation Guide

### Type
- Map to an abstract base class (interface) `IRecognitionListener` (following the AIDL definition).

### Methods
- `virtual void onReadyForSpeech(const Bundle& params) = 0;`
- `virtual void onBeginningOfSpeech() = 0;`
- `virtual void onRmsChanged(float rmsdB) = 0;`
- `virtual void onBufferReceived(const std::vector<uint8_t>& buffer) = 0;`
- `virtual void onEndOfSpeech() = 0;`
- `virtual void onError(int32_t error) = 0;`
- `virtual void onResults(const Bundle& results) = 0;`
- `virtual void onPartialResults(const Bundle& results) = 0;`
- `virtual void onSegmentResults(const Bundle& segmentResults) = 0;`
- `virtual void onEndOfSegmentedSession() = 0;`
- `virtual void onLanguageDetection(const Bundle& results) = 0;`
- `virtual void onEvent(int32_t eventType, const Bundle& params) = 0;`

### Data Types
- `Bundle`: Requires a C++ equivalent map/dictionary structure capable of holding various types (likely `android::os::Bundle`).
