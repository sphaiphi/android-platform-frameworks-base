# InsetsFlags - Reverse Engineering Documentation

## Executive Summary
`InsetsFlags` is a simple data container used to transmit the requested appearance and behavior of system bars from a client application to the `WindowManagerService`.

## Data Model
*   **`appearance`**: `int` - A bitmask of flags like `APPEARANCE_LIGHT_STATUS_BARS` or `APPEARANCE_OPAQUE_NAVIGATION_BARS`.
*   **`behavior`**: `int` - Defines how bars react to gestures (e.g., `BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE`).

## Detailed Functionality
*   **Metadata**: Annotated with `@ViewDebug.ExportedProperty` for use in hierarchy viewers and dumpsys.

## Java-to-C++ Translation Guide
*   **Structure**: Map to a C++ `struct` with two integer members.
*   **Parcelling**: Marshalling must match the order in `WindowManager.LayoutParams`.

## Implementation Risks
*   **Behavior Consistency**: Ensure the `BEHAVIOR_DEFAULT` value matches the system standard.
