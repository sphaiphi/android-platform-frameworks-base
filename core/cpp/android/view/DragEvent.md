# DragEvent - Reverse Engineering Documentation

## Executive Summary
`DragEvent` is a Parcelable object representing a drag-and-drop interaction. It carries the data being dragged (`ClipData`), the state of the drag (entered, location, drop), and coordinates. It is used to notify views about drag operations occurring above them.

## Data Model

### 1. Actions
*   **`ACTION_DRAG_STARTED`**: Signals the start of a drag. Views return true to indicate they can accept drops.
*   **`ACTION_DRAG_ENTERED` / `ACTION_DRAG_EXITED`**: Signals the drag shadow entering/leaving a view's bounds.
*   **`ACTION_DRAG_LOCATION`**: Provides updates as the user moves the drag shadow over a view.
*   **`ACTION_DROP`**: Signals that the user has released the drag shadow over a valid target.
*   **`ACTION_DRAG_ENDED`**: Final event signaling the end of the global drag session.

### 2. Payload
*   **`mClipData`**: The data being transferred (only available in `ACTION_DROP` for security).
*   **`mClipDescription`**: Metadata about the data (available in all events except `ENDED`).
*   **`mLocalState`**: Arbitrary object passed by the source view (only available within the same process).

## Detailed Functionality
*   **Pooling**: Uses an `obtain()` / `recycle()` mechanism to minimize garbage collection overhead for high-frequency `LOCATION` events.
*   **Surface Control**: In some cases, contains a `mDragSurface` representing the visual shadow being dragged.

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap a native `DragEvent` structure.
*   **Parceling**: Ensure fields (`action`, `x`, `y`, `ClipData`) are marshalled in the order defined in the Java `writeToParcel`.

## Implementation Risks
*   **Security**: `ClipData` must be null-checked and only exposed during the `DROP` action to prevent data sniffing by non-target views.
*   **Coordinate Space**: The `x` and `y` coordinates are relative to the receiving view's coordinate system.
