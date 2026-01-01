# ExtractEditText - Reverse Engineering Documentation

## Executive Summary
`ExtractEditText` is a specialized `EditText` used in the fullscreen extracted text view. It acts as a proxy for the actual text field in the target application. It handles text changes, selection changes, and context menu actions by forwarding them to the `InputMethodService`. It also masks internal changes (updates coming *from* the application) to prevent feedback loops.

## Architecture Overview
*   **Inheritance**: `EditText` -> `ExtractEditText`.
*   **Owner**: Owned by `InputMethodService` (`mIME`).

## Detailed Functionality

### Change Tracking (`mSettingExtractedText`)
*   **Purpose**: Distinguish between user edits (in the IME) and updates pushed from the application.
*   **Mechanism**:
    *   `setExtractedText`: Increments `mSettingExtractedText` before super call, decrements after.
    *   `onSelectionChanged`: Only notifies IME if `mSettingExtractedText == 0`.

### IME Interaction
*   **Event Forwarding**:
    *   `performClick` -> `mIME.onExtractedTextClicked`.
    *   `onTextContextMenuItem` -> `mIME.onExtractTextContextMenuItem`.
    *   `onSelectionChanged` -> `mIME.onExtractedSelectionChanged`.
    *   `viewClicked` -> `mIME.onViewClicked`.
    *   `deleteText_internal`, `replaceText_internal`, `setSpan_internal`, `setCursorPosition_internal` -> Forward to `mIME.onExtracted...`.

### Focus Faking
*   **Overrides**: `hasWindowFocus`, `isFocused`, `hasFocus`.
*   **Behavior**: Always returns `this.isEnabled()`.
*   **Reason**: To ensure the cursor and highlights are visible even if the system doesn't think this view has the "real" focus (since focus is complicated in IME windows).

### Attributes
*   `isInputMethodTarget`: Always returns `true`.

## Data Model
*   `mIME`: Reference to the `InputMethodService`.
*   `mSettingExtractedText`: Counter/Flag for suppressing callbacks during external updates.

## Java-to-C++ Translation Guide
*   **View System**: Requires a TextView/EditText equivalent in the C++ UI framework.
*   **Event Interception**: Needs mechanism to intercept text changes/selection before they are committed or just after, to forward to the Logic layer (`InputMethodService`).
*   **Ref Counting**: The `mSettingExtractedText` pattern is a common re-entrancy guard.

## Implementation Risks
*   **Infinite Loops**: Failure to correctly implement the `mSettingExtractedText` guard can lead to infinite loops where an update from the app triggers an update to the app, which triggers an update back...
