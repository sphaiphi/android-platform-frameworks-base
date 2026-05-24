# InputConnection - Reverse Engineering Documentation

## Executive Summary
The core interface for communication between an IME and an Editor (View).

## Key Methods
*   `getTextBefore/AfterCursor`
*   `getSelectedText`
*   `commitText`
*   `deleteSurroundingText`
*   `setComposingText/Region`
*   `sendKeyEvent`
*   `performEditorAction`
*   `performHandwritingGesture`

## Java-to-C++ Translation Guide
*   **Interface**: Core abstract interface.
