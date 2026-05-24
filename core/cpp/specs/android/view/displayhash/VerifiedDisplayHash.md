# VerifiedDisplayHash - Reverse Engineering Documentation

## Executive Summary
A data class representing a `DisplayHash` that has been successfully verified by the system. It contains the same information as `DisplayHash` but excludes the `mHmac` field, as the verification has already taken place.

## Data Model
*   `mTimeMillis`: Timestamp.
*   `mBoundsInWindow`: `Rect` area.
*   `mHashAlgorithm`: Algorithm name.
*   `mImageHash`: The validated image hash.

## Java-to-C++ Translation Guide
*   **Data Structure**: Mirror of `DisplayHash` (excluding HMAC).
