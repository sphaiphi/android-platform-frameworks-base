# TranslationRequest - Reverse Engineering Documentation

## Executive Summary
A Parcelable data class representing a request to translate content. It can contain raw values or view-based requests.

## Data Model
*   **Flags**:
    *   `FLAG_TRANSLATION_RESULT` (0x1)
    *   `FLAG_DICTIONARY_RESULT` (0x2)
    *   `FLAG_TRANSLITERATION_RESULT` (0x4)
    *   `FLAG_PARTIAL_RESPONSES` (0x8)
*   **Values**:
    *   `mTranslationRequestValues`: List of `TranslationRequestValue` (raw text).
    *   `mViewTranslationRequests`: List of `ViewTranslationRequest` (view hierarchy data).

## Java-to-C++ Translation Guide
*   **Collections**: `List<T>` maps to `std::vector<T>`.
*   **Data Class**: Standard struct with serialization.
