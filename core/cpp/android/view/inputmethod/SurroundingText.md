# SurroundingText - Reverse Engineering Documentation

## Executive Summary
Snapshot of text surrounding the cursor. Includes the text, selection start/end, and an offset.

## Data Model
*   `mText`: CharSequence.
*   `mSelectionStart`, `mSelectionEnd`.
*   `mOffset`.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
