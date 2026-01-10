# ActionProvider - Reverse Engineering Documentation

## Executive Summary
`ActionProvider` is a component that provides rich menu interaction within a single `MenuItem`. It can generate its own "action view" for the Action Bar, handle default clicks, and dynamically populate submenus. This allows for complex UI components (like a `ShareActionProvider` or `SearchManager`) to be reusable and encapsulated.

## Architecture Overview
*   **Role**: Delegated UI and logic provider for menu items.
*   **Lifecycle**: Bound to a `MenuItem`. It receives callbacks when the item needs a view or when its submenu should be prepared.
*   **Listeners**: Notifies the system of visibility and sub-UI changes (e.g., when a popup is anchored).

## Detailed Functionality

### 1. View Creation
*   **`onCreateActionView(MenuItem)`**: The primary hook to return a `View` that will be displayed in the Action Bar.

### 2. Visibility and Interaction
*   **`overridesItemVisibility()`**: If true, the provider decides if the `MenuItem` should be shown based on `isVisible()`.
*   **`onPerformDefaultAction()`**: Handles the interaction when the item is in the overflow menu or doesn't have an action view.

### 3. Submenu Management
*   **`hasSubMenu()`**: Indicates if this provider manages a set of sub-options.
*   **`onPrepareSubMenu(SubMenu)`**: Called right before the submenu is shown to the user, allowing dynamic item population.

## Java-to-C++ Translation Guide
*   **Factory Pattern**: `onCreateActionView` is a factory method.
*   **Event Propagation**: Implement a listener pattern to propagate visibility changes back to the native menu presenter.

## Implementation Risks
*   **Leakage**: Since `ActionProvider` holds a `Context`, ensure it is cleared when the menu is destroyed.
*   **Compatibility**: Deprecated `onCreateActionView()` (no args) must still be supported for older implementations.
