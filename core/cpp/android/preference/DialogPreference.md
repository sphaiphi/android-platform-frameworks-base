# DialogPreference - Reverse Engineering Documentation

## Executive Summary
`DialogPreference` is an abstract base class for preferences that show a dialog when clicked (e.g., `EditTextPreference`, `ListPreference`). It handles the dialog creation, display, and lifecycle.

**Note:** This class is deprecated.

## Architecture Overview
- **Inheritance**: `DialogPreference` -> `Preference`.
- **Pattern**: Template Method (for dialog creation and binding).
- **Components**: Uses `AlertDialog.Builder` to construct the dialog.

## Detailed Functionality
1.  **Dialog Configuration**: Manages title, message, icon, layout, and positive/negative button text via XML attributes or setters.
2.  **Display**: On click, it builds and shows an `AlertDialog`.
3.  **Content**: Can inflate a custom layout (`setDialogLayoutResource`) into the dialog.
4.  **Lifecycle**: Persists dialog state (is showing, bundle) across configuration changes.

## Data Model
- **Attributes**: `dialogTitle`, `dialogMessage`, `dialogIcon`, `positiveButtonText`, `negativeButtonText`, `dialogLayout`.

## API Reference
- `setDialogTitle(...)`, `getDialogTitle()`
- `setDialogMessage(...)`, `getDialogMessage()`
- `setDialogIcon(...)`, `getDialogIcon()`
- `setPositiveButtonText(...)`, `setNegativeButtonText(...)`
- `setDialogLayoutResource(int)`
- `onClick()`: Shows the dialog.
- `onDialogClosed(boolean)`: Abstract-like hook for subclasses to handle result.

## Java-to-C++ Translation Guide
- **Dialogs**: C++ UI frameworks (if any) need a dialog equivalent.
- **State Saving**: The `SavedState` inner class logic (saving `isDialogShowing` and `dialogBundle`) is crucial for robustness.

## Implementation Risks
-   **Window Leaks**: The class handles `onActivityDestroy` to dismiss the dialog, preventing window leaks. This must be replicated.
