# CorrectionInfo - Reverse Engineering Documentation

## Executive Summary
Data class representing a text correction (e.g., spell check fix) reported by the editor to the IME.

## Data Model
*   `mOffset`: int.
*   `mOldText`: CharSequence.
*   `mNewText`: CharSequence.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
