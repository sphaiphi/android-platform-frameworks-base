# KeyEvent - Reverse Engineering Documentation

## Executive Summary
`KeyEvent` is a Parcelable object used to report hardware key and button events. Each key press is represented by a sequence of events (ACTION_DOWN, multiple ACTION_DOWNs for repeats, and ACTION_UP). It abstracts raw hardware scan codes into universal Android key codes (e.g., `KEYCODE_BACK`, `KEYCODE_ENTER`).

## Data Model

### Core Fields
*   **`mAction`**: `int` - `ACTION_DOWN` (0), `ACTION_UP` (1), or `ACTION_MULTIPLE` (2).
*   **`mKeyCode`**: `int` - The identifier for the key (e.g., `KEYCODE_VOLUME_UP`).
*   **`mRepeatCount`**: `int` - Number of times the key has repeated.
*   **`mMetaState`**: `int` - Bitmask of modifier keys (SHIFT, ALT, CTRL, META).
*   **`mEventTime`**: `long` - The time when the event occurred (SystemClock.uptimeMillis).
*   **`mDownTime`**: `long` - The time when the original key press started.
*   **`mScanCode`**: `int` - The raw hardware-specific code.

### Key Actions
*   `ACTION_DOWN`: Key was pressed.
*   `ACTION_UP`: Key was released.
*   `ACTION_MULTIPLE`: (Deprecated) A string of characters or multiple repeat events.

## Detailed Functionality

### 1. Flag Management
*   **`FLAG_CANCELED`**: Set if the key sequence was aborted.
*   **`FLAG_LONG_PRESS`**: Set by the framework if the key is held down longer than the long-press threshold.
*   **`FLAG_VIRTUAL_HARD_KEY`**: Indicates the key is a software-rendered button that behaves like a hard key.

### 2. Unicode Conversion
*   **`getUnicodeChar()`**: Uses the `KeyCharacterMap` associated with the device to map the key code and meta state to a UTF-8 character.

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap `android::KeyEvent`.
*   **Parceling**: Serialization must match `frameworks/native/libs/input/Input.cpp`.
*   **Enum Mapping**: Map all `KEYCODE_` constants to a C++ enum for type-safe handling in the input pipeline.

## Implementation Risks
*   **Event Consistency**: The system expects a strict DOWN -> [DOWN repeats] -> UP sequence. Dropping an event or receiving an out-of-order sequence can confuse state machines (like `GestureDetector` or `View` focus logic).
*   **IME Interop**: Most software keyboards (IMEs) do NOT generate `KeyEvent`s for text entry; they use the `InputConnection` API. `KeyEvent` is primarily for physical buttons and specialized keys.
