# SearchRequest - Reverse Engineering Documentation

## Executive Summary
`SearchRequest` is a data carrier class used to encapsulate all parameters required to perform a cloud search. It is `Parcelable`, allowing it to be transferred across process boundaries (IPC). It uses the Builder pattern for construction.

## Architecture Overview
*   **Pattern**: Immutable Data Object / Builder Pattern.
*   **Role**: Request DTO (Data Transfer Object) for `CloudSearchManager`.
*   **Key Dependencies**: `android.os.Bundle` for extensible constraints.

## Detailed Functionality

### Core Fields
*   **Query**: The text string to search for.
*   **ResultOffset**: Pagination offset (int).
*   **ResultNumber**: Number of results requested (int).
*   **MaxLatencyMillis**: Maximum time allowed for the search (float).
*   **SearchConstraints**: A `Bundle` containing generic key-value constraints.
*   **CallerPackageName**: The package name of the app making the request.
*   **RequestId**: A unique identifier for the request.

### Constants (Search Constraints)
*   `CONSTRAINT_IS_PRESUBMIT_SUGGESTION`: Boolean key. Indicates if the query is partial (as user types).
*   `CONSTRAINT_SEARCH_PROVIDER_FILTER`: String key. Semicolon-separated list of package names to restrict search providers.

### Constructor & Builder
*   Private constructor enforces usage of the `Builder`.
*   `Builder` allows setting optional fields, with sensible defaults (though defaults in getters currently return empty/zero values in the provided source).

**Java-Specific Notes**:
*   **`Parcelable`**: Implements Android's optimized serialization for IPC.
*   **`Bundle`**: Used for `searchConstraints` to allow adding new parameters without changing the API signature.
*   **`@StringDef`**: Annotation used for compile-time validation of constraint keys.

**C++ Implementation Guidance**:
*   Implement `Parcelable` read/write logic matching the Java implementation (not fully shown in source, but standard order is expected).
*   `Bundle` maps to a flexible dictionary type (e.g., `std::map<std::string, std::variant<...>>` or `android::os::Bundle` in native code).

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `query` | `String` | The user's search query. |
| `resultOffset` | `int` | Pagination start index. |
| `resultNumber` | `int` | Max results to return. |
| `maxLatencyMillis` | `float` | Timeout/latency preference. |
| `searchConstraints` | `Bundle` | Map of extra constraints. |
| `callerPackageName` | `String` | Identity of the caller. |
| `requestId` | `String` | Unique ID. |

## API Reference

### Getters
*   `getQuery()`: Returns string.
*   `getResultOffset()`: Returns int.
*   `getResultNumber()`: Returns int.
*   `getMaxLatencyMillis()`: Returns float.
*   `getSearchConstraints()`: Returns Bundle (non-null).
*   `getCallerPackageName()`: Returns string.
*   `getRequestId()`: Returns string.

### Setters (via Builder)
*   Standard fluent setters matching the fields.
*   `setCallerPackageName` is also exposed on the request object itself (likely for system server use).

## Java-to-C++ Translation Guide

| Java Feature | C++ Equivalent | Notes |
| :--- | :--- | :--- |
| `String` | `std::string` or `android::String16` | Handle UTF-16 usually used in Android IPC. |
| `Bundle` | `android::os::Bundle` | Native counterpart exists. |
| `Parcelable` | `android::Parcelable` | Native implementation of `writeToParcel`/`readFromParcel`. |
| `Builder` | Builder Pattern / Struct | Inner class builder or separate factory. |

## Test Cases & Validation
1.  **Builder Construction**:
    *   Set all fields.
    *   Verify getters return set values.
2.  **Parceling**:
    *   Write object to parcel.
    *   Read back.
    *   Verify equality.

## Implementation Risks
*   **Bundle Serialization**: Ensure the native Bundle implementation handles the specific types used in constraints (String, Boolean) correctly matching Java's serialization.

## Questions for C++ Team
*   Does the C++ side need to generate `requestId` if it's empty?
