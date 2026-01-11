# ViewFocusParameterInfo - Reverse Engineering Documentation

## Executive Summary
Container for storing parameters used in `startInput`. Used to check if a new start input request is redundant (e.g., switching between non-editable views).

## Data Model
*   `mPreviousEditorInfo`.
*   `mPreviousStartInputFlags`, `Reason`, `SoftInputMode`, `WindowFlags`.

## Java-to-C++ Translation Guide
*   **Struct**: Helper struct for state comparison.
