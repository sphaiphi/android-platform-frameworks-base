# NavigationBarView - Reverse Engineering Documentation

## Executive Summary
`NavigationBarView` is the high-level container logic for the IME navigation bar. It initializes the dispatchers, handles configuration changes (rotation, light/dark mode), and manages the `DeadZone`.

## Detailed Functionality
*   **Initialization**: Creates `ButtonDispatcher`s for Back and ImeSwitcher.
*   **Orientation**: Re-inflates or re-orients views on config change (`updateOrientationViews`, `reorient`).
*   **Icon Tinting**: Propagates dark intensity to dispatchers.
*   **Back Button Rotation**: Animates back button rotation (e.g., if it indicates "dismiss IME" vs "back").

## Java-to-C++ Translation Guide
*   **State Management**: Complex state logic for layout and appearance.
