# KeystoreArguments - Reverse Engineering Documentation

## Executive Summary
`KeystoreArguments` is a simple Parcelable container used to pass byte array arguments to Keystore binder calls.

## Architecture Overview
*   **Package**: `android.security`
*   **Type**: Class (Parcelable)
*   **Structure**: A wrapper around a 2D byte array (`byte[][]`).

## Data Model
*   `public byte[][] args`: The arguments.

## Serialization (Parcelable)
*   **Write**:
    *   Writes length of the outer array.
    *   Writes each byte array via `writeByteArray`.
*   **Read**:
    *   Reads length.
    *   Allocates outer array.
    *   Reads each byte array via `createByteArray`.

## Java-to-C++ Translation Guide
*   **Type**: `std::vector<std::vector<uint8_t>>` or `std::vector<android::os::String16>` depending on usage, but strictly it is bytes.
*   **Parceling**: Standard C++ Binder (AIDL) mapping for `byte[][]` should be verified. If manual parceling is needed, match the Java logic: count (int32) -> loop -> blob.
