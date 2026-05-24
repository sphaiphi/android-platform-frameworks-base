# TextSwitcher - Reverse Engineering Documentation

## Executive Summary
`TextSwitcher` is a specialized `ViewSwitcher` designed for animating text changes. When `setText` is called, it animates the old TextView out and the new TextView in.

## Architecture Overview
*   **Inheritance**: `ViewSwitcher` -> `TextSwitcher`.
*   **Constraint**: Children must be `TextView`s.

## Detailed Functionality
*   **`setText(CharSequence)`**:
    1.  Gets the *next* view (the hidden one).
    2.  Sets its text.
    3.  Calls `showNext()` (triggers animation).
*   **`setCurrentText(CharSequence)`**: Sets text on the *current* view without animation.

## Java-to-C++ Translation Guide
*   **Convenience**: Just a wrapper around `ViewSwitcher`.

## Implementation Risks
*   None.
