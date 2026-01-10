# JsDialogHelper - Reverse Engineering Documentation

## Executive Summary
`JsDialogHelper` helps create and show standard Android `AlertDialog`s for JavaScript `alert()`, `confirm()`, `prompt()`, and `onbeforeunload` events.

## Architecture Overview
*   **Dialog Types**: ALERT, CONFIRM, PROMPT, UNLOAD.
*   **Interaction**: Uses `JsPromptResult` or `JsResult` to report user action back to the web engine.

## Detailed Functionality
*   **`showDialog(Context)`**: Builds and shows the `AlertDialog`.
    *   Handles "Prompt" by inflating a view with an `EditText`.
    *   Handles titles (page URL vs default).
*   **`invokeCallback`**: Helper to dispatch to `WebChromeClient` methods.

## Java-to-C++ Translation Guide
*   **UI Helper**: This is purely a Java UI helper. The C++ engine calls up to `WebChromeClient`, which might use this helper.
