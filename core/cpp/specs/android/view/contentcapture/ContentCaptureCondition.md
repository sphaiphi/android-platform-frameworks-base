# ContentCaptureCondition - Reverse Engineering Documentation

## Executive Summary
Defines conditions under which content capture should be allowed (e.g., matching a LocusId, potentially with Regex).

## Data Model
*   `mLocusId`: The identifier to match.
*   `mFlags`: `FLAG_IS_REGEX` (0x2).

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
*   **Regex**: C++ `std::regex`.
