# DialogFragment - Reverse Engineering Documentation

## Executive Summary
`DialogFragment` is a Fragment that manages a Dialog instance. It bridges the Fragment lifecycle with the Dialog lifecycle, allowing dialogs to be managed by the FragmentManager (back stack, state saving).

## Architecture Overview
*   **Inheritance**: `Fragment`.
*   **Key Component**: `Dialog` (mDialog).

## Detailed Functionality

### Lifecycle Integration
*   `onGetLayoutInflater`: Creates the Dialog.
*   `onActivityCreated`: Configuring the dialog (content view, owner).
*   `onStart`: Shows the dialog (`mDialog.show()`).
*   `onStop`: Hides the dialog (`mDialog.hide()`).
*   `onDestroyView`: Dismisses the dialog.

### Display Modes
*   **Dialog Mode**: Shows as a floating dialog.
*   **Embed Mode**: Can also be embedded as a standard fragment (if `showsDialog` is false).

### API
*   `show(FragmentManager, tag)`: Adds to transaction and commits.
*   `dismiss()`: Dismisses dialog and removes fragment.

## Java-to-C++ Translation Guide
*   Requires `Fragment` implementation.
*   Logic acts as a glue between Fragment state transitions and Dialog methods.

## Implementation Risks
*   **State Loss**: Dismissing after onSaveInstanceState requires `allowStateLoss` variants.
*   **Recreation**: Dialog must be recreated on configuration change (handled by Fragment lifecycle).
