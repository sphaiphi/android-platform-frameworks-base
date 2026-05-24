# Editor - Reverse Engineering Documentation

## Executive Summary
`Editor` is a helper class used exclusively by `TextView` to handle all functionality related to **editing**, **selection**, and **interaction** (text handles, cursor, action modes, IME integration). It offloads a massive amount of complexity from the `TextView` class.

## Architecture Overview
*   **Role**: Controller / Helper for TextView.
*   **Relationship**: 1:1 with `TextView`. Created lazily when the TextView becomes editable or selectable.

## Detailed Functionality

### 1. Cursor & Selection
*   **Controllers**:
    *   `InsertionPointCursorController`: Manages the single cursor handle.
    *   `SelectionModifierCursorController`: Manages the two selection start/end handles.
*   **Handles**: Draws the teardrop handles (`Drawable`) on the screen via `PopupWindow`s (or overlaid views). Handles touch events to drag them.
*   **Cursor Drawing**: Draws the blinking cursor in `onDraw`.

### 2. Input Method (IME) Integration
*   **InputConnection**: Bridges the `TextView` content to the keyboard.
*   **Batch Edits**: Handles `beginBatchEdit` / `endBatchEdit` to group IME operations.
*   **Extraction**: Manages "Extracted Mode" (full-screen editing in landscape).

### 3. Action Modes
*   **Selection Mode**: Shows the floating toolbar (Copy, Paste, Select All) when text is selected.
*   **Insertion Mode**: Shows handles and potentially a paste/replace menu when cursor is placed.

### 4. Undo/Redo
*   **`UndoManager`**: Manages the undo stack.
*   **`UndoInputFilter`**: Listens to text changes and pushes operations to the manager.

### 5. Magnifier
*   Shows a magnifying glass popup when the user drags the cursor/handles to allow precise positioning.

## Java-to-C++ Translation Guide
*   **Complexity**: This is one of the heaviest classes.
*   **Popup Management**: The handles are often implemented as system popups. In a native engine, they might just be overlay nodes in the scene graph.
*   **IME**: Requires deep integration with the OS text input subsystem.

## Implementation Risks
*   **Sync**: Keeping the visual handles, the logical selection indices, and the IME state in sync is notoriously difficult.
*   **Touch Handling**: Complex state machine for distinguishing taps, double taps, long presses, and drags (`EditorTouchState`).
