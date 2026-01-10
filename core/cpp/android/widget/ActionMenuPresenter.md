# ActionMenuPresenter - Reverse Engineering Documentation

## Executive Summary
`ActionMenuPresenter` is a concrete implementation of `MenuPresenter` responsible for managing the display of action items in the `ActionBar` or `Toolbar`. It handles the creation of action buttons, the "overflow" menu (three dots), and submenus. It acts as the bridge between the semantic `MenuBuilder` (data) and the `ActionMenuView` (UI).

## Architecture Overview
*   **Inheritance**: `BaseMenuPresenter` -> `ActionMenuPresenter`.
*   **Implements**: `ActionProvider.SubUiVisibilityListener`.
*   **Role**: Controller for Action Menu UI.
*   **Key Components**:
    *   `mOverflowButton`: The view that triggers the overflow popup.
    *   `mOverflowPopup`: The popup window displaying non-action items.
    *   `mActionButtonGroups`: Tracks which items are currently shown as actions vs overflow.

## Detailed Functionality

### 1. Initialization (`initForMenu`)
*   Reads configuration (screen width, density) to determine how many action items can fit (`mMaxItems`) and the width limit (`mWidthLimit`).
*   Decides if an overflow button is needed (usually yes, unless it's a legacy device with a hardware menu key, though that logic is mostly obsolete).

### 2. Item Filtering (`flagActionItems`)
*   Crucial logic: Iterates through menu items to decide which ones get the `IS_ACTION` flag.
*   Prioritizes items with `SHOW_AS_ACTION_ALWAYS`.
*   Fills remaining slots with `SHOW_AS_ACTION_IF_ROOM` items until width or count limits are reached.
*   Handles "Action Groups" to keep related items together if possible.

### 3. View Binding (`bindItemView`)
*   Creates `ActionMenuItemView` for items shown as actions.
*   Sets up click listeners and interaction handlers.

### 4. Overflow Handling
*   `showOverflowMenu()` / `hideOverflowMenu()`: Manages the visibility of the popup list.
*   Uses `OverflowMenuButton` (an `ImageButton` subclass) as the anchor.

## Java-to-C++ Translation Guide
*   **Presenter Pattern**: Follow the MVP (Model-View-Presenter) pattern. This is the Presenter.
*   **Layout Logic**: The `flagActionItems` method contains complex business logic for measuring and prioritizing items. This should be ported carefully to ensure the same items appear as icons vs in the list.
*   **Popup Management**: Requires a C++ equivalent of `MenuPopupHelper` to handle the floating windows.

## Implementation Risks
*   **Configuration Changes**: Needs to react to orientation/screen size changes to re-calculate `mMaxItems`.
*   **Concurrency**: Posting runnables (`OpenOverflowRunnable`) is used to debounce or delay popup showing. C++ event loop integration is needed.
