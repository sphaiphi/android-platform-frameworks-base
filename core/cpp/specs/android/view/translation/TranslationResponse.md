# TranslationResponse - Reverse Engineering Documentation

## Executive Summary
A Parcelable data class representing the result from the translation service. It mirrors the structure of the request.

## Data Model
*   **Status**: `SUCCESS`, `UNKNOWN_ERROR`, `CONTEXT_UNSUPPORTED`.
*   **Values**:
    *   `mTranslationResponseValues`: `SparseArray` mapping request index to `TranslationResponseValue`.
    *   `mViewTranslationResponses`: `SparseArray` mapping request index to `ViewTranslationResponse`.
*   **Partial Responses**: `mFinalResponse` boolean indicates if more chunks are coming.

## Java-to-C++ Translation Guide
*   **SparseArray**: Maps to `std::map<int, T>` or specialized sparse container.
*   **Parcelable**: Standard serialization.
