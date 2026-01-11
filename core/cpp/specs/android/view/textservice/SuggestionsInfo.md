# SuggestionsInfo - Reverse Engineering Documentation

## Executive Summary
Contains suggestions for a specific word/text segment.

## Data Model
*   **Attributes**: Flags (`RESULT_ATTR_IN_THE_DICTIONARY`, `RESULT_ATTR_LOOKS_LIKE_TYPO`, etc.).
*   **Suggestions**: String array.
*   **Cookie/Sequence**: Context tracking integers.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
