# KeyCharacterMap - Reverse Engineering Documentation

## Executive Summary
`KeyCharacterMap` describes the character mappings for a keyboard device. It translates raw hardware key codes into Unicode characters based on the device's specific layout and the current modifier state (Shift, Alt, etc.). It also handles "dead keys" for accent combination (e.g., `^` followed by `e` becomes `ê`).

## Architecture Overview
*   **Role**: Key-to-Character translation engine.
*   **JNI Centric**: Acts as a wrapper around a native C++ `KeyCharacterMap`.
*   **Types**: Defines keyboard categories: `NUMERIC`, `PREDICTIVE`, `ALPHA`, `FULL`, and `SPECIAL_FUNCTION`.

## Detailed Functionality

### 1. Character Retrieval
*   **`get(keyCode, metaState)`**: Returns the Unicode character or a combining accent bitmask.
*   **`getDeadChar(accent, c)`**: Combines a dead key with a character to produce an accented glyph using Unicode normalization (NFC).

### 2. Fallback Actions
*   **`getFallbackAction()`**: Determines what to do if an app doesn't handle a key (e.g., mapping a specialized media key to a standard one).

### 3. Events Generation
*   **`getEvents(char[])`**: Synthesizes a sequence of `KeyEvent` objects that would produce the given string. Useful for testing and automation.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Wrap `android::KeyCharacterMap`.
*   **Unicode Support**: Rely on ICU (International Components for Unicode) for normalization logic in `getDeadChar`.
*   **Overlay Support**: C++ implementation must support applying KCM overlays via `nativeApplyOverlay`.

## Implementation Risks
*   **Dead Key Recursion**: The accent combination logic must be carefully implemented to prevent infinite loops with malformed character maps.
*   **Locale Sync**: The active map should be updated if the user changes the system's input language.
