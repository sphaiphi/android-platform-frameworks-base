# CompoundButton - Reverse Engineering Documentation

## Executive Summary
`CompoundButton` is the abstract base class for buttons with two states (checked/unchecked), such as `CheckBox`, `RadioButton`, and `Switch`. It manages the checked state, the "button" drawable (the box/radio circle), and the OnCheckedChangeListener.

## Architecture Overview
*   **Inheritance**: `Button` -> `CompoundButton`.
*   **Implements**: `Checkable`.
*   **Key Components**:
    *   `mButtonDrawable`: The visual indicator (checkbox, radio circle, switch track/thumb).
    *   `mOnCheckedChangeListener`: Callback.

## Detailed Functionality

### 1. State Management
*   **`setChecked`**:
    *   Changes `mChecked`.
    *   Refreshes drawable state (`CHECKED_STATE_SET`).
    *   Notifies listener.
    *   Handles "broadcasting" prevention to avoid infinite loops if the listener changes the state back.

### 2. Drawing
*   **`onDraw`**:
    *   Draws the `mButtonDrawable`.
    *   Aligns it vertically (center or bottom).
    *   Calls `super.onDraw` (which draws the text).
*   **Padding**: Overrides `getCompoundPaddingLeft/Right` to include the width of the button drawable, ensuring the text doesn't overlap it.

### 3. Touch
*   **`performClick`**: Toggles the state (`toggle()`).

## Java-to-C++ Translation Guide
*   **Drawable State**: Essential to map the "checked" boolean to the visual state of the drawable.
*   **Layout**: The custom drawing and padding calculation logic is critical for correct text positioning.

## Implementation Risks
*   **Accessibility**: Needs to report checked state correctly.
