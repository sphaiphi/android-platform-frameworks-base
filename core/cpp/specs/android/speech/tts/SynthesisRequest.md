# SynthesisRequest - Reverse Engineering Documentation

## Executive Summary
`SynthesisRequest` is a data class containing all the information required by a TTS engine to synthesize a single request. it includes the text, locale, voice parameters, and additional engine-specific parameters.

## Data Model

### Core Fields
- `mText` (CharSequence): The text to synthesize.
- `mParams` (Bundle): Extra parameters (e.g., stream type, volume, pan).
- `mLanguage`, `mCountry`, `mVariant`: Locale info (ISO 3-letter codes).
- `mVoiceName`: Name of the specific voice requested.
- `mSpeechRate`, `mPitch`: User preferences (100 = normal).
- `mCallerUid`: UID of the requesting application.

## API Reference

### Accessors
- `getText()` / `getCharSequenceText()`
- `getLanguage()`, `getCountry()`, `getVariant()`
- `getVoiceName()`
- `getSpeechRate()`, `getPitch()`
- `getParams()`
- `getCallerUid()`

## Java-to-C++ Translation Guide
- Map to a struct or class `SynthesisRequest`.
- Use a `Bundle` equivalent for `mParams`.
- Strings should be `std::string` or `std::u16string`.
