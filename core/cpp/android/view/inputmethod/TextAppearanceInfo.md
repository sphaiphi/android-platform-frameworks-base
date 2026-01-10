# TextAppearanceInfo - Reverse Engineering Documentation

## Executive Summary
Information about text appearance (size, font, color, etc.) in an editor. Passed to IME via `CursorAnchorInfo`.

## Data Model
*   `mTextSize`, `mTextColor`, `mTextStyle`.
*   `mTextLocales`.
*   Many other Paint/TextView properties.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
