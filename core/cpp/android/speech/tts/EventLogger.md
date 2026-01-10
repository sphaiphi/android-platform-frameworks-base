# EventLogger - Reverse Engineering Documentation

## Executive Summary
`EventLogger` is a concrete implementation of `AbstractEventLogger` that logs synthesis events to the Android system event log (`EventLogTags`). It extracts metadata like utterance length and locale from a `SynthesisRequest`.

## Detailed Functionality

### Logging Logic
- `logFailure(statusCode)`: Writes `tts_speak_failure` to the event log if the status isn't `STOPPED`.
- `logSuccess(audioLatency, engineLatency, engineTotal)`: Writes `tts_speak_success` with all calculated latencies.

### Metadata Extraction
- **Utterance Length**: Returns `text.length()` or 0 if null.
- **Locale String**: Formats as `lang-country-variant`. Handles empty country/variant gracefully.

## Java-to-C++ Translation Guide

### Mapping
- Use `android_log_write` or equivalent event logging macros in C++.
- Ensure the format of the locale string matches the Java implementation for consistency in analytics.
