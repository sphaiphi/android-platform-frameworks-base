# TranslationRequestValue - Reverse Engineering Documentation

## Executive Summary
A wrapper for a single piece of content to be translated within a `TranslationRequest`. Currently mainly wraps text.

## Data Model
*   **Content**: `CharSequence mText`.

## Java-to-C++ Translation Guide
*   **String Handling**: `CharSequence` usually maps to `std::string` (UTF-8) or `std::u16string` (UTF-16) depending on Android platform conventions (often UTF-16 in Framework layers).
