# CompletionInfo - Reverse Engineering Documentation

## Executive Summary
Simple data class representing a single completion suggestion from an editor to the IME.

## Data Model
*   `mId`: long ID.
*   `mPosition`: int index.
*   `mText`: CharSequence (text to insert).
*   `mLabel`: CharSequence (label to show).

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
