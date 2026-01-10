# InputMethodSession - Reverse Engineering Documentation

## Executive Summary
Interface for the client-side session with the IME. Safe subset of `InputMethod` exposed to apps.

## Key Methods
*   `finishInput`.
*   `updateSelection`.
*   `updateCursorAnchorInfo`.
*   `dispatchKeyEvent`.

## Java-to-C++ Translation Guide
*   **Interface**: Session interface.
