# ContentSelection - Reverse Engineering Documentation

## Executive Summary
`ContentSelection` represents a suggested selection within a set of on-screen content. It is typically the result of a `SelectionsRequest`. It identifies a specific piece of content (text, image region, etc.) that the system has detected.

## Architecture Overview
This is a **Data Transfer Object (DTO)** implementing `Parcelable`. It is immutable and serves as the fundamental unit of "selected content" in this API.

## Detailed Functionality

### `ContentSelection`
**Purpose**: Encapsulates a content selection.
**Components**:
1.  `mSelectionId`: A unique ID for this selection.
2.  `mExtras`: A `Bundle` containing data representing the selection (e.g., text content, bounding box coordinates).

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mSelectionId` | `String` | Implementation-specific ID. Cannot be null. |
| `mExtras` | `Bundle` | Selection data. Cannot be null. |

## API Reference

### Public Methods
*   `ContentSelection(String selectionId, Bundle extras)`: Constructor.
*   `getId()`: Returns the selection ID.
*   `getExtras()`: Returns the extras.
*   `writeToParcel(Parcel dest, int flags)`: Serializes to Parcel.

## Java-to-C++ Translation Guide

### Serialization
*   **`writeToParcel`**:
    *   `mSelectionId`: `Parcel::writeString`.
    *   `mExtras`: `Parcel::writeBundle`.

### Types
*   `String` -> `android::String16` or `std::string`.
*   `Bundle` -> `android::os::Bundle`.

## Test Cases & Validation
1.  **Serialization**: Verify strict ordering of ID followed by Bundle in the Parcel.
2.  **Data Integrity**: Ensure the Bundle content is preserved exactly across IPC boundaries.

## Implementation Risks
*   **Bundle Complexity**: The `mExtras` Bundle might contain complex nested structures. The C++ Bundle implementation must support all types that might be placed here by the Java side.
