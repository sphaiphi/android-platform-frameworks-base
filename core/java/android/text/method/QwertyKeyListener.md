# QwertyKeyListener - Reverse Engineering Documentation

## Executive Summary
Default key listener for QWERTY keyboards. Handles standard typing, auto-capitalization, and auto-text (correction).

## Logic
- **`onKeyDown`**:
    - Gets unicode char from event.
    - Handles `PICKER_DIALOG_INPUT` (accent picker).
    - Handles dead keys (accents).
    - Handles Auto-Cap (checks `TextKeyListener.shouldCap`).
    - Handles Auto-Text (replacements like "teh" -> "the").

## Java-to-C++ Translation Guide
- **Complex Logic**: Integrates many features (dead keys, capitalization, replacement). Requires access to `AutoText` dictionary and settings.
