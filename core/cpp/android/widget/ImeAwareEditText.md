# ImeAwareEditText - Reverse Engineering Documentation

## Executive Summary
`ImeAwareEditText` is a subclass of `EditText` used internally (e.g., in `SearchView` or `AutoCompleteTextView` dropdowns) to better coordinate with the Input Method Manager (IMM). It tracks whether the soft keyboard has been requested and retries showing it if the connection wasn't active yet.

## Architecture Overview
*   **Inheritance**: `EditText` -> `ImeAwareEditText`.
*   **Role**: IME State Manager.

## Detailed Functionality
*   **`scheduleShowSoftInput`**:
    *   If connected to IME: Calls `imm.showSoftInput`.
    *   If not connected: Sets `mHasPendingShowSoftInputRequest = true`.
*   **`onCreateInputConnection`**: If a pending request exists, posts a runnable to show the soft input after the connection is established.

## Java-to-C++ Translation Guide
*   **IME Integration**: Requires tight coupling with the platform's text input subsystem.

## Implementation Risks
*   **Race Conditions**: Showing the keyboard often fails if the view isn't focused or attached; this class mitigates that specific race.
