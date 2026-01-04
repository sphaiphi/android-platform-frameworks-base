# HapticFeedbackConstants - Reverse Engineering Documentation

## Executive Summary
`HapticFeedbackConstants` defines a set of integer constants representing different tactile vibration effects. These constants are used with `View.performHapticFeedback()` to provide physical feedback for user interactions like key presses, long presses, and gestures.

## Data Model

### Interaction Effects
*   **`LONG_PRESS`**, **`VIRTUAL_KEY`**, **`KEYBOARD_TAP`**: Standard UI responses.
*   **`CONFIRM`** / **`REJECT`**: Feedback for success or failure.
*   **`SCROLL_TICK`** / **`SCROLL_LIMIT`**: Textures for scrolling interactions.
*   **`SEGMENT_TICK`**: Soft clicks for sliders or list items.

### Flags
*   **`FLAG_IGNORE_VIEW_SETTING`**: Forces the haptic even if the view has it disabled.
*   **`FLAG_IGNORE_GLOBAL_SETTING`**: (Deprecated) Forces haptic even if system-wide vibration is off.

## Java-to-C++ Translation Guide
*   **Enum Mapping**: Map these constants to a C++ `enum class`.
*   **Constants**: Ensure bit-for-bit parity with the Java integers for cross-process compatibility (e.g., in Binder calls).

## Implementation Risks
*   **Consistency**: Different hardware vendors may map these constants to different physical vibration patterns. The framework should strive for a uniform "feel" across devices.
