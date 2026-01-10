# AutofillPopupWindow - Reverse Engineering Documentation

## Executive Summary
A custom `PopupWindow` used to show the Autofill UI (e.g., the dropdown menu). It isolates the UI content from the app process (rendered in a system process via `IAutofillWindowPresenter` if using the constructor with presenter).

## Architecture
*   **Presenter**: `IAutofillWindowPresenter` (Binder) controls the backing window.
*   **Anchor**: Attaches to an anchor View.

## Java-to-C++ Translation Guide
*   **UI Toolkit**: This is a UI widget. Requires a windowing system.
