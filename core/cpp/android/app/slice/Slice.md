# Slice - Reverse Engineering Documentation

## Executive Summary
The `Slice` class represents a piece of app content and actions that can be surfaced outside of the app (e.g., in the system UI or other apps). It is structured as a tree of `SliceItem` objects. It is `Parcelable` and serves as the primary data transport container for the Slice framework.

## Architecture Overview
*   **Package**: `android.app.slice`
*   **Type**: `final class`, implements `Parcelable`
*   **Relationships**:
    *   Contains an array of `SliceItem` (children).
    *   Has a `SliceSpec` defining its type/version.
    *   Identified by a `Uri`.
    *   Used by `SliceManager` and `SliceProvider`.

## Detailed Functionality

### Core Data Structure
The `Slice` is essentially a container for:
1.  **Uri**: The unique identifier for this slice.
2.  **SliceSpec**: The version/schema definition.
3.  **Items**: An ordered list of `SliceItem` objects representing the content tree.
4.  **Hints**: A list of string keywords describing the slice's semantic meaning (e.g., "list", "large", "error").

### Builder Pattern (`Slice.Builder`)
**Purpose**: Constructs `Slice` objects.
**Algorithm**:
1.  Initialized with a `Uri` and `SliceSpec`.
2.  Allows adding children via methods like `addAction`, `addText`, `addIcon`, `addInt`, `addSubSlice`.
3.  Accumulates hints.
4.  `build()` assembles the final `Slice` object.
**Java-Specific Notes**:
*   The Builder creates child `SliceItem`s immediately and stores them in an `ArrayList`.
*   `addSubSlice` constructor generates a synthetic Uri if not provided: `parentUri + "/_gen" + index`.

### Parceling Logic
**Purpose**: Serialization for IPC.
**Algorithm**:
1.  Writes Hints (String array).
2.  Writes Items (`SliceItem` array) using `writeTypedArray`.
3.  Writes Uri.
4.  Writes Spec.
**C++ Implementation Guidance**: Ensure strict order matching `writeToParcel`.

## Data Model

### `Slice`
| Field | Type | Description |
| :--- | :--- | :--- |
| `mItems` | `SliceItem[]` | The children of this slice node. |
| `mHints` | `String[]` | semantic tags (e.g., `HINT_TITLE`, `HINT_LIST`). |
| `mSpec` | `SliceSpec` | The schema version/type. |
| `mUri` | `Uri` | The content URI. |

### Constants (Hints)
Strings defined as constants (e.g., `HINT_TITLE = "title"`, `HINT_LIST = "list"`). C++ should define these as `constexpr char*` or `std::string` constants.

## API Reference

### `getSpec()`
*   **Returns**: `SliceSpec` or `null`.

### `getUri()`
*   **Returns**: `Uri`.

### `getItems()`
*   **Returns**: `List<SliceItem>` (Immutable wrapper around `mItems` in Java).

### `getHints()`
*   **Returns**: `List<String>`.

### `hasHint(String hint)`
*   **Returns**: `true` if `mHints` contains the given string.

### `isCallerNeeded()`
*   **Returns**: `true` if `HINT_CALLER_NEEDED` is present. Used to determine if the `SliceProvider` needs to know the calling package.

## Java-to-C++ Translation Guide

| Java Feature | C++ Equivalent | Notes |
| :--- | :--- | :--- |
| `Parcelable` | `Parcelable` interface | Use `android::os::Parcelable`. |
| `ArrayList<SliceItem>` | `std::vector<SliceItem>` | Used in Builder. |
| `String[]` | `std::vector<std::string>` | For hints. |
| `Uri` | `android::net::Uri` | Standard Android C++ Uri class. |
| `SliceSpec` | `SliceSpec` | Custom class (see `SliceSpec.md`). |
| `@StringDef` | `enum` or `constexpr` strings | Java annotations for string validation are compile-time only; use constants in C++. |

## Test Cases & Validation

### Case 1: Serialization
*   **Input**: Create a Slice with 1 Text item, 1 Hint "title", Uri "content://test".
*   **Action**: Write to Parcel, read from Parcel.
*   **Expected**: Reconstructed object equals input.

### Case 2: Builder Hierarchy
*   **Input**: Builder A adds SubSlice B.
*   **Expected**: Resulting Slice A contains a SliceItem of format `FORMAT_SLICE` containing Slice B.

## Implementation Risks
*   **Recursion**: Slices are tree structures. Serialization/Deserialization must handle depth correctly, though infinite recursion shouldn't happen by design (DAG).
*   **Nullability**: `mSpec` can be null. `mUri` cannot.

## Questions for C++ Team
*   Is there an existing C++ `Uri` implementation available in the target framework library?
