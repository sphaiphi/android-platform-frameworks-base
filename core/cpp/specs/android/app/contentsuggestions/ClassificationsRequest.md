# ClassificationsRequest - Reverse Engineering Documentation

## Executive Summary
`ClassificationsRequest` is a data carrier class used within the Content Suggestions API. Its primary purpose is to encapsulate a request sent to the `ContentSuggestionsManager` (and subsequently the system service) to classify a set of previously identified content selections. It bundles a list of `ContentSelection` objects with implementation-specific extra data.

## Architecture Overview
This class is a simple **Data Transfer Object (DTO)** implementing the `Parcelable` interface. It is designed to be immutable once built, utilizing a **Builder pattern** for construction. It sits in the `android.app.contentsuggestions` package and relies on `ContentSelection` objects as its primary payload.

## Detailed Functionality

### `ClassificationsRequest` (Core)
**Purpose**: Holds the data necessary to perform content classification.
**Components**:
1.  `mSelections`: A list of `ContentSelection` objects that need classification.
2.  `mExtras`: A `Bundle` containing arbitrary extra data required by the underlying classification service.

### `Builder`
**Purpose**: Facilitates the construction of `ClassificationsRequest` instances.
**Pattern**: Standard Builder pattern.
**Logic**:
1.  Takes the mandatory list of selections in the constructor.
2.  Allows optional setting of extras via `setExtras`.
3.  `build()` creates the immutable request object.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mSelections` | `List<ContentSelection>` | The list of content selections to classify. Cannot be null. |
| `mExtras` | `Bundle` | Optional extra data. If null during construction, accessors return an empty Bundle. |

## API Reference

### Public Methods
*   `getSelections()`: Returns `List<ContentSelection>`. Guaranteed non-null.
*   `getExtras()`: Returns `Bundle`. Guaranteed non-null (returns new empty Bundle if null internally).
*   `describeContents()`: Standard Parcelable implementation (returns 0).
*   `writeToParcel(Parcel dest, int flags)`: Serializes the object to a Parcel.

### Builder API
*   `Builder(List<ContentSelection> selections)`: Constructor requiring the mandatory selections list.
*   `setExtras(Bundle extras)`: Sets the extras bundle.
*   `build()`: Returns a new `ClassificationsRequest`.

## Java-to-C++ Translation Guide

### Serialization (Parcelable)
This class implements `Parcelable`. In C++, this typically maps to a class implementing `android::Parcelable` or providing `writeToParcel` and `readFromParcel` methods compatible with the Binder IPC mechanism.

*   **`writeToParcel`**:
    *   `mSelections`: Use `Parcel::writeTypedList` equivalent. Requires `ContentSelection` to be parcelable.
    *   `mExtras`: Use `Parcel::writeBundle`.

*   **`createFromParcel`**:
    *   `mSelections`: Use `Parcel::createTypedArrayList`.
    *   `mExtras`: Use `Parcel::readBundle`.

### Types
*   `java.util.List<ContentSelection>` -> `std::vector<android::app::contentsuggestions::ContentSelection>`
*   `android.os.Bundle` -> `android::os::Bundle` (C++ implementation of Bundle).

### Memory Management
*   The Java class is immutable. The C++ equivalent should likely also be immutable or use `const` accessors.
*   Ownership of the `Bundle` and `Vector` elements needs to be managed (likely value semantics or smart pointers depending on the framework conventions).

## Test Cases & Validation
1.  **Serialization**: Write a `ClassificationsRequest` to a Parcel, read it back, and verify `mSelections` and `mExtras` match.
2.  **Null Extras**: Create a request without setting extras. Verify `getExtras()` returns a non-null empty Bundle.
3.  **Content Integrity**: Verify the list of selections preserves order and content during IPC.

## Implementation Risks
*   **Parcel Compatibility**: Ensure the order of writing to the Parcel (Selections then Extras) matches exactly between Java and C++.
*   **Null Safety**: The C++ implementation must handle the potential for `mExtras` being null in the raw data, ensuring the accessor returns a valid empty object if needed to match Java behavior.
