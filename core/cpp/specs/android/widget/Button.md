# Button - Reverse Engineering Documentation

## Executive Summary
`Button` is a `TextView` subclass that represents a push-button. In standard Android, it is mostly a styling wrapper (applying a specific background drawable and text style) with minimal additional logic beyond `TextView`.

## Architecture Overview
*   **Inheritance**: `TextView` -> `Button`.
*   **Role**: Interactive Clickable Widget.

## Detailed Functionality
*   **Pointer Icon**: On API 24+, changes the mouse pointer to a hand icon when hovering over the button (if clickable).
*   **Style**: Applies `com.android.internal.R.attr.buttonStyle`.

## Java-to-C++ Translation Guide
*   **Styling**: The core difference is the default style/theme. Ensure the C++ UI system applies the "button" appearance (9-patch background with pressed states).

## Implementation Risks
*   None.
