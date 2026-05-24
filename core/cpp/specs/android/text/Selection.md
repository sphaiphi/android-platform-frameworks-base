# Selection - Reverse Engineering Documentation

## Executive Summary
Utility class for managing text selection and cursor positions. Selection is represented by `SELECTION_START` and `SELECTION_END` spans.

## Data Model
- **`SELECTION_START`**: Object/Span marker.
- **`SELECTION_END`**: Object/Span marker.
- **`SELECTION_MEMORY`**: Used to remember horizontal position during vertical navigation.

## API Reference
- **`getSelectionStart(CharSequence)`**
- **`getSelectionEnd(CharSequence)`**
- **`setSelection(Spannable, int start, int stop)`**: Updates span positions.
- **`moveUp`, `moveDown`, `moveLeft`, `moveRight`**: Logic for cursor movement respecting layout.

## Java-to-C++ Translation Guide
- **Spans**: Relies on the Span system.
- **Logic**: Navigation logic depends on `Layout` APIs (`getLineForOffset`, `getPrimaryHorizontal`).
