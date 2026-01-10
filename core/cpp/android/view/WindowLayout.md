# WindowLayout - Reverse Engineering Documentation

## Executive Summary
`WindowLayout` is a utility class responsible for the geometric calculation of window frames. it implements the logic for positioning a window based on its requested size, gravity, display cutouts, and system insets. it is used by `ViewRootImpl` to determine exactly where a window should sit on the screen.

## Architecture Overview
*   **Role**: Window geometry calculator.
*   **Logic**: Implements the standard Android "Gravity" and "Cutout" avoidance rules.

## Detailed Functionality

### 1. Frame Calculation (`computeFrames`)
*   Determines the `displayFrame`, `parentFrame`, and the final `frame`.
*   **Insets**: Accounts for `fitInsetsTypes` and `fitInsetsSides`.
*   **Cutouts**: Implements logic for `LAYOUT_IN_DISPLAY_CUTOUT_MODE_ALWAYS` vs `DEFAULT`.

### 2. Coordinate Mapping
*   Translates "Requested Width/Height" into physical pixel dimensions, accounting for `MATCH_PARENT`, `WRAP_CONTENT`, and `FLAG_SCALED`.

## Java-to-C++ Translation Guide
*   **Math**: Relies heavily on `android::Rect` intersection and union logic.
*   **Patterns**: Move the arithmetic logic to a pure C++ utility to share it between the system process and the application process.

## Implementation Risks
*   **Inconsistency**: The layout logic in `WindowLayout` MUST perfectly match the logic used by `WindowManagerService` on the server side to avoid "flickering" during relayouts.
*   **Recursive Dependencies**: Layout calculations can depend on the current state of insets, which are themselves updated during layout.
