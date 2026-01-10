# InsetsFrameProvider - Reverse Engineering Documentation

## Executive Summary
`InsetsFrameProvider` is a descriptor used by a window to declare itself as a source of insets for other windows. It defines how the system should calculate the inset frame based on the window's own geometry.

## Data Model

### 1. Source Frame
*   **`SOURCE_DISPLAY`**: Uses the display boundaries.
*   **`SOURCE_FRAME`**: Uses the window's assigned frame.
*   **`SOURCE_ARBITRARY_RECTANGLE`**: Uses a specific custom `Rect`.

### 2. Modifications
*   **`mInsetsSize`**: A fixed size applied to one side of the source frame to create the inset (e.g., a 50px bottom bar).
*   **`mInsetsSizeOverrides`**: Allows providing different sizes for different window types.

## Detailed Functionality
*   **Identity**: `mId` is a unique integer combining the owner, index, and `InsetsType`.
*   **Flags**: `FLAG_ANIMATE_RESIZING`, `FLAG_FORCE_CONSUMING`.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Map to a C++ `class InsetsFrameProvider`.
*   **ID Logic**: Use `InsetsSource::createId` logic for ID generation.

## Implementation Risks
*   **Calculated Bounds**: If the `SOURCE_FRAME` is not yet available during layout, the system may report incorrect insets, leading to UI "jumping."
