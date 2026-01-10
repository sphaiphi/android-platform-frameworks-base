# TranslationResponseValue - Reverse Engineering Documentation

## Executive Summary
A specific translated value. Contains the text, status, and optional extras (like dictionary definitions).

## Data Model
*   **Status**: `SUCCESS` (0), `ERROR` (1).
*   **Content**:
    *   `mText`: The translated text.
    *   `mTransliteration`: Pronunciation guide.
    *   `mExtras`: `Bundle`, usually containing dictionary definitions under `EXTRA_DEFINITIONS`.

## Java-to-C++ Translation Guide
*   **Bundle**: `android.os.Bundle` translates to a `PersistableBundle` or key-value map in C++ binder interfaces.
