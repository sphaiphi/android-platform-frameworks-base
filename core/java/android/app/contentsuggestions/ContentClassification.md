# ContentClassification - Reverse Engineering Documentation

## Executive Summary
`ContentClassification` represents the result of a classification operation initiated by a `ClassificationsRequest`. It encapsulates the classification outcome for a specific content selection, providing an ID and associated extra data.

## Architecture Overview
This is a **Data Transfer Object (DTO)** implementing `Parcelable`. It is a final class used to pass data back from the Content Suggestions service to the client. It is immutable.

## Detailed Functionality

### `ContentClassification`
**Purpose**: Stores the classification result.
**Components**:
1.  `mClassificationId`: A string ID representing the specific classification or the ID of the selection being classified (implementation specific).
2.  `mExtras`: A `Bundle` containing the detailed classification data (e.g., entity type, confidence score, actions).

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mClassificationId` | `String` | Implementation-specific ID. Cannot be null. |
| `mExtras` | `Bundle` | Classification data. Cannot be null. |

## API Reference

### Public Methods
*   `ContentClassification(String classificationId, Bundle extras)`: Constructor.
*   `getId()`: Returns the classification ID (`String`).
*   `getExtras()`: Returns the extras (`Bundle`).
*   `describeContents()`: Standard Parcelable implementation.
*   `writeToParcel(Parcel dest, int flags)`: Serializes to Parcel.

## Java-to-C++ Translation Guide

### Serialization
*   **`writeToParcel`**:
    *   `mClassificationId`: `Parcel::writeString`.
    *   `mExtras`: `Parcel::writeBundle`.
*   **`createFromParcel`**:
    *   `mClassificationId`: `Parcel::readString`.
    *   `mExtras`: `Parcel::readBundle`.

### Types
*   `String` -> `android::String16` or `std::string` (UTF-8/UTF-16 conversion handled by Parcel).
*   `Bundle` -> `android::os::Bundle`.

## Test Cases & Validation
1.  **Round-trip IPC**: Write to Parcel, read back, assert equality of ID and Bundle contents.
2.  **Null Checks**: The constructor enforces `@NonNull`. C++ should likely enforce this via reference parameters or assertions.

## Implementation Risks
*   **String Encoding**: Ensure string encoding (UTF-8 vs UTF-16) is consistent with the Parcel implementation in the framework.
