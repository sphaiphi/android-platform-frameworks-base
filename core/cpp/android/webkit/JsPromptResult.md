# JsPromptResult - Reverse Engineering Documentation

## Executive Summary
`JsPromptResult` extends `JsResult` to handle the result of a JavaScript `prompt()` dialog, which includes a string input from the user.

## Detailed Functionality
*   **`confirm(String result)`**: Confirms the prompt and provides the user's input string.
*   **`getStringResult()`**: Internal getter for the result.

## Java-to-C++ Translation Guide
*   **Callback Data**: Passes the string back to the script execution engine.
