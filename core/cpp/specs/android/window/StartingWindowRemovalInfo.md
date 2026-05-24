# StartingWindowRemovalInfo - Reverse Engineering Documentation

## Executive Summary
`StartingWindowRemovalInfo` informs the `TaskOrganizer` how to remove a starting window. It specifies whether to play a reveal animation, whether to defer removal, and provides the necessary leash/frame for animations.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: DTO.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `taskId` | `int` | Task ID. |
| `windowAnimationLeash` | `SurfaceControl` | Leash for animation. |
| `mainFrame` | `Rect` | Frame of the main window. |
| `playRevealAnimation` | `boolean` | If true, play reveal. |
| `deferRemoveMode` | `int` | Mode (Normal, Rotation, None). |
| `roundedCornerRadius` | `float` | Radius for animation masking. |
| `windowlessSurface` | `boolean` | If true, the starting window was windowless. |
| `removeImmediately` | `boolean` | Force remove. |

## Java-to-C++ Translation Guide

### Data Types
*   `SurfaceControl` -> `android::view::SurfaceControl` or similar handle.

### Parceling
*   Standard write order.

## Implementation Risks
*   **Leash Lifecycle**: `windowAnimationLeash` ownership must be handled carefully.
