# KeyButtonView - Reverse Engineering Documentation

## Executive Summary
`KeyButtonView` is the View implementation for a navigation button (Back, Home, Switcher). It handles touch events, triggers ripple effects, plays sounds/haptics, and converts touches into KeyEvents (e.g., `KEYCODE_BACK`).

## Detailed Functionality
*   **Input to Key**: `onTouchEvent` -> `sendEvent` (injects `KeyEvent`).
*   **Ripple**: Sets `KeyButtonRipple` as background.
*   **Long Click**: Supports repeated actions or long-press detection.

## Java-to-C++ Translation Guide
*   **Input Injection**: Injecting keys into the system requires privileged access or IPC to InputManager.
