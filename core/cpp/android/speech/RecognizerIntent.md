# RecognizerIntent - Reverse Engineering Documentation

## Executive Summary
`RecognizerIntent` defines constants (Actions, Extras, Result Codes) for Intents used to initiate speech recognition activities or services. It is the contract between applications requesting recognition and the `SpeechRecognizer` or Activity handling the request.

## API Reference

### Actions
- `ACTION_RECOGNIZE_SPEECH`: Start an activity to prompt user for speech and recognize it.
- `ACTION_WEB_SEARCH`: Start an activity for web search via speech.
- `ACTION_VOICE_SEARCH_HANDS_FREE`: Hands-free voice search.

### Request Extras (Input)
- `EXTRA_LANGUAGE_MODEL` ("free_form" or "web_search").
- `EXTRA_PROMPT`: Text prompt to show.
- `EXTRA_LANGUAGE`: IETF language tag.
- `EXTRA_MAX_RESULTS`: Limit on number of results.
- `EXTRA_PARTIAL_RESULTS`: Request partial (streaming) results.
- `EXTRA_AUDIO_SOURCE`: `ParcelFileDescriptor` for custom audio source.
- `EXTRA_AUDIO_SOURCE_...`: Config for custom audio source (sample rate, encoding, channel count).
- `EXTRA_SEGMENTED_SESSION`: Enable segmented session.
- `EXTRA_ENABLE_LANGUAGE_DETECTION`: Enable language detection.
- `EXTRA_ENABLE_LANGUAGE_SWITCH`: Enable auto language switching.
- `EXTRA_PREFER_OFFLINE`: Prefer offline engines.
- `EXTRA_SECURE`: Indicate secure mode (lock screen).

### Result Extras (Output)
- `EXTRA_RESULTS`: ArrayList of Strings (recognition text).
- `EXTRA_CONFIDENCE_SCORES`: Float array of confidence values (0.0 - 1.0).
- `EXTRA_AUDIO_SOURCE`: Audio recording (if requested/supported).

### Result Codes
- `RESULT_NO_MATCH`, `RESULT_CLIENT_ERROR`, `RESULT_SERVER_ERROR`, etc.

## Java-to-C++ Translation Guide

### Usage
- These are constant string keys and integer values.
- In C++, define these as `static const char*` or `constexpr` variables in a namespace (e.g., `android::speech::RecognizerIntent`).
- Useful for constructing `Intent` objects (if C++ Intent wrapper exists) or `Bundle` objects passed via Binder.
