# ActionMode - Reverse Engineering Documentation

## Executive Summary
`ActionMode` represents a contextual mode of the User Interface. It provides alternative interaction patterns (like a contextual toolbar) that replace parts of the normal UI (like the Action Bar) temporarily. Common use cases include text selection actions (Copy/Paste) and item selection in lists.

## Architecture Overview
*   **Role**: Contextual UI state manager.
*   **Lifecycle**: Managed via a `Callback` interface that handles creation, preparation, action clicks, and destruction.
*   **Types**:
    *   `TYPE_PRIMARY`: The standard contextual bar at the top of the screen.
    *   `TYPE_FLOATING`: A floating toolbar that appears near the selection/interaction point.

## Detailed Functionality

### 1. UI Configuration
*   **`setTitle()` / `setSubtitle()`**: Sets the labels shown in the mode.
*   **`setCustomView()`**: Allows an app to provide its own view instead of the standard title/subtitle labels.
*   **`setTag()`**: Associates arbitrary data with the mode for tracking.

### 2. Lifecycle Control
*   **`invalidate()`**: Forces the mode to refresh its menu items. Triggers `onPrepareActionMode`.
*   **`finish()`**: Ends the contextual mode and returns to the normal UI. Triggers `onDestroyActionMode`.

### 3. Positioning
*   **`Callback2.onGetContentRect()`**: Provides coordinates to ensure the `ActionMode` (especially floating ones) does not obscure relevant content.

## Java-to-C++ Translation Guide
*   **Pattern**: Implement as a state machine where the UI switches between "Normal" and "Contextual" states.
*   **Callbacks**: Use an abstract class or interface for `ActionMode::Callback`.
*   **Menu**: Integration with a native menu system is required to handle the `getMenu()` call.

## Implementation Risks
*   **Occlusion**: Floating action modes can cover up text or buttons if the content rect is not correctly calculated.
*   **Input Focus**: The contextual mode must decide if it steals focus from the underlying window (via `isUiFocusable`).
