# TaskConstants - Reverse Engineering Documentation

## Executive Summary
`TaskConstants` defines Z-order layer values for children of a Task Surface. It allows organizing different types of content (Letterbox background, Windows, Overlays) within the task's surface hierarchy.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` (Constants)
*   **Role**: Constant definitions.

## Constants (TaskChildLayer)
*   `TASK_CHILD_LAYER_REGION_SIZE` (10000)
*   `TASK_CHILD_LAYER_TASK_BACKGROUND` (-30000)
*   `TASK_CHILD_LAYER_LETTERBOX_BACKGROUND` (-20000)
*   `TASK_CHILD_LAYER_COMPAT_UI` (10000)
*   `TASK_CHILD_LAYER_SETTINGS_DIALOG` (20000)
*   `TASK_CHILD_LAYER_WINDOW_DECORATIONS` (30000)
*   `TASK_CHILD_LAYER_RECENTS_ANIMATION_PIP_OVERLAY` (40000)
*   `TASK_CHILD_LAYER_TASK_OVERLAY` (50000)
*   `TASK_CHILD_LAYER_RESIZE_VEIL` (60000)
*   `TASK_CHILD_LAYER_FLOATING_MENU` (70000)

## Java-to-C++ Translation Guide
*   **Enum**: `enum TaskChildLayer : int32_t { ... }`.

## Implementation Risks
*   None.
