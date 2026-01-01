# KeyphraseMetadata - Reverse Engineering Documentation

## Executive Summary
`KeyphraseMetadata` stores static information about a specific voice keyphrase (e.g., "OK Google") supported by an enrollment application. it defines the keyphrase text, supported locales, and the allowed recognition modes for that phrase.

## Architecture Overview
- **Data Source**: Read from an enrollment app's manifest metadata (`android.voice_enrollment`).
- **Storage**: Immutable data class.
- **Usage**: Used by `KeyphraseEnrollmentInfo` to discover and manage voice triggers.

## Detailed Functionality

### Phrase and Locale Matching
**Purpose**: To determine if a specific user request for enrollment can be handled by the current model.
**Algorithm**:
- `supportsPhrase(String)`: Checks if the requested phrase matches the metadata (case-insensitive).
- `supportsLocale(Locale)`: Checks if the requested locale is in the supported set.

### Recognition Flags
**Purpose**: To indicate how the keyphrase can be detected.
**Flags**: Maps to `SoundTrigger.RECOGNITION_MODE_*` constants (e.g., `VOICE_TRIGGER`, `USER_IDENTIFICATION`).

## Data Model

### Members
- `mId`: Unique keyphrase ID.
- `mKeyphrase`: The actual wake-word text.
- `mSupportedLocales`: Set of Java `Locale` objects.
- `mRecognitionModeFlags`: Bitmask of supported detection modes.

## API Reference

### Public Methods
- `int getId()`
- `String getKeyphrase()`
- `Set<Locale> getSupportedLocales()`
- `int getRecognitionModeFlags()`
- `boolean supportsPhrase(String)`
- `boolean supportsLocale(Locale)`

## Java-to-C++ Translation Guide

### Data Structures
- **Java**: `ArraySet<Locale>`.
- **C++**: `std::set<std::string>` (storing BCP-47 tags) or `std::set<icu::Locale>`.

### Serialization
- **Java**: Automatic via `@DataClass` and `Parcelable`.
- **C++**: Implement `android::Parcelable` or a JSON/FlatBuffers serializer for persistence.

## Test Cases & Validation
1. **Locale Set**: Verify that "en-US" matches a set containing only "en".
2. **Case Sensitivity**: Ensure "ok google" matches "OK Google".
3. **Empty Phrase**: Check if an empty phrase in metadata acts as a wildcard (matching all phrases).
