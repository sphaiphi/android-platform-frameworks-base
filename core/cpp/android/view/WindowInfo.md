# WindowInfo - Reverse Engineering Documentation

## Executive Summary
`WindowInfo` is a comprehensive internal data class used by the `WindowManagerService` to describe a window to other system components (primarily the Accessibility and Content Capture services). it contains identity, hierarchy, visibility, and geometric information.

## Data Model

### 1. Identity and Hierarchy
*   **`token`**: The `IWindow` binder.
*   **`parentToken`** / **`childTokens`**: Links to other windows in the hierarchy.
*   **`activityToken`**: Links the window to its host activity.

### 2. Geometry
*   **`regionInScreen`**: The physical area occupied by the window.
*   **`mTransformMatrix`**: The matrix used to map window coordinates to screen coordinates.
*   **`mMagnificationSpec`**: Any active accessibility zoom applied to the window.

### 3. State
*   **`focused`**: Whether the window has input focus.
*   **`inPictureInPicture`**: PIP status.

## Detailed Functionality
*   **Pooling**: Uses `obtain()` / `recycle()` to reduce allocation pressure during high-frequency system updates.

## Java-to-C++ Translation Guide
*   **Primary Type**: Map to `android::view::WindowInfo`.
*   **Parceling**: Parity with native `WindowInfo` marshalling is required.

## Implementation Risks
*   **Security**: This object contains sensitive internal tokens; it should never be exposed directly to non-privileged applications.
