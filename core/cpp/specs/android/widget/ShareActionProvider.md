# ShareActionProvider - Reverse Engineering Documentation

## Executive Summary
`ShareActionProvider` is an `ActionProvider` used in menus to create a "Share" action. It displays a share icon that, when clicked, opens a share sheet. It also maintains a history of recently used share targets in a submenu.

## Architecture Overview
*   **Inheritance**: `ActionProvider` -> `ShareActionProvider`.
*   **Key Components**:
    *   `ActivityChooserModel`: Data model that tracks share history and available intents.
    *   `ActivityChooserView`: The UI widget displayed in the action bar.

## Detailed Functionality
*   **`onCreateActionView`**: Creates an `ActivityChooserView` and binds it to the data model.
*   **Submenu**: If added to the overflow menu, it populates a `SubMenu` with the most frequent share targets.
*   **Intent**: `setShareIntent` updates the model with the content to be shared.

## Java-to-C++ Translation Guide
*   **Menu System**: Requires a rich menu system supporting custom views (`ActionView`) and submenus.
*   **History**: The "most recently used" logic is delegated to `ActivityChooserModel`.

## Implementation Risks
*   **Persistence**: Reading/writing the share history XML file.
