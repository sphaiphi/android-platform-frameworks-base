# SearchResponse - Reverse Engineering Documentation

## Executive Summary
`SearchResponse` is a data carrier class used to encapsulate the results returned from a cloud search operation. It allows returning a status code, a source identifier, and a list of `SearchResult` objects. It implements `Parcelable`.

## Architecture Overview
*   **Pattern**: Immutable Data Object / Builder Pattern.
*   **Role**: Response DTO (Data Transfer Object) for `CloudSearchManager`.
*   **Key Dependencies**: `SearchResult` (contained list item).

## Detailed Functionality

### Core Fields
*   **StatusCode**: Integer status (OK, Unknown, Timeout, No Internet).
*   **Source**: String identifier of the search provider.
*   **SearchResults**: A list of `SearchResult` objects.

### Constants (Status Codes)
*   `SEARCH_STATUS_UNKNOWN` (-1)
*   `SEARCH_STATUS_OK` (0)
*   `SEARCH_STATUS_TIME_OUT` (1)
*   `SEARCH_STATUS_NO_INTERNET` (2)

**Java-Specific Notes**:
*   **`@IntDef`**: Annotation for compile-time validation of status codes.
*   **`List<SearchResult>`**: Generic list.

**C++ Implementation Guidance**:
*   `StatusCode` can be an `enum` or `enum class`.
*   `List<SearchResult>` maps to `std::vector<SearchResult>`.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `statusCode` | `int` | Result status. |
| `source` | `String` | Provider package name/ID. |
| `searchResults` | `List<SearchResult>` | The actual results. |

## API Reference

### Getters
*   `getStatusCode()`: Returns int.
*   `getSource()`: Returns String.
*   `getSearchResults()`: Returns `List<SearchResult>`.

### Setters (via Builder)
*   `setStatusCode(int)`
*   `setSource(String)`
*   `setSearchResults(List<SearchResult>)`

## Java-to-C++ Translation Guide

| Java Feature | C++ Equivalent | Notes |
| :--- | :--- | :--- |
| `List<E>` | `std::vector<E>` | |
| `@IntDef` | `enum class` | |
| `Parcelable` | `android::Parcelable` | Serialization logic. |

## Test Cases & Validation
1.  **Empty Response**:
    *   Status: OK.
    *   Results: Empty list.
2.  **Error Response**:
    *   Status: TIME_OUT.
    *   Results: Ignored/Empty.
3.  **Populated Response**:
    *   Verify list contains expected `SearchResult` items.

## Implementation Risks
*   **Null Safety**: Java `List` can be null in some contexts, though API says `@NonNull`. C++ `std::vector` is never null, just empty. Ensure deserialization handles null lists by creating empty vectors.
