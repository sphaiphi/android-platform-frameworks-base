# ActivityWindowInfo - Reverse Engineering Documentation

## Executive Summary
`ActivityWindowInfo` is a data class used to store and transport specific window information associated with an Android Activity. It primarily captures details regarding whether an activity is embedded (e.g., in a TaskFragment) and the bounds of its container Task and TaskFragment. This information complements the standard `Configuration` object.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Data Transfer Object (DTO) for activity window state.
*   **Relationships**:
    *   Used by `ActivityThread` to track client-side records.
    *   Retrievable via static method `getActivityWindowInfo(Activity)`.

## Detailed Functionality

### Data Storage
**Purpose**: Holds the embedded state and layout bounds.
**State**:
*   `mIsEmbedded`: Boolean indicating if the activity is a TaskFragment not filling the leaf Task.
*   `mTaskBounds`: `Rect` defining the bounds of the leaf Task in display space.
*   `mTaskFragmentBounds`: `Rect` defining the bounds of the leaf TaskFragment in display space.

### `getActivityWindowInfo(@NonNull Activity activity)`
**Purpose**: Static utility to retrieve the info for a given activity instance.
**Algorithm**:
1.  Checks if activity is finishing; returns `null` if so.
2.  Retrieves the `ActivityClientRecord` from `ActivityThread` using the activity's token.
3.  Returns the `ActivityWindowInfo` from the record if found.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mIsEmbedded` | `boolean` | True if the activity is embedded (TaskFragment doesn't fill leaf Task). |
| `mTaskBounds` | `Rect` | Bounds of the leaf Task. Non-null. |
| `mTaskFragmentBounds` | `Rect` | Bounds of the leaf TaskFragment. Non-null. |

## API Reference

### Public Methods
*   `set(ActivityWindowInfo info)`: Copies data from another instance.
*   `set(boolean isEmbedded, Rect taskBounds, Rect taskFragmentBounds)`: Sets fields directly.
*   `isEmbedded()`: Returns the embedded state.
*   `getTaskBounds()`: Returns the task bounds.
*   `getTaskFragmentBounds()`: Returns the task fragment bounds.
*   `equals(Object o)`: Standard equality check.
*   `hashCode()`: Standard hash code generation.
*   `toString()`: String representation for debugging.

### Static Methods
*   `getActivityWindowInfo(Activity activity)`: Retrieves info for an activity.

## Java-to-C++ Translation Guide

### Data Types
*   `boolean` -> `bool`
*   `Rect` -> `android::graphics::Rect` (or equivalent C++ struct)
*   `Parcelable` -> `AParcelable` (Android NDK) or custom serialization compatible with Binder.

### Memory Management
*   Java uses `new Rect()` for members. C++ should likely use direct embedding or `std::unique_ptr` depending on the surrounding architecture, though direct member embedding (`android::Rect`) is preferred for small structs.

### Serialization
*   Implements `Parcelable`. C++ implementation must match the read/write order:
    1.  `writeBoolean(mIsEmbedded)`
    2.  `mTaskBounds.writeToParcel`
    3.  `mTaskFragmentBounds.writeToParcel`

## Test Cases & Validation
1.  **Serialization**: Write to parcel, read back, assert equals.
2.  **Embedding Check**: Verify `isEmbedded` returns correct boolean.
3.  **Bounds Access**: Verify `getTaskBounds` and `getTaskFragmentBounds` return expected Rects.
4.  **Static Retrieval**: Mock `ActivityThread` lookups to verify `getActivityWindowInfo` returns correct object or null.
