# ExtractedText - Reverse Engineering Documentation

## Executive Summary
Information about extracted text sent from Editor to IME (for fullscreen mode extraction).

## Data Model
*   `text`: CharSequence.
*   `startOffset`: int.
*   `selectionStart/End`: int.
*   `flags`: SINGLE_LINE, SELECTING.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
