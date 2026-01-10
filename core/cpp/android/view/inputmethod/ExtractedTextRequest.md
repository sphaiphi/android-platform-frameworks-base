# ExtractedTextRequest - Reverse Engineering Documentation

## Executive Summary
Request parameters for `getExtractedText`.

## Data Model
*   `token`: int.
*   `flags`: int.
*   `hintMaxLines`, `hintMaxChars`: ints.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
