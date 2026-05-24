# UiTranslationSpec - Reverse Engineering Documentation

## Executive Summary
Configuration for UI translation. Currently focuses on compatibility options.

## Data Model
*   **`mShouldPadContentForCompat`**: Boolean. If true, `TextView`s might be padded with spaces to match the length of the translated text. This prevents crashes in apps that assume text length doesn't change (e.g., using `DynamicLayout` offsets).

## Java-to-C++ Translation Guide
*   **Simple Config**: Struct with boolean flags.
