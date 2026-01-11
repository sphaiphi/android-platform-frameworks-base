# TranslationContext - Reverse Engineering Documentation

## Executive Summary
A Parcelable data class providing context for creating a `Translator`. It defines what language pair is needed and specific configuration flags (low latency, transliteration, etc.).

## Data Model
*   **Specs**: `mSourceSpec`, `mTargetSpec` (TranslationSpec).
*   **Flags (`int`)**:
    *   `FLAG_LOW_LATENCY` (0x1)
    *   `FLAG_TRANSLITERATION` (0x2)
    *   `FLAG_DEFINITIONS` (0x4)
*   **ActivityId**: Optional ID associating the context with a specific activity (for UI translation).

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard AIDL/Binder mapping.
*   **Builder Pattern**: Used for construction in Java, similar pattern or struct initialization in C++.
