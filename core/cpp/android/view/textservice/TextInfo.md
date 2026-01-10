# TextInfo - Reverse Engineering Documentation

## Executive Summary
Represents the input text passed to the Spell Checker. It holds the text, and optional cookie/sequence numbers for tracking.

## Data Model
*   **Text**: `CharSequence` (often `SpannableStringBuilder` to strip internal spans).
*   **Metadata**: Cookie, Sequence Number.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
