# SelectionActionModeHelper - Reverse Engineering Documentation

## Executive Summary
`SelectionActionModeHelper` is a helper class that orchestrates the "Smart Selection" (TextClassifier) features for `TextView` and `Editor`. It handles the asynchronous classification of selected text, the display of the selection menu (floating toolbar), and the generation of smart actions (e.g., "Map", "Call").

## Architecture Overview
*   **Role**: Controller / Coordinator.
*   **Dependencies**: `Editor`, `TextView`, `TextClassifier` (System Service).
*   **Key Components**:
    *   `TextClassificationHelper`: Wraps `TextClassifier` calls.
    *   `SelectionTracker`: Logs metrics.
    *   `SmartSelectSprite`: (Optional) Animates the selection expansion.

## Detailed Functionality

### 1. Asynchronous Classification
*   **`startSelectionActionModeAsync`**:
    1.  Resets previous state.
    2.  Checks conditions (password, no-op classifier).
    3.  Starts a `TextClassificationAsyncTask` to query the system `TextClassifier`.
    4.  On callback (`startSelectionActionMode`), updates the selection indices (if "Smart Selection" expanded the range) and shows the toolbar.

### 2. Smart Selection Logic
*   **Selection Expansion**: If enabled, the `TextClassifier` suggests a better selection range (e.g., expanding a tap on "1600" to "1600 Amphitheatre Pkwy").
*   **Animation**: `SmartSelectSprite` draws a visual expansion animation from the original tap to the final bounds.

### 3. Selection Actions
*   Retrieves actions (Copy, Paste, specific App Actions) from the classification result and passes them to the `Editor` to populate the `ActionMode` menu.

## Java-to-C++ Translation Guide
*   **Async/Await**: The core flow is asynchronous. Use coroutines or callbacks.
*   **System Integration**: Relies heavily on the platform's TextClassifier service. If that's not available in the target C++ environment, this class is largely a no-op or falls back to basic clipboard operations.
*   **Geometry**: Rectangle merging logic (`mergeRectangleIntoList`) is used for the animation sprite.

## Implementation Risks
*   **Latency**: Text classification can be slow. The UI must remain responsive.
*   **Race Conditions**: Handling text changes or new selection events while a classification is in flight.
