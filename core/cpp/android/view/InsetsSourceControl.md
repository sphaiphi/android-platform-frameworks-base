# InsetsSourceControl - Reverse Engineering Documentation

## Executive Summary
`InsetsSourceControl` is a Parcelable object that grants an application control over a specific `InsetsSource`. It contains a `SurfaceControl` leash that the application can use to animate the position, alpha, and cropping of the system bar or IME.

## Data Model
*   **`mId`**: The ID of the source being controlled.
*   **`mLeash`**: `SurfaceControl` - The handle used for native animations.
*   **`mSurfacePosition`**: `Point` - The initial position of the surface in screen coordinates.
*   **`mInsetsHint`**: `Insets` - The dimensions the source normally occupies.

## Detailed Functionality
*   **`release()`**: Frees the animation leash.
*   **`InsetsSourceControl.Array`**: A specialized container for passing multiple controls over Binder, ensuring sequential updates via a sequence number (`mSeq`).

## Java-to-C++ Translation Guide
*   **Primary Type**: Map to `android::view::InsetsSourceControl`.
*   **Parceling**: Serialization MUST match `frameworks/native/libs/gui/`.

## Implementation Risks
*   **Leash Invalidity**: Applications must check `getLeash().isValid()` before using it in a transaction.
*   **Sync**: Mismatched sequence numbers in `Array` will cause the client to drop updates from the server.
