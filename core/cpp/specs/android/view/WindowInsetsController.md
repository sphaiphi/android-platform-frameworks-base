# WindowInsetsController - Reverse Engineering Documentation

## Executive Summary
`WindowInsetsController` is the public interface that allows applications to control the behavior and visibility of system bars (Status Bar, Navigation Bar) and the IME (Keyboard). It replaces the deprecated `SYSTEM_UI_FLAG_*` flags on `View`.

## Data Model

### 1. Appearance Flags
*   **`APPEARANCE_LIGHT_STATUS_BARS`**: Changes status bar icons to dark (for light backgrounds).
*   **`APPEARANCE_LIGHT_NAVIGATION_BARS`**: Changes nav bar icons to dark.

### 2. Behavior Flags
*   **`BEHAVIOR_DEFAULT`**: Bars appear on swipe.
*   **`BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE`**: Bars appear semi-transparently and auto-hide (Immersive Mode).

## Detailed Functionality
*   **`show(int types)`**: Request to show specific insets.
*   **`hide(int types)`**: Request to hide specific insets.
*   **`setSystemBarsAppearance()`**: Controls the visual style of the bars.
*   **`controlWindowInsetsAnimation()`**: Takes control of the animation for custom transitions.

## Java-to-C++ Translation Guide
*   **Interface**: Pure virtual base class in C++.
*   **Implementation**: `InsetsController` (which I documented separately) implements this interface.

## Implementation Risks
*   **Conflict**: If multiple windows (or the system) try to control the bars simultaneously, the "Top Focused Window" usually wins.
