# ViewTranslationRequest - Reverse Engineering Documentation

## Executive Summary
Represents a translation request for a specific View. It captures the View's identity (`AutofillId`) and the specific content keys to translate (e.g., "android:text").

## Data Model
*   **ID**: `AutofillId`.
*   **Values**: Map of `String` (key) -> `TranslationRequestValue`.
*   **Keys**: `ID_TEXT`, `ID_CONTENT_DESCRIPTION`.

## Java-to-C++ Translation Guide
*   **AutofillId**: Needs a corresponding identifier structure.
*   **Map**: `std::map<std::string, TranslationRequestValue>`.
