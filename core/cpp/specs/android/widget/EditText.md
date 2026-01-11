# EditText - Reverse Engineering Documentation

## Executive Summary
`EditText` is a thin wrapper around `TextView` that configures it to be editable by default. It is the standard text entry widget in Android.

## Architecture Overview
*   **Inheritance**: `TextView` -> `EditText`.
*   **Role**: Text Input.

## Detailed Functionality
*   **Defaults**: Sets `editable=true`, `focusable=true`, `focusableInTouchMode=true`.
*   **Selection**: Provides convenience methods (`selectAll`, `setSelection`, `extendSelection`) wrapping `Selection.setSelection`.
*   **MovementMethod**: Defaults to `ArrowKeyMovementMethod`.
*   **Styling Shortcuts**: Supports Ctrl+B (Bold), Ctrl+I (Italic), etc., if enabled.

## Java-to-C++ Translation Guide
*   **Inheritance**: Most logic is in `TextView` / `Editor`. `EditText` is primarily configuration.

## Implementation Risks
*   None.
