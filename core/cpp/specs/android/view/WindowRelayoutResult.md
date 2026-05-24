# WindowRelayoutResult - Reverse Engineering Documentation

## Executive Summary
`WindowRelayoutResult` is a Parcelable data structure used as an "out" parameter for the `IWindowSession.relayout()` call. it bundles all the data returned by the `WindowManagerService` after a window relayout, including the new frames, surface control handles, and the current insets state.

## Data Model
*   **`frames`**: `ClientWindowFrames` - The new physical coordinates for the window.
*   **`mergedConfiguration`**: The latest global and override configurations.
*   **`surfaceControl`**: The updated native handle for the window's compositor layer.
*   **`insetsState`**: The current system-wide inset configuration.
*   **`activeControls`**: A collection of `InsetsSourceControl` objects for system bars.

## Java-to-C++ Translation Guide
*   **Structure**: Map to a C++ `struct WindowRelayoutResult`.
*   **Parceling**: Serialization MUST match the AIDL-generated code for `android.view.WindowRelayoutResult`.

## Implementation Risks
*   **Marshaling Overhead**: This is a large structure transmitted on every layout change; ensuring efficient Parcel handling is critical for UI performance.
