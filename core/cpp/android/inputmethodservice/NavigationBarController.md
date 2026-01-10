# NavigationBarController - Reverse Engineering Documentation

## Executive Summary
`NavigationBarController` manages the logic for the IME navigation bar (which replaces the system navigation bar in Gestural Navigation mode when the IME is shown). It handles window creation, view inflation, and integration with `InputMethodService` insets.

## Architecture Overview
*   **Pattern**: Pimpl (Pointer to Implementation) via `Callback` interface.
*   **Impl**: Real implementation `Impl` vs `NOOP` (based on `canImeRenderGesturalNavButtons`).

## Detailed Functionality

### `Impl` Class
*   **Frame Installation**:
    *   Injects `NavigationBarFrame` into the `SoftInputWindow`'s decor view.
    *   Inflates `input_method_navigation_bar` layout.
*   **Insets**: `updateInsets`, `updateTouchableInsets`. Ensures the nav bar area is accounted for in the IME's reported insets so it's touchable and visible.
*   **Appearance**: Handles light/dark mode (`onSystemBarAppearanceChanged`) and background color.
*   **Buttons**: `prepareNavButtons`. Sets up Back and IME Switcher listeners.

## Data Model
*   `mNavigationBarFrame`: The root view of the nav bar.
*   `mService`: Reference to IMS.

## Java-to-C++ Translation Guide
*   **Window Injection**: Modifying the DecorView of a Dialog/Window from inside a controller. Requires access to the View hierarchy.
