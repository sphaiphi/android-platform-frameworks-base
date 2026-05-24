# BaseInputConnection - Reverse Engineering Documentation

## Executive Summary
Base implementation of the `InputConnection` interface. It provides default behavior for most methods, handling common tasks like batch edit nesting and composing text management. It is designed to be subclassed by views that want to implement custom text editing.

## Architecture
*   **Composing Text**: Uses a `ComposingText` span to mark the currently composing region in the `Editable`.
*   **Batch Editing**: Supports nested batch edits (though implementation is minimal here, subclasses typically hook into it).
*   **Fallback Mode**: Supports a "fallback" mode (initialized with `false` for full editors) where it mimics some behavior but might not have full control over the underlying text storage if not provided.

## Key Algorithms
*   **`setComposingText`**: Replaces the current composing region with new text and sets the cursor.
*   **`deleteSurroundingText`**: Deletes text around the cursor. Handles selection and composing regions.
*   **`sendKeyEvent`**: Delegates key events to the `InputMethodManager` to be dispatched to the target view.

## Java-to-C++ Translation Guide
*   **Spannable**: Relies heavily on `Spannable` interface for text manipulation (spans). C++ equivalent needs a rich text string class.
*   **InputMethodManager**: Interactions with IMM are frequent.
