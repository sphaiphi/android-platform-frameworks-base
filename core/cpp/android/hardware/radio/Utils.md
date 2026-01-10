# Utils - Reverse Engineering Documentation

## Executive Summary
`Utils` provides static helper methods for serializing and deserializing common collection types (Maps, Sets) to and from `Parcel` objects, and for handling `ICloseHandle` resources.

## Architecture Overview
-   **Type**: Package-Private Utility Class.
-   **Package**: `android.hardware.radio`.
-   **Role**: Serialization helper.

## Detailed Functionality

### Methods
-   `writeStringMap`/`readStringMap`: Handles `Map<String, String>`.
    -   Format: Size (int) -> [Key (String), Value (String)]...
-   `writeStringIntMap`/`readStringIntMap`: Handles `Map<String, Integer>`.
    -   Format: Size (int) -> [Key (String), Value (Int)]...
-   `writeSet`/`createSet`: Handles `Set<T extends Parcelable>`.
    -   Format: Size (int) -> [Parcelable]...
-   `writeIntSet`/`createIntSet`: Handles `Set<Integer>`.
    -   Format: Size (int) -> [Int]...
-   `writeTypedCollection`: Writes a collection as a typed list.
-   `close(ICloseHandle)`: Safely closes a remote handle, rethrowing `RemoteException` as RuntimeException.

## Java-to-C++ Translation Guide
-   **Parcel Helpers**: In C++, use `android::Parcel` methods (`writeMap`, `readMap`, `writeInt32`, `writeString16`).
-   **Containers**: Map Java `Map` to `std::map` and `Set` to `std::set` or `std::vector` (if order/uniqueness logic is handled).
-   **Close Handle**: `ICloseHandle` maps to `sp<ICloseHandle>`, call `close()` on it.

---
