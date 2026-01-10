# SoundEffectConstants - Reverse Engineering Documentation

## Executive Summary
`SoundEffectConstants` defines a set of integer identifiers for standard system UI sound effects. These are used with `View.playSoundEffect()` to provide audible confirmation for navigation and clicks.

## Data Model

### standard Effects
*   **`CLICK`**: The standard selection sound.
*   **`NAVIGATION_LEFT/UP/RIGHT/DOWN`**: Sounds for directional movement.
*   **`NAVIGATION_REPEAT_*`**: Variations used during long-press repeating navigation.

## Detailed Functionality
*   **`getConstantForFocusDirection()`**: Maps a `View.FocusDirection` to the appropriate directional sound.
*   **`nextNavigationRepeatSoundEffectId()`**: Randomizes the sound used during repeated movement to avoid robotic or annoying repetition.

## Java-to-C++ Translation Guide
*   **Enum Parity**: C++ implementation must use the same integer values for consistent integration with the `AudioManager` native service.

## Implementation Risks
*   **Audio Latency**: Sound effects must be triggered with minimal latency to feel responsive to touch or key input.
