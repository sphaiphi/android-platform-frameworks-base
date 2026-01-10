# SurfaceControlActivePicture - Reverse Engineering Documentation

## Executive Summary
`SurfaceControlActivePicture` is a metadata record describing a visible compositor layer that is currently using "Picture Processing" (hardware-level image quality enhancement). it identifies the layer, its owner, and the specific picture profile handle being applied.

## Data Model
*   **`mLayerId`**: `int` - The internal ID of the `SurfaceControl` layer.
*   **`mOwnerUid`**: `int` - The UID of the process that owns the layer.
*   **`mPictureProfileHandle`**: `PictureProfileHandle` - The descriptor for the active quality profile.

## Java-to-C++ Translation Guide
*   **Mapping**: Map to a native C++ `struct`.
*   **Parcelling**: Marshalling must match the native implementation in `frameworks/native/libs/gui/`.

## Implementation Risks
*   **Stale IDs**: Layer IDs can be recycled; the system must ensure this metadata is refreshed when layers are destroyed.
