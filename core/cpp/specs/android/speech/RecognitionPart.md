# RecognitionPart - Reverse Engineering Documentation

## Executive Summary
`RecognitionPart` is a data class (Parcelable) representing a granular component of a speech recognition result, such as a word or a character, along with metadata like timestamps and confidence scores. It is part of the `SpeechRecognizer` output.

## Data Model

### Core Fields
- `mRawText` (String): The raw text of the recognized part. Non-null.
- `mFormattedText` (String): Formatted text (optional).
- `mTimestampMillis` (long): Offset from start of session in milliseconds. Non-negative.
- `mConfidenceLevel` (int): Confidence level (1-5, or 0 for unknown).

### Constants (Confidence Levels)
- `CONFIDENCE_LEVEL_UNKNOWN` (0)
- `CONFIDENCE_LEVEL_LOW` (1)
- `CONFIDENCE_LEVEL_MEDIUM_LOW` (2)
- `CONFIDENCE_LEVEL_MEDIUM` (3)
- `CONFIDENCE_LEVEL_MEDIUM_HIGH` (4)
- `CONFIDENCE_LEVEL_HIGH` (5)

## API Reference

### Builder
- `Builder(String rawText)`: Constructor.
- `setFormattedText(String)`: Sets formatted text.
- `setTimestampMillis(long)`: Sets timestamp.
- `setConfidenceLevel(int)`: Sets confidence level.
- `build()`: Returns `RecognitionPart`.

### Accessors
- `getRawText()`
- `getFormattedText()`
- `getTimestampMillis()`
- `getConfidenceLevel()`

### Standard Methods
- `toString()`, `equals()`, `hashCode()`.
- Parcelable implementation.

## Java-to-C++ Translation Guide

### Class Mapping
- Map to a struct or class `RecognitionPart`.

### Fields
- `std::string raw_text`
- `std::optional<std::string> formatted_text`
- `int64_t timestamp_millis`
- `int32_t confidence_level` (enum)

### Serialization
- Implement `Parcelable` read/write.
    - Flags byte for nullable fields (`formatted_text`).
    - String write for text.
    - Long write for timestamp.
    - Int write for confidence.
