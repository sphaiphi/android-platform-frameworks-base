# JsResult - Reverse Engineering Documentation

## Executive Summary
`JsResult` is an object passed to the application to handle the outcome of JavaScript dialogs (`alert`, `confirm`). It allows the app to signal whether the user accepted or cancelled the dialog.

## Detailed Functionality
*   **`confirm()`**: User clicked OK.
*   **`cancel()`**: User clicked Cancel.
*   **`wakeUp()`**: Internal method to notify the `ResultReceiver` (bridge to native code).

## Java-to-C++ Translation Guide
*   **Synchronization**: This often controls blocking the JS thread. The `confirm`/`cancel` call must signal a condition variable or callback to resume JS execution.
