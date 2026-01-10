# InlineSuggestionInfo - Reverse Engineering Documentation

## Executive Summary
Metadata for an `InlineSuggestion` (source, type, hints, pinning).

## Data Model
*   `mSource`: AUTOFILL, PLATFORM.
*   `mType`: SUGGESTION, ACTION.
*   `mInlinePresentationSpec`: UI spec.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
