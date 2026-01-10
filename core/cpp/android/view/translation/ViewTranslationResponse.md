# ViewTranslationResponse - Reverse Engineering Documentation

## Executive Summary
Represents the translated results for a specific View.

## Data Model
*   **ID**: `AutofillId`.
*   **Values**: Map of `String` (key) -> `TranslationResponseValue`.

## Java-to-C++ Translation Guide
*   **Mirror of Request**: Structure matches `ViewTranslationRequest` but contains response values.
