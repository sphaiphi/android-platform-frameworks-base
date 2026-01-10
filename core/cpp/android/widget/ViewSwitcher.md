# ViewSwitcher - Reverse Engineering Documentation

## Executive Summary
`ViewSwitcher` is a `ViewAnimator` restricted to exactly two child views. It uses a `ViewFactory` to create them if needed.

## Architecture Overview
*   **Inheritance**: `ViewAnimator` -> `ViewSwitcher`.
*   **Role**: Toggle between two views (e.g., Loading vs Content).

## Detailed Functionality
*   **`getNextView`**: Returns the view that is *not* currently displayed.
*   **Factory**: `setFactory` allows dynamic creation of the two views.

## Java-to-C++ Translation Guide
*   **Simplification**: Just a ViewAnimator with a check for `getChildCount() <= 2`.

## Implementation Risks
*   None.
