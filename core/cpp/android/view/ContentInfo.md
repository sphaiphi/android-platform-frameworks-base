# ContentInfo - Reverse Engineering Documentation

## Executive Summary
`ContentInfo` is a container for data being inserted into a `View`, typically through operations like Paste, Drag & Drop, or IME insertion. It standardizes how content (text, images, URIs) and its associated metadata (source, flags, permissions) are passed to applications.

## Data Model

### Core Fields
*   **`mClip`**: `ClipData` - The actual content payload (can contain multiple items).
*   **`mSource`**: `int` - Where the content came from (`SOURCE_APP`, `SOURCE_CLIPBOARD`, `SOURCE_INPUT_METHOD`, etc.).
*   **`mFlags`**: `int` - Configuration for insertion (e.g., `FLAG_CONVERT_TO_PLAIN_TEXT`).
*   **`mLinkUri`**: `Uri` - Optional link associated with the content.

### Metadata
*   **`mInputContentInfo`**: Data specific to IME insertions.
*   **`mDragAndDropPermissions`**: Permissions that must be released after handling a drag-and-drop operation.

## Detailed Functionality

### 1. Partitioning
*   **`partition(Predicate<ClipData.Item>)`**: Splits the content into two `ContentInfo` objects based on a predicate. This allows a view to handle specific items (e.g., text) and delegate others (e.g., images) to the platform.

### 2. Permission Management
*   **`releasePermissions()`**: Proactively releases URI permissions granted by the system for the payload.

## Java-to-C++ Translation Guide
*   **Primary Type**: In C++, this can be implemented as a `struct` or `class` wrapping a native `ClipData` equivalent.
*   **Parceling**: Standard `Parcelable` implementation. Must handle nested objects like `Uri` and `Bundle`.

## Implementation Risks
*   **Permission Leaks**: Failing to call `releasePermissions()` for `SOURCE_DRAG_AND_DROP` or `SOURCE_INPUT_METHOD` can lead to permission leaks in the system.
*   **Asynchronous Handling**: If an app handles content on a background thread, it must retain a reference to the `ContentInfo` to keep the permissions alive.
