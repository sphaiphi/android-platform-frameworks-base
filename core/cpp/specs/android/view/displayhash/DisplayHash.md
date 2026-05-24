# DisplayHash - Reverse Engineering Documentation

## Executive Summary
A Parcelable data class representing a hash of a portion of the display. It contains the image hash itself, metadata about when and where it was generated, and an HMAC for system-level verification.

## Data Model
*   **Time**: `mTimeMillis` (Timestamp of generation).
*   **Bounds**: `mBoundsInWindow` (The `Rect` area hashed, in window coordinates).
*   **Algorithm**: `mHashAlgorithm` (The name of the hashing algorithm used).
*   **Hashes**:
    *   `mImageHash`: The actual perceptual/image hash.
    *   `mHmac`: A system-generated HMAC used to ensure the hash was produced by the Android system and hasn't been tampered with.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard AIDL/Binder serialization.
*   **Security**: The `mHmac` field is sensitive and intended for system-process verification.
