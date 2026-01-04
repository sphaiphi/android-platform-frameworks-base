# VerifiedKeyEvent - Reverse Engineering Documentation

## Executive Summary
`VerifiedKeyEvent` is a Parcelable data class containing a subset of a `KeyEvent` that has been authenticated by the system. it ensures that the core details of a key event (Action, KeyCode, MetaState) are reliable and haven't been tampered with.

## Data Model
*   **`mAction`**: The authenticated key action (Down or Up).
*   **`mKeyCode`**: The authenticated hardware key code.
*   **`mMetaState`**: The authenticated state of modifier keys.
*   **`mDownTimeNanos`**: The authenticated timestamp of the initial key press.

## Detailed Functionality
*   **Inheritance**: Extends `VerifiedInputEvent`.
*   **Verification**: Implements `getFlag()` to check specific authenticated properties like `FLAG_CANCELED`.

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap `android::VerifiedKeyEvent`.
*   **Parceling**: Bit-for-bit parity with `frameworks/native/libs/input/`.

## Implementation Risks
*   **Data Completeness**: Does NOT contain all fields of a standard `KeyEvent` (e.g., repeating count or scan code details might be limited).
