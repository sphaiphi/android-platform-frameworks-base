# Query - Reverse Engineering Documentation

## Executive Summary
`Query` is a Parcelable data transfer object (DTO) used to pass search box input and context from the client to the system search service. It encapsulates the user's input string, a timestamp, and optional UI constraints (extras).

## Architecture Overview
- **Package**: `android.app.search`
- **Type**: `Parcelable` class, `final`
- **Role**: Data carrier for search queries initiated by `SearchSession`.

## Detailed Functionality

### Constructors
1.  **Primary Constructor**:
    -   **Inputs**: `String input`, `long timestampMillis`, `Bundle extras`
    -   **Logic**:
        -   Assigns inputs to fields.
        -   If `extras` is null, initializes an empty `Bundle`.
2.  **Convenience Constructor**:
    -   **Inputs**: `String input`, `long timestampMillis`
    -   **Logic**: Calls primary constructor with an empty `Bundle`.

### Field Accessors
-   `getInput()`: Returns the search string.
-   `getTimestampMillis()`: Returns the timestamp (base `SystemClock.elapsedRealtime()`).
-   `getExtras()`: Returns the extras Bundle (ensures non-null).

## Data Model

| Field Name | Type | Description |
| :--- | :--- | :--- |
| `mInput` | `String` | The user's search query text. Non-null. |
| `mTimestampMillis` | `long` | Timestamp of query creation. |
| `mExtras` | `Bundle` | Additional UI constraints (e.g., IME height). Non-null. |

## API Reference
-   `Query(@NonNull String input, long timestampMillis, @NonNull Bundle extras)`
-   `String getInput()`
-   `long getTimestampMillis()`
-   `Bundle getExtras()`

## Java-to-C++ Translation Guide

### Serialization (Parcelable)
The `writeToParcel` method serializes fields in the following order:

1.  **Input String**:
    -   Java: `dest.writeString(mInput)`
    -   C++: `parcel->writeString16(mInput)` (Standard string serialization)
2.  **Timestamp**:
    -   Java: `dest.writeLong(mTimestampMillis)`
    -   C++: `parcel->writeInt64(mTimestampMillis)`
3.  **Extras**:
    -   Java: `dest.writeBundle(mExtras)`
    -   C++: `parcel->writeBundle(mExtras)`

### Reading from Parcel
The private constructor `Query(Parcel parcel)` reads in the exact same order:
1.  `readString`
2.  `readLong`
3.  `readBundle`

## Implementation Risks
-   **Bundle Handling**: Ensure the C++ `Bundle` implementation handles the `null` case if the IPC mechanism allows sending null bundles (though the class logic ensures `mExtras` is not null, `readBundle` can return null depending on the binder implementation, so the C++ constructor should handle that).
-   **String Encoding**: Verify if `writeString` maps to UTF-16 in the specific binder context. Standard Android Binder usually uses UTF-16 for strings.

## Questions for C++ Team
-   None.
