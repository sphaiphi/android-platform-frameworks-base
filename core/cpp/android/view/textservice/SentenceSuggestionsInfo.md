# SentenceSuggestionsInfo - Reverse Engineering Documentation

## Executive Summary
A container for suggestions returned by a text service (e.g., Spell Checker) for an entire sentence. It holds multiple `SuggestionsInfo` objects, along with their offsets and lengths within the original sentence.

## Data Model
*   **Suggestions**: Array of `SuggestionsInfo`.
*   **Offsets**: Array of ints (start indices).
*   **Lengths**: Array of ints (lengths of text segments).

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
*   **Arrays**: Map to `std::vector` or raw arrays.
