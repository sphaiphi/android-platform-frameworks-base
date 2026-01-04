# KeyboardShortcutInfo - Reverse Engineering Documentation

## Executive Summary
`KeyboardShortcutInfo` contains the details of a single keyboard shortcut. It maps a human-readable label to a combination of a base key (either a key code or a character) and a set of modifier keys (Ctrl, Alt, Meta, etc.).

## Data Model
*   **`mLabel`**: The descriptive name of the action (e.g., "Copy").
*   **`mKeycode`**: The hardware key code (if using a physical key).
*   **`mBaseCharacter`**: The literal character (if using character-based mapping).
*   **`mModifiers`**: A bitmask of required metakeys (e.g., `META_CTRL_ON`).

## Detailed Functionality
*   **Validation**: Ensures the key code is within the valid range.
*   **Icon Support**: (Internal) Can optionally include an `Icon` for the shortcut UI.

## Java-to-C++ Translation Guide
*   **Constants**: Use the standard `KeyEvent.META_*` bitmasks for modifiers.
*   **Parcelling**: Serialize the label, icon, character, keycode, and modifiers in that order.

## Implementation Risks
*   **Metakey Ambiguity**: Some shortcuts may be triggered by multiple modifier combinations (e.g., Left-Ctrl vs. Right-Ctrl). The system must resolve these consistently.
