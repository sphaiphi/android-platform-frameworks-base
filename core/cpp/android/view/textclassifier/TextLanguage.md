# TextLanguage - Reverse Engineering Documentation

## Executive Summary
Result of a language detection request. Contains a list of `ULocale` hypotheses with confidence scores.

## Nested Classes
*   **Request**: Arguments for `detectLanguage` (text, bundle).
*   **Builder**: Builder pattern.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
*   **ICU**: Uses `ULocale` (ICU).
