# Parcelable - Reverse Engineering Documentation

## Executive Summary
`Parcelable` is an interface for classes that can be marshaled to/from a `Parcel`. It is the Android equivalent of serialization but optimized for IPC performance (avoiding reflection).

## Architecture Overview
-   **Contract**:
    -   `writeToParcel(Parcel dest, int flags)`: Serialize state.
    -   `describeContents()`: Bitmask (e.g., `CONTENTS_FILE_DESCRIPTOR`).
    -   `static CREATOR`: `Parcelable.Creator<T>` factory for deserialization.

## Data Model
-   **Creator**:
    -   `createFromParcel(Parcel source)`
    -   `newArray(int size)`

## API Reference
-   `PARCELABLE_WRITE_RETURN_VALUE`: Flag indicating the object is being returned from a function.
-   `PARCELABLE_STABILITY_VINTF`: Flag for AIDL stability guarantees.

## Java-to-C++ Translation Guide
-   **Equivalent**: `android::Parcelable` (C++ interface in binder).
-   **Serialization**: C++ classes implement `writeToParcel` and `readFromParcel`.
-   **AIDL**: The AIDL compiler generates the `Parcelable` implementation (C++ and Java) automatically for structured data. Manual implementation is required for custom objects.
