# TextViewOnReceiveContentListener - Reverse Engineering Documentation

## Executive Summary
`TextViewOnReceiveContentListener` is the default implementation for `View#onReceiveContent` for `TextView`. It handles the insertion of content (text, styled text, HTML) from sources like the clipboard or drag-and-drop.

## Architecture Overview
*   **Implements**: `OnReceiveContentListener`.
*   **Role**: Content Insertion Handler.

## Detailed Functionality
*   **`onReceiveContent`**:
    *   Ignores `SOURCE_INPUT_METHOD` (IME handles this directly usually).
    *   Handles `SOURCE_AUTOFILL` specifically.
    *   For other sources (Clipboard, Drag/Drop):
        *   Iterates through `ClipData`.
        *   Coerces items to text.
        *   Inserts/Replaces selection in the editable text.
*   **Autofill Fallback**: Provides fallback MIME types for autofill if the app hasn't specified them.

## Java-to-C++ Translation Guide
*   **Clipboard/Drag**: Logic for handling rich content insertion.
*   **Selection**: Replacing current selection with inserted content.

## Implementation Risks
*   **Rich Text**: Handling spans and styles from the clipboard.
