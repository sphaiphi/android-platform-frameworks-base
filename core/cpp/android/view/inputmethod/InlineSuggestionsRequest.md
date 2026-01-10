# InlineSuggestionsRequest - Reverse Engineering Documentation

## Executive Summary
Request for inline suggestions. Contains constraints like max count, supported locales, and presentation specs.

## Data Model
*   `mMaxSuggestionCount`.
*   `mInlinePresentationSpecs`.
*   `mHostPackageName`.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
