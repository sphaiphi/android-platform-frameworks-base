# PrivacyIndicatorBounds - Reverse Engineering Documentation

## Executive Summary
`PrivacyIndicatorBounds` manages the geometric area on the screen where the system privacy indicators (e.g., Camera or Microphone usage dots) are displayed. It maintains a set of rectangles for each possible screen rotation to ensure that applications can avoid placing critical UI elements under these indicators.

## Data Model
*   **`mStaticBounds`**: `Rect[]` - An array of 4 rectangles, one for each rotation (`ROTATION_0`, `90`, `180`, `270`).
*   **`mRotation`**: `int` - The current active rotation.

## Detailed Functionality
*   **`inset()`**: Adjusts the indicator bounds when the window frame is moved or resized.
*   **`getStaticPrivacyIndicatorBounds()`**: Returns the rectangle corresponding to the current rotation.
*   **`updateStaticBounds()`**: Allows SystemUI to push updated geometry to the system.

## Java-to-C++ Translation Guide
*   **Structure**: Map to a C++ `class` with a fixed-size array of `android::Rect`.
*   **Parcelling**: Marshalling must match the `DataClass` generated logic.

## Implementation Risks
*   **Screen Space**: Bounds are typically defined in screen coordinates; ensure correct transformation when translating to window or view coordinates.
